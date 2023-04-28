// GENERATED BY ast_generator. DO NOT EDIT.
#ifndef _STMT_H_
#define _STMT_H_

#include <iostream>
#include "token.h"
#include "expr.h"

// GENERATOR_START
// Block      : *Stmt[] statements
// Expression : *Expr expression
// Function   : Token name, Token[] params, *Stmt[] body
// Return     : Token keyword, *Expr value
// Class      : Token name, *Variable superclass, *Function[] methods
// If         : *Expr condition, *Stmt thenBranch, *Stmt elseBranch
// Print      : *Expr expression
// Var        : Token name, *Expr initializer
// While      : *Expr condition, *Stmt body
// GENERATED
// class declaration
class Block;
class Expression;
class Function;
class Return;
class Class;
class If;
class Print;
class Var;
class While;

// templated vistor for inherit
template <typename T>
class StmtVisitor {
public:
    virtual T visitBlock(Block *) = 0;
    virtual T visitExpression(Expression *) = 0;
    virtual T visitFunction(Function *) = 0;
    virtual T visitReturn(Return *) = 0;
    virtual T visitClass(Class *) = 0;
    virtual T visitIf(If *) = 0;
    virtual T visitPrint(Print *) = 0;
    virtual T visitVar(Var *) = 0;
    virtual T visitWhile(While *) = 0;
};

// internal general vistor for virtual accept
class _StmtVisitor {
public:
    virtual std::shared_ptr<void> visitBlock(Block *) = 0;
    virtual std::shared_ptr<void> visitExpression(Expression *) = 0;
    virtual std::shared_ptr<void> visitFunction(Function *) = 0;
    virtual std::shared_ptr<void> visitReturn(Return *) = 0;
    virtual std::shared_ptr<void> visitClass(Class *) = 0;
    virtual std::shared_ptr<void> visitIf(If *) = 0;
    virtual std::shared_ptr<void> visitPrint(Print *) = 0;
    virtual std::shared_ptr<void> visitVar(Var *) = 0;
    virtual std::shared_ptr<void> visitWhile(While *) = 0;
};

// templated vistor to internal vistor
template <typename T>
class StmtVisitorConvertor: public _StmtVisitor {
    StmtVisitor<T> *v;
public:
    StmtVisitorConvertor(StmtVisitor<T> *v): v(v) {}
    std::shared_ptr<void> visitBlock(Block *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitBlock(e)));
    }
    std::shared_ptr<void> visitExpression(Expression *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitExpression(e)));
    }
    std::shared_ptr<void> visitFunction(Function *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitFunction(e)));
    }
    std::shared_ptr<void> visitReturn(Return *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitReturn(e)));
    }
    std::shared_ptr<void> visitClass(Class *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitClass(e)));
    }
    std::shared_ptr<void> visitIf(If *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitIf(e)));
    }
    std::shared_ptr<void> visitPrint(Print *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitPrint(e)));
    }
    std::shared_ptr<void> visitVar(Var *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitVar(e)));
    }
    std::shared_ptr<void> visitWhile(While *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitWhile(e)));
    }
};

// 返回值类型为shared_ptr的模板特化
template <typename T>
class StmtVisitorConvertor<std::shared_ptr<T>>: public _StmtVisitor {
    StmtVisitor<std::shared_ptr<T>> *v;
public:
    StmtVisitorConvertor(StmtVisitor<std::shared_ptr<T>> *v): v(v) {}
    std::shared_ptr<void> visitBlock(Block *e) {
        return std::static_pointer_cast<void>(v->visitBlock(e));
    }
    std::shared_ptr<void> visitExpression(Expression *e) {
        return std::static_pointer_cast<void>(v->visitExpression(e));
    }
    std::shared_ptr<void> visitFunction(Function *e) {
        return std::static_pointer_cast<void>(v->visitFunction(e));
    }
    std::shared_ptr<void> visitReturn(Return *e) {
        return std::static_pointer_cast<void>(v->visitReturn(e));
    }
    std::shared_ptr<void> visitClass(Class *e) {
        return std::static_pointer_cast<void>(v->visitClass(e));
    }
    std::shared_ptr<void> visitIf(If *e) {
        return std::static_pointer_cast<void>(v->visitIf(e));
    }
    std::shared_ptr<void> visitPrint(Print *e) {
        return std::static_pointer_cast<void>(v->visitPrint(e));
    }
    std::shared_ptr<void> visitVar(Var *e) {
        return std::static_pointer_cast<void>(v->visitVar(e));
    }
    std::shared_ptr<void> visitWhile(While *e) {
        return std::static_pointer_cast<void>(v->visitWhile(e));
    }
};

