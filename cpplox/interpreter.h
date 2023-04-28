#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include <functional>

#include "expr.h"
#include "stmt.h"
#include "value.h"
#include "callable.h"
#include "return.h"
#include "environment.h"
#include "error.h"
#include "utils/string_format.h"

template<typename F>
struct BinOpTraits;

template<typename R, typename A>
struct BinOpTraits<R(*)(A,A)> {
    using RetType = R;
    using ArgType = A;
};
template<typename R, typename A>
struct BinOpTraits<std::function<R(A,A)>> {
    using RetType = R;
    using ArgType = A;
};

// literal to value
class Interpreter: public ExprVisitor<std::shared_ptr<Value>>, public StmtVisitor<void> {
    friend class UserFunction;
    friend class Resolver;

    // Environment *environment;
    std::shared_ptr<Environment> globals;
    std::shared_ptr<Environment> environment;

    static double add(double l, double r) {
        return l + r;
    }
    static double sub(double l, double r) {
        std::cout<<"sub"<<l<<" " << r<<std::endl;
        return l - r;
    }
    static double mul(double l, double r) {
        return l * r;
    }
    static double div(double l, double r) {
        return l / r;
    }
    static bool greater(double l, double r) { return l > r; }
    static bool greater_equal(double l, double r) { return l >= r; }
    static bool less(double l, double r) { return l < r; }
    static bool less_equal(double l, double r) { return l <= r; }
    static bool not_equal(double l, double r) { return l != r; } // TODO string equal
    // static bool equal(double l, double r) { return l == r; }

    // 函数模板不允许特化
    template<typename Op>
    static auto evalBin(Op op, std::shared_ptr<Value> l, std::shared_ptr<Value> r, const std::shared_ptr<RuntimeError> err=nullptr) {
    // static auto evalBin(Op op, std::shared_ptr<Value> l, std::shared_ptr<Value> r) {
        using vt = typename BinOpTraits<Op>::ArgType;
        using rt = typename BinOpTraits<Op>::RetType;
        auto ln = std::dynamic_pointer_cast<Val<vt>>(l);
        auto rn = std::dynamic_pointer_cast<Val<vt>>(r);
        if(ln && rn) {
            return std::make_shared<Val<rt>>(op(ln->v, rn->v));
        }
        if (err != nullptr) {
            throw *err;
        }
        return std::shared_ptr<Val<rt>>(nullptr);
    }

