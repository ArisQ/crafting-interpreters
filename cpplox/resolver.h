#ifndef _RESOLVER_H_
#define _RESOLVER_H_

#include <stack>

#include "expr.h"
#include "stmt.h"
#include "interpreter.h"
#include "lox.h"

enum FunctionType {
    NONE,
    FUNCITON,
    INITIALIZER,
    METHOD,
};
enum ClassType {
    CT_NONE,
    CT_CLASS,
};

class Resolver: public ExprVisitor<void>, public StmtVisitor<void> {
    Lox *lox;
    Interpreter *interpreter;

    FunctionType currentFunction = NONE;
    ClassType currentClass = CT_NONE;

    std::vector<std::map<std::string, bool>> scopes;
    void beginScope() {
        scopes.push_back(std::map<std::string,bool>());
    }
    void endScope() {
        scopes.pop_back();
    }
    void declare(Token name) {
        if(scopes.empty()) return;
        auto &scope = scopes.back();
        if(scope.contains(name.lexeme)) {
            lox->error(name, "Already variable with this name in this scope.");
        }
        scope[name.lexeme] = false;
    }
    void define(Token name) {
        if(scopes.empty()) return;
        auto &scope = scopes.back();
        scope[name.lexeme] = true;
    }

    void resolveLocal(const Expr *const e, const Token &name) {
        auto size = scopes.size();
        for(int i=size-1; i>=0; --i) {
            if(scopes[i].contains(name.lexeme)) {
                interpreter->resolve(e, size - 1 - i);
                return;
            }
        }
    }
    void resolveFunction(const Function &fn, FunctionType type) {
        auto enclosingFunction = currentFunction;
        currentFunction = type;
        beginScope();
        for(auto param: fn.params) {
            declare(param);
            define(param);
        }
        resolve(fn.body);
        endScope();
        currentFunction = enclosingFunction;
    }
public:
    Resolver(Lox *lox,Interpreter *interpreter): lox(lox),interpreter(interpreter) {}

    // visit expr
    void visitAssign(Assign *e) {
        resolve(e->value);
        resolveLocal(e, e->name);
    }
    void visitBinary(Binary *e) {
        resolve(e->left);
        resolve(e->right);
    }
    void visitCall(Call *e) {
        resolve(e->callee);
        for(auto &arg: e->arguments) {
            resolve(arg);
        }
    }
    void visitGet(Get *e) {
        resolve(e->object);
    }
    void visitSet(Set *e) {
        resolve(e->object);
        resolve(e->value);
    }
    void visitGrouping(Grouping *e) {
        resolve(e->expression);
    }
    void visitThis(This *e) {
        if(currentClass==CT_NONE) {
            lox->error(e->keyword, "Can't use 'this' outside of a class.");
            return;
        }
        resolveLocal(e, e->keyword);
    }
    void visitSuper(Super *e) {
        if(currentClass==CT_NONE) {
            lox->error(e->keyword, "Can't use 'super' outside of a class.");
            return;
        }
        resolveLocal(e, e->keyword);
    }
    void visitLiteral(Literal *e) { /* nothing */ }
    void visitLogical(Logical *e) {
        resolve(e->left);
        resolve(e->right);
    }
    void visitUnary(Unary *e) {
        resolve(e->right);
    }
    void visitVariable(Variable *e) {
        if(!scopes.empty()) {
            auto &scope = scopes.back();
            if(scope.contains(e->name.lexeme) && scope.at(e->name.lexeme)==false) {
                lox->error(e->name, "Can't read local variable in its own initializer.");
            }
        }
        resolveLocal(e, e->name);
    }

    // visit stmt
    void visitBlock(Block *stmt) {
        beginScope();
        resolve(stmt->statements);
        endScope();
    }
    void visitExpression(Expression *stmt) {
        resolve(stmt->expression);
    }
    void visitClass(Class *stmt) {
        auto enclosingClass = currentClass;
        currentClass = CT_CLASS;

        declare(stmt->name);
        define(stmt->name);

        auto &superclass = stmt->superclass;
        if(superclass != nullptr) {
            if(superclass->name.lexeme == stmt->name.lexeme) {
                lox->error(superclass->name, "A class can't inherit from itself.");
            }
            resolve(superclass);

            beginScope();
            scopes.back()["super"] = true;
        }

        beginScope();
        scopes.back()["this"] = true;

        for(auto &m: stmt->methods) {
            auto declaration = METHOD;
            if (m->name.lexeme == "init") {
                declaration = INITIALIZER;
            }
            resolveFunction(*m, declaration);
        }

        if(stmt->superclass!=nullptr) {
            endScope();
        }
        endScope();

        currentClass = enclosingClass;
    }
    void visitFunction(Function *stmt) {
        declare(stmt->name);
        define(stmt->name);
        resolveFunction(*stmt, FUNCITON);
    }
    void visitReturn(Return *stmt) {
        if(currentFunction==NONE) {
            lox->error(stmt->keyword, "Can't return from top-level code.");
        }
        if(stmt->value!=nullptr) {
            if(currentFunction==INITIALIZER) {
                lox->error(stmt->keyword, "Can't return a value from an initializer.");
            }
            resolve(stmt->value);
        }
    }
    void visitIf(If *stmt) {
        resolve(stmt->condition);
        resolve(stmt->thenBranch);
        if(stmt->elseBranch!=nullptr) resolve(stmt->elseBranch);
    }
    void visitPrint(Print *stmt) {
        resolve(stmt->expression);
    }
    void visitVar(Var *stmt) {
        declare(stmt->name);
        if(stmt->initializer!=nullptr) {
            resolve(stmt->initializer);
        }
        define(stmt->name);
    }
    void visitWhile(While *stmt) {
        resolve(stmt->condition);
        resolve(stmt->body);
    }

    void resolve(std::vector<std::shared_ptr<Stmt>> statements) {
        for(const auto &s: statements) {
            resolve(s);
        }
    }
    void resolve(std::shared_ptr<Stmt> stmt) {
        stmt->accept(this);
    }
    void resolve(std::shared_ptr<Expr> expr) {
        expr->accept(this);
    }
};

#endif // _RESOLVER_H_