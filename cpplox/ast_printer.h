#ifndef _AST_PRINTER_H_
#define _AST_PRINTER_H_

#include "expr.h"
#include "stmt.h"

class AstPrinter: public ExprVisitor<std::string>, StmtVisitor<std::string> {
    std::string parenthesize(const std::string &name,std::initializer_list<std::shared_ptr<Expr>> list = {}) {
        std::string ret = "(";
        ret += name;
        for (auto expr: list)
        {
            ret += ", ";
            std::string v = "nullptr";
            if(expr!=nullptr) {
                v = expr->accept(this);
                // v = *(expr->accept<int>(this));
            }
            ret += v;
        }
        ret += ")";
        return ret;
    }
    std::string parenthesize(const std::string &name, const Token &token,std::initializer_list<std::shared_ptr<Expr>> list = {}) {
        std::string ret = "(";
        ret += name;
        ret += ", ";
        ret += token.lexeme;
        for (auto expr: list)
        {
            ret += ", ";
            std::string v = "nullptr";
            if(expr!=nullptr) {
                v = expr->accept(this);
            }
            ret += v;
        }
        ret += ")";
        return ret;
    }
    std::string visitAssign(Assign *e) {
        // return parenthesize("assign " + e->name.lexeme, {e->value});
        return parenthesize("=", e->name, {e->value});
    }
    std::string visitBinary(Binary *e) {
        return parenthesize(e->op.lexeme, {e->left, e->right});
    }
    std::string visitGrouping(Grouping *e) {
        return parenthesize("group", {e->expression});
    }
    std::string visitLiteral(Literal *e) {
        return e->value->toString();
    }
    std::string visitUnary(Unary *e) {
        return parenthesize(e->op.lexeme, {e->right});
    }
    std::string visitVariable(Variable *e) {
        return "<" + e->name.lexeme + ">";
    }

    // visit statements
    std::string visitExpression(Expression *stmt) {
        return stmt->expression->accept(this);
    }
    std::string visitPrint(Print *stmt) {
        return parenthesize("print", {stmt->expression});
    }
    std::string visitVar(Var *stmt) {
        // return parenthesize("var<" + stmt->name.lexeme + ">", {stmt->initializer});
        return parenthesize("var", stmt->name, {stmt->initializer});
    }
    std::string visitBlock(Block *stmt) {
        std::vector<std::string> result;
        result.push_back("(");
        for(auto &s: visit(stmt->statements)) {
            result.push_back("  " + s);
        }
        result.push_back(")");
        std::string ret;
        for(const auto &r: result) {
            ret += r;
            ret += '\n';
        }
        return ret;
    }
public:
    const std::string print(std::vector<std::shared_ptr<Stmt>> stmts) {
        std::string ret;
        for(const auto &r: visit(stmts)) {
            ret += r;
            ret += '\n';
        }
        return ret;
    }
    const std::vector<std::string> visit(std::vector<std::shared_ptr<Stmt>> stmts) {
        std::vector<std::string> result;
        for(const auto &stmt: stmts) {
            result.push_back(stmt->accept(this));
        }
        return result;
    }
};

#endif // _AST_PRINTER_H_