    std::shared_ptr<Value> visitBinary(Binary *e) {
        auto left = evaluate(e->left);
        auto right = evaluate(e->right);
        auto number_err = std::make_shared<RuntimeError>(RuntimeError::NumberOperand(e->op));
        switch(e->op.type) {
            case MINUS:
                // return evalBin(sub, left, right);
                return evalBin(std::function([](double l, double r) -> double { return l - r; }), left, right, number_err);
            case SLASH:
                return evalBin(div, left, right, number_err);
            case STAR:
                return evalBin(mul, left, right, number_err);
            case PLUS: {
                    if(auto sum = evalBin(add, left, right)){ // != nullptr
                        return sum;
                    }
                    if(auto sum = evalBin(std::function([](std::string l, std::string r)->std::string { return l + r;}), left, right)){ // != nullptr
                        return sum;
                    }
                    auto l = std::dynamic_pointer_cast<StringValue>(left);
                    if(l) {
                        return std::make_shared<StringValue>(l->v + right->toString());
                    }
                    throw RuntimeError::NumberStringOperand(e->op);
                    // return evalBin(std::operator+<std::string>, left,right);
            }
            case GREATER:
                return evalBin(greater, left, right, number_err);
            case GREATER_EQUAL:
                return evalBin(greater_equal, left, right, number_err);
            case LESS:
                return evalBin(less, left, right, number_err);
            case LESS_EQUAL:
                return evalBin(less_equal, left, right, number_err);
            case BANG_EQUAL:
                // return evalBin(not_equal, left, right, number_err);
                return std::make_shared<BoolValue>((*left) != right);
            case EQUAL_EQUAL: {
                return std::make_shared<BoolValue>((*left) == right);
            }
            default:
                throw std::runtime_error("interpreter error visit non-binary expr.");
        }
    }
    std::shared_ptr<Value> visitAssign(Assign *e) {
        auto v = evaluate(e->value);
        if (locals.contains(e)) {
            auto distance = locals[e];
            environment->assignAt(distance, e->name, v);
        } else {
            globals->assign(e->name, v);
        }
        return v;
    }
    std::shared_ptr<Value> visitGrouping(Grouping *e) {
        return evaluate(e->expression);
    }
    std::shared_ptr<Value> visitThis(This *e) {
        return lookUpVariable(e->keyword, e);
    }
    std::shared_ptr<Value> visitLiteral(Literal *e) {
        return e->value;
    }
    std::shared_ptr<Value> visitLogical(Logical *e) {
        auto left = evaluate(e->left);
        if (e->op.type==OR) {
            if(isTruthy(left)) return left;
        } else {
            if(!isTruthy(left)) return left;
        }
        return evaluate(e->right);
    }
    std::shared_ptr<Value> visitUnary(Unary *e) {
        auto right = evaluate(e->right);
        switch(e->op.type) {
            case BANG:
                return std::make_shared<BoolValue>(!isTruthy(right));
            case MINUS:
                if(auto v = std::dynamic_pointer_cast<NumberValue>(right)) {
                    return std::make_shared<NumberValue>(-(v->v));
                } else {
                    throw RuntimeError(e->op, "Operand must be a number.");
                }
            default:
                throw std::runtime_error("interpreter error visit non-unary expr."); // this is not lox runtime error! It's interpreter bug.
        }
        return nullptr;
    }
    std::shared_ptr<Value> visitCall(Call *e) {
        auto callee = evaluate(e->callee);
        std::vector<std::shared_ptr<Value>> arguments;
        arguments.reserve(e->arguments.size());
        for(auto &argument: e->arguments) {
            arguments.push_back(evaluate(argument));
        }
        auto function = std::dynamic_pointer_cast<Callable>(callee);
        if (function == nullptr) {
            throw RuntimeError(e->paren, "Can only call function and classes.");
        }
        if (arguments.size() != function->arity()) {
            throw RuntimeError(e->paren, string_format("Expected %d arguments but got %d.", function->arity(), arguments.size()));
        }
        return function->call(this, e->paren, arguments);
        return std::make_shared<NilValue>();
    }
    std::shared_ptr<Value> visitGet(Get *e) {
        auto object = evaluate(e->object);
        auto instance = std::dynamic_pointer_cast<UserClassInstance>(object);
        if (instance==nullptr) {
            throw RuntimeError(e->name,"Only instance have properties.");
        }
        return instance->get(e->name);
    }
    std::shared_ptr<Value> visitSet(Set *e) {
        auto object = evaluate(e->object);
        auto instance = std::dynamic_pointer_cast<UserClassInstance>(object);
        if (instance==nullptr) {
            throw RuntimeError(e->name,"Only instance have fields.");
        }
        auto value = evaluate(e->value);
        instance->set(e->name, value);
        return value;
    }
    std::shared_ptr<Value> visitVariable(Variable *e) {
        return lookUpVariable(e->name, e);
    }

    bool isTruthy(std::shared_ptr<Value> v) {
        /* if(auto bv=valueAs<BoolValue>(v)) { */
        /*     return bv->v; */
        /* } else if(auto nv=valueAs<NilValue>(v)) { */
        /*     return false; */
        /* } */
        if(auto bv=std::dynamic_pointer_cast<BoolValue>(v)) {
            return bv->v;
        } else if(auto nv=std::dynamic_pointer_cast<NilValue>(v)) {
            return false;
        }
        return true;
    }