// 返回值类型为void的模板特化
template <>
class StmtVisitorConvertor<void>: public _StmtVisitor {
    StmtVisitor<void> *v;
public:
    StmtVisitorConvertor(StmtVisitor<void> *v): v(v) {}
    std::shared_ptr<void> visitBlock(Block *e) {
        v->visitBlock(e);
        return nullptr;
    }
    std::shared_ptr<void> visitExpression(Expression *e) {
        v->visitExpression(e);
        return nullptr;
    }
    std::shared_ptr<void> visitFunction(Function *e) {
        v->visitFunction(e);
        return nullptr;
    }
    std::shared_ptr<void> visitReturn(Return *e) {
        v->visitReturn(e);
        return nullptr;
    }
    std::shared_ptr<void> visitClass(Class *e) {
        v->visitClass(e);
        return nullptr;
    }
    std::shared_ptr<void> visitIf(If *e) {
        v->visitIf(e);
        return nullptr;
    }
    std::shared_ptr<void> visitPrint(Print *e) {
        v->visitPrint(e);
        return nullptr;
    }
    std::shared_ptr<void> visitVar(Var *e) {
        v->visitVar(e);
        return nullptr;
    }
    std::shared_ptr<void> visitWhile(While *e) {
        v->visitWhile(e);
        return nullptr;
    }
};

// Stmt definition
struct Stmt {
    template <typename T>
    T accept(StmtVisitor<T> *const v) {
        auto visitor = StmtVisitorConvertor<T>(v);
        return *(std::static_pointer_cast<T>(this->_accept(&visitor)));
    }

    template <typename T>
    std::shared_ptr<T> accept(StmtVisitor<std::shared_ptr<T>> *const v) {
        auto visitor = StmtVisitorConvertor<std::shared_ptr<T>>(v);
        return std::static_pointer_cast<T>(this->_accept(&visitor));
    }

    // c++ 成员函数不支持template + virtual
    // 分成两步
    // virtual的_accept用于继承，使用通用类型的visitor
    // 基类实现template的accept，不需要子类继承，仅做类型转换后调用使用通用类型的virtual的_accept
    virtual std::shared_ptr<void> _accept(_StmtVisitor* const) = 0;
};
template <>
inline void Stmt::accept<void>(StmtVisitor<void> *const v) {
    auto visitor = StmtVisitorConvertor<void>(v);
    this->_accept(&visitor);
}

struct Block: public Stmt {
    std::vector<std::shared_ptr<Stmt>> statements;

    std::shared_ptr<void> _accept(_StmtVisitor * const v) { return v->visitBlock(this); }
    Block(std::vector<std::shared_ptr<Stmt>> statements): statements(statements) {}
};

struct Expression: public Stmt {
    std::shared_ptr<Expr> expression;

    std::shared_ptr<void> _accept(_StmtVisitor * const v) { return v->visitExpression(this); }
    Expression(std::shared_ptr<Expr> expression): expression(expression) {}
};

struct Function: public Stmt {
    Token name;
    std::vector<Token> params;
    std::vector<std::shared_ptr<Stmt>> body;

    std::shared_ptr<void> _accept(_StmtVisitor * const v) { return v->visitFunction(this); }
    Function(Token name, std::vector<Token> params, std::vector<std::shared_ptr<Stmt>> body): name(name), params(params), body(body) {}
};

struct Return: public Stmt {
    Token keyword;
    std::shared_ptr<Expr> value;

    std::shared_ptr<void> _accept(_StmtVisitor * const v) { return v->visitReturn(this); }
    Return(Token keyword, std::shared_ptr<Expr> value): keyword(keyword), value(value) {}
};

struct Class: public Stmt {
    Token name;
    std::shared_ptr<Variable> superclass;
    std::vector<std::shared_ptr<Function>> methods;

    std::shared_ptr<void> _accept(_StmtVisitor * const v) { return v->visitClass(this); }
    Class(Token name, std::shared_ptr<Variable> superclass, std::vector<std::shared_ptr<Function>> methods): name(name), superclass(superclass), methods(methods) {}
};

struct If: public Stmt {
    std::shared_ptr<Expr> condition;
    std::shared_ptr<Stmt> thenBranch;
    std::shared_ptr<Stmt> elseBranch;

    std::shared_ptr<void> _accept(_StmtVisitor * const v) { return v->visitIf(this); }
    If(std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> thenBranch, std::shared_ptr<Stmt> elseBranch): condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}
};

struct Print: public Stmt {
    std::shared_ptr<Expr> expression;

    std::shared_ptr<void> _accept(_StmtVisitor * const v) { return v->visitPrint(this); }
    Print(std::shared_ptr<Expr> expression): expression(expression) {}
};

struct Var: public Stmt {
    Token name;
    std::shared_ptr<Expr> initializer;

    std::shared_ptr<void> _accept(_StmtVisitor * const v) { return v->visitVar(this); }
    Var(Token name, std::shared_ptr<Expr> initializer): name(name), initializer(initializer) {}
};

struct While: public Stmt {
    std::shared_ptr<Expr> condition;
    std::shared_ptr<Stmt> body;

    std::shared_ptr<void> _accept(_StmtVisitor * const v) { return v->visitWhile(this); }
    While(std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> body): condition(condition), body(body) {}
};

// GENERATOR_END

#endif // _STMT_H_
