#ifndef _EXPR_H_
#define _EXPR_H_

#include "token.h"

class ExprVisitor;
// abstract expr
struct Expr
{
    virtual std::shared_ptr<void> accept(ExprVisitor* const) = 0;
};

// GENERATOR_START
// Binary      : *Expr left, Token op, *Expr right
// Grouping    : *Expr expression
// Literal     : *Value value
// Unary       : Token op, *Expr right
// GENERATED
// GENERATOR_END

#endif // _EXPR_H_
