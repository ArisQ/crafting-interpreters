#ifndef _VM_COMPILER_H_
#define _VM_COMPILER_H_

#include "../stmt.h"
#include "../expr.h"

#include "chunk.h"

namespace vm {
class Compiler: public ExprVisitor<void>, public StmtVisitor<void> {
    Chunk *chunk;
    int currentLine = 0; // 不准确

    bool _hasError = false;
    void error(const char *msg) {
        _hasError = true;
        std::cerr << "[line " << currentLine << "] "<< msg << std::endl;
    }

    void writeConstant(const Value value) {
        auto constant = chunk->addConstant(value);
        if (constant > UINT8_MAX) {
            error("Too many constants in on chunk.");
            return;
        }
        chunk->write(OP_CONSTANT, currentLine);
        chunk->write(constant, currentLine);
        // chunk->writeConstant(value, currentLine);
    }
    void writeOp(const OpCode op) {
        chunk->write(op, currentLine);
    }
    void writeOp(const OpCode op1, const OpCode op2) {
        writeOp(op1);
        writeOp(op2);
    }

    void visitAssign(Assign *) {}
    void visitBinary(Binary *e) {
        currentLine = e->op.line;
        e->left->accept(this);
        e->right->accept(this);
        switch(e->op.type) {
            case PLUS: writeOp(OP_ADD); break;
            case MINUS: writeOp(OP_SUBSTRACT); break;
            case STAR: writeOp(OP_MULTIPLY); break;
            case SLASH: writeOp(OP_DIVIDE); break;
            case GREATER: writeOp(OP_GREATER); break;
            case GREATER_EQUAL: writeOp(OP_LESS, OP_NOT); break;
            case LESS: writeOp(OP_LESS); break;
            case LESS_EQUAL: writeOp(OP_GREATER, OP_NOT); break;
            case EQUAL_EQUAL: writeOp(OP_EQUAL); break;
            case BANG_EQUAL: writeOp(OP_EQUAL, OP_NOT); break;
            default: error("compiler error visit non-binary expr.");
        }
    }
    void visitCall(Call *) {}
    void visitGet(Get *) {}
    void visitSet(Set *) {}
    void visitThis(This *) {}
    void visitSuper(Super *) {}
    void visitGrouping(Grouping *e) {
        e->expression->accept(this);
    }
    void visitLiteral(Literal *e) {
        if(auto n = std::dynamic_pointer_cast<NumberValue>(e->value)) {
            writeConstant(NUMBER_VAL(n->v));
        } else if(auto n = std::dynamic_pointer_cast<NilValue>(e->value)) {
            writeOp(OP_NIL);
        } else if(auto n = std::dynamic_pointer_cast<BoolValue>(e->value)) {
            writeOp(n->v?OP_TRUE:OP_FALSE);
        } else if(auto n = std::dynamic_pointer_cast<StringValue>(e->value)) {
            writeConstant(OBJ_VAL(new ObjString(n->v)));
        }
    }
    void visitLogical(Logical *) {}
    void visitUnary(Unary *e) {
        e->right->accept(this);
        switch(e->op.type) {
            case BANG: writeOp(OP_NOT); break;
            case MINUS: writeOp(OP_NEGATE); break;
            default: error("compiler error visit non-binary expr.");
        }
    }
    void visitVariable(Variable *) {}

    void visitBlock(Block *) {}
    void visitExpression(Expression *s) {
        s->expression->accept(this);
    }
    void visitFunction(Function *) {}
    void visitReturn(Return *) {}
    void visitClass(Class *) {}
    void visitIf(If *) {}
    void visitPrint(Print *) {}
    void visitVar(Var *) {}
    void visitWhile(While *) {}
public:
    Chunk compile(std::vector<std::shared_ptr<Stmt>> stmts) {
        Chunk k;
        chunk = &k;
        for(const auto stmt: stmts) {
            stmt->accept(this);
        }
        currentLine++;
        writeOp(OP_RETURN);
        return k;
    }

    inline bool hasError() { return _hasError; }
};
}

#endif // _VM_COMPILER_H_