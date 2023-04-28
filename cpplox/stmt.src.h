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
// GENERATOR_END

#endif // _STMT_H_
