#ifndef _AST_PRINTER_H_
#define _AST_PRINTER_H_

#include "expr.h"
#include "stmt.h"

class AstPrinter: public ExprVisitor<std::string>, StmtVisitor<std::string> {
    std::string parenthesize(const std::string &name,std::vector<std::shared_ptr<Expr>> list = {}) {
        std::string ret = "(";
        ret += name;
        for (auto expr: list)
        {
            ret += " ";
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
        ret += " ";
        ret += token.lexeme;
        for (auto expr: list)
        {
            ret += " ";
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
    std::string visitThis(This *e) {
        return e->keyword.lexeme;
    }
    std::string visitLiteral(Literal *e) {
        return e->value->toString();
    }
    std::string visitLogical(Logical *e) {
        return parenthesize(e->op.lexeme, {e->left, e->right});
    }
    std::string visitUnary(Unary *e) {
        return parenthesize(e->op.lexeme, {e->right});
    }
    std::string visitCall(Call *e) {
        return parenthesize(e->callee->accept(this), e->arguments);
    }
    std::string visitGet(Get *e) {
        return parenthesize("get", e->name, {e->object});
    }
    std::string visitSet(Set *e) {
        return parenthesize("set", e->name, {e->object, e->value});
    }
    std::string visitVariable(Variable *e) {
        return "<" + e->name.lexeme + ">";
    }

    std::string indent = "";
    std::string incrIndent() {
        auto oldIdnent = indent;
        indent = indent + "  ";
        return oldIdnent;
    }
    void restoreIndent(std::string ind) {
        indent = ind;
    }
    std::string stmtIndent(std::string str) {
        return indent + str + '\n';
    }

    // visit statements
    std::string visitExpression(Expression *stmt) {
        return stmtIndent(stmt->expression->accept(this));
    }
    std::string visitPrint(Print *stmt) {
        return stmtIndent(parenthesize("print", {stmt->expression}));
    }
    std::string visitVar(Var *stmt) {
        // return parenthesize("var<" + stmt->name.lexeme + ">", {stmt->initializer});
        return stmtIndent(parenthesize("var", stmt->name, {stmt->initializer}));
    }
    std::string visitClass(Class *stmt) {
        std::string ret = stmtIndent("(class " + stmt->name.lexeme);
        auto oldIndent = incrIndent();
        for(const auto &r: stmt->methods) {
            ret += r->accept(this);
        }
        restoreIndent(oldIndent);
        ret += stmtIndent(")");
        return ret;
    }
    std::string visitFunction(Function *stmt) {
        std::string ret = "(fun " + stmt->name.lexeme;
        for (auto &p: stmt->params) {
            ret += " " + p.lexeme;
        }
        ret = stmtIndent(ret);
        auto oldIndent = incrIndent();
        ret += block(stmt->body);
        restoreIndent(oldIndent);
        ret += stmtIndent(")");
        return ret;
    }
    std::string visitReturn(Return *stmt) {
        return stmtIndent(parenthesize(stmt->keyword.lexeme, {stmt->value}));
    }
    std::string visitBlock(Block *stmt) {
        return block(stmt->statements);
    }
    std::string block(std::vector<std::shared_ptr<Stmt>> stmts) {
        std::string ret = stmtIndent("(");
        auto oldIndent = incrIndent();
        for(auto &s: stmts) {
            ret += s->accept(this);
        }
        restoreIndent(oldIndent);
        ret += stmtIndent(")");
        return ret;
    }
    std::string visitIf(If *stmt) {
        std::string ret;
        ret += stmtIndent("(");
        auto oldIndent = incrIndent();
        ret += stmtIndent( "if " + stmt->condition->accept(this));
        ret += stmt->thenBranch->accept(this);
        if(stmt->elseBranch != nullptr) {
            ret += stmtIndent("else");
            ret += stmt->elseBranch->accept(this);
        }
        restoreIndent(oldIndent);
        ret += stmtIndent(")");
        return ret;
    }
    std::string visitWhile(While *stmt) {
        std::vector<std::string> result;
        result.push_back(stmtIndent("("));
        auto oldIndent = incrIndent();
        result.push_back(stmtIndent( "while " + stmt->condition->accept(this)));
        result.push_back(stmt->body->accept(this));
        restoreIndent(oldIndent);
        result.push_back(stmtIndent(")"));
        std::string ret;
        for(const auto &r: result) {
            ret += r;
        }
        return ret;
    }
public:
    const std::string print(std::vector<std::shared_ptr<Stmt>> stmts) {
        std::string ret;
        for(const auto &r: visit(stmts)) {
            ret += r;
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