    // visit statements
    void visitExpression(Expression *stmt) {
        // stmt->expression->accept(this);
        evaluate(stmt->expression); // discard return value
    }
    void visitPrint(Print *stmt) {
        auto v = evaluate(stmt->expression);
        std::cout<< v->toString() << std::endl;
    }
    void visitVar(Var *stmt) {
        std::shared_ptr<Value> v = std::make_shared<NilValue>();
        if (stmt->initializer!=nullptr) {
            v = evaluate(stmt->initializer);
        }
        environment->define(stmt->name.lexeme, v);
    }
    void visitClass(Class *stmt) {
        std::shared_ptr<UserClass> superclass;
        if(stmt->superclass!=nullptr) {
            superclass = std::dynamic_pointer_cast<UserClass>(evaluate(stmt->superclass));
            if(superclass==nullptr) {
                throw RuntimeError(stmt->superclass->name, "Superclass must be a class.");
            }
        }

        environment->define(stmt->name.lexeme, std::make_shared<NilValue>());
        std::map<std::string, std::shared_ptr<UserFunction>> methods;
        for(const auto &method: stmt->methods) {
            auto isInitializer = method->name.lexeme == "init";
            methods[method->name.lexeme] = std::make_shared<UserFunction>(*method, environment, isInitializer); // 重复引用environment
        }
        auto klass = std::make_shared<UserClass>(stmt, superclass, methods);
        environment->assign(stmt->name, klass);
    }
    void visitFunction(Function *stmt) {
        /*
            TODO
            此处会导致environment和UserFunction之间的shared_ptr循环引用，
            切不能使用week_ptr打破循环，因为存在两种引用方式
            environment->function               (局部函数)
            globals/outer->function->enviroment (闭包函数)
            会导致没有引用时，无法释放
            function<->enviroment (循环)

            class同理
        */
        environment->define(stmt->name.lexeme, std::make_shared<UserFunction>(*stmt, environment));
    }
    void visitReturn(Return *stmt) {
        std::shared_ptr<Value> v;
        if (stmt->value != nullptr) {
            v = evaluate(stmt->value);
        } else {
            v = std::make_shared<NilValue>();
        }
        throw ReturnException(v);
    }
    void visitBlock(Block *stmt) {
        executeBlock(stmt->statements, std::make_shared<Environment>(environment)); // execute block in new environment
    }
    void executeBlock(std::vector<std::shared_ptr<Stmt>> stmts, std::shared_ptr<Environment> env) {
        auto previous = environment;
        environment = env;
        try {
            evaluate(stmts);
        } catch(...) {
            // restore environment for exception
            environment = previous;
            throw;
        }
        environment = previous;
    }
    void visitIf(If *stmt) {
        auto condition  = evaluate(stmt->condition);
        if(isTruthy(condition)) {
            evaluate(stmt->thenBranch);
        } else if (stmt->elseBranch != nullptr) {
            evaluate(stmt->elseBranch);
        }
    }
    void visitWhile(While *stmt) {
        while (isTruthy(evaluate(stmt->condition))) {
            evaluate(stmt->body);
        }
    }

    std::map<const Expr*, int> locals;
    void resolve(const Expr * const e, int depth) {
        locals[e] = depth;
    }
    std::shared_ptr<Value> lookUpVariable(Token name, const Expr * const expr) {
        if (!locals.contains(expr)) {
            return globals->get(name);
        }
        auto distance = locals[expr];
        try{
            return environment->getAt(distance, name);
        } catch(...) {
            std::cout << "error looking up '" << name << "' " << expr <<" @ distance " << distance << std::endl;
            Environment::dump(environment);
            throw;
        }
    }
public:
    Interpreter() {
        globals = std::make_shared<Environment>();
        environment = globals;
        globals->define("clock", std::make_shared<NativeClock>());
        globals->define("read", std::make_shared<NativeRead>());
    }
    std::shared_ptr<Value> evaluate(std::shared_ptr<Expr> expr) {
        /* if(expr==nullptr) { */
        /*     /1* return std::make_shared<NumberLiteral>(); *1/ */
        /*     return nullptr; */
        /* } */
        return expr->accept(this);
    }
    void evaluate(std::vector<std::shared_ptr<Stmt>> stmts) {
        for(const auto stmt: stmts) {
            stmt->accept(this);
        }
    }
    void evaluate(std::shared_ptr<Stmt> stmt) {
        stmt->accept(this);
    }
};

#endif //_INTERPRETER_H_
