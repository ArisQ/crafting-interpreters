#ifndef _EXPR_H_
#define _EXPR_H_

#include <iostream>
#include "token.h"

// GENERATOR_START
// Assign      : Token name, *Expr value
// Binary      : *Expr left, Token op, *Expr right
// Grouping    : *Expr expression
// Literal     : *Value value
// Logical     : *Expr left, Token op, *Expr right
// Unary       : Token op, *Expr right
// Variable    : Token name
// GENERATED
class Binary;
class Grouping;
class Literal;
class Unary;

template <typename T>
class ExprVisitor {
public:
    virtual T visitBinary(Binary *) = 0;
    virtual T visitGrouping(Grouping *) = 0;
    virtual T visitLiteral(Literal*) = 0;
    virtual T visitUnary(Unary *) = 0;
};

class _ExprVisitor {
public:
    virtual std::shared_ptr<void> visitBinary(Binary *) = 0;
    virtual std::shared_ptr<void> visitGrouping(Grouping *) = 0;
    virtual std::shared_ptr<void> visitLiteral(Literal*) = 0;
    virtual std::shared_ptr<void> visitUnary(Unary *) = 0;
};

template <typename T>
class ExprVisitorConvertor: public _ExprVisitor {
    ExprVisitor<T> *v;
public:
    ExprVisitorConvertor(ExprVisitor<T> *v): v(v){}
    std::shared_ptr<void> visitBinary(Binary *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitBinary(e)));
    }
    std::shared_ptr<void> visitGrouping(Grouping *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitGrouping(e)));
    }
    std::shared_ptr<void> visitLiteral(Literal *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitLiteral(e)));
    }
    std::shared_ptr<void> visitUnary(Unary *e) {
        return std::static_pointer_cast<void>(std::make_shared<T>(v->visitUnary(e)));
    }
};
// 返回值类型为shared_ptr的模板特化
template <typename T>
class ExprVisitorConvertor<std::shared_ptr<T>>: public _ExprVisitor {
    ExprVisitor<std::shared_ptr<T>> *v;
public:
    ExprVisitorConvertor(ExprVisitor<std::shared_ptr<T>> *v): v(v){}
    std::shared_ptr<void> visitBinary(Binary *e) {
        return std::static_pointer_cast<void>(v->visitBinary(e));
    }
    std::shared_ptr<void> visitGrouping(Grouping *e) {
        return std::static_pointer_cast<void>(v->visitGrouping(e));
    }
    std::shared_ptr<void> visitLiteral(Literal*e) {
        /* std::cout<<"特化visitLiteral" <<std::endl; */
        return std::static_pointer_cast<void>(v->visitLiteral(e));
    }
    std::shared_ptr<void> visitUnary(Unary *e) {
        return std::static_pointer_cast<void>(v->visitUnary(e));
    }
};

struct Expr {
    template <typename T>
    T accept(ExprVisitor<T> *const v) {
        /* std::cout<<"value 版本 accept" <<std::endl; */
        auto visitor = ExprVisitorConvertor<T>(v);
        return *(std::static_pointer_cast<T>(this->_accept(&visitor)));
    }
    template <typename T>
    std::shared_ptr<T> accept(ExprVisitor<std::shared_ptr<T>> *const v) {
        /* std::cout<<"shared_ptr 版本 accept" <<std::endl; */
        auto visitor = ExprVisitorConvertor<std::shared_ptr<T>>(v);
        return std::static_pointer_cast<T>(this->_accept(&visitor));
    }
    // c++ 成员函数不支持template + virtual
    // 分成两步
    // virtual的_accept用于继承，使用通用类型的visitor
    // Expr基类实现template的accept，不需要子类继承，仅做类型转换后调用使用通用类型的virtual的_accept
    virtual std::shared_ptr<void> _accept(_ExprVisitor* const) = 0;
};

struct Binary: public Expr {
    Token op;
    std::shared_ptr<Expr> left;
    std::shared_ptr<Expr> right;

    std::shared_ptr<void> _accept(_ExprVisitor * const v) { return v->visitBinary(this); }
    Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(left), op(op), right(right) { }
};
struct Grouping: public Expr {
    std::shared_ptr<Expr> expression;

    std::shared_ptr<void> _accept(_ExprVisitor *v) { return v->visitGrouping(this); }
    Grouping(std::shared_ptr<Expr> expr) : expression(expr) {}
};
struct Literal: public Expr { // literal expr
    std::shared_ptr<Value> value;

    std::shared_ptr<void> _accept(_ExprVisitor *v) { return v->visitLiteral(this); }
    Literal(std::shared_ptr<Value> value): value(value) {}
};
struct Unary: public Expr {
    Token op;
    std::shared_ptr<Expr> right;

    std::shared_ptr<void> _accept(_ExprVisitor *v) { return v->visitUnary(this); }
    Unary(Token op, std::shared_ptr<Expr> right): op(op), right(right) {}
};
// GENERATOR_END

#endif // _EXPR_H_
