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

    uint8_t makeConstant(const Value &value) {
        auto constant = chunk->addConstant(value);
        if (constant > UINT8_MAX) {
            error("Too many constants in on chunk.");
            return 0xFF;
        }
        return constant;
    }
    // emitConstant
    void writeConstant(const Value &value) {
        auto constant = makeConstant(value);
        chunk->write(OP_CONSTANT, currentLine);
        chunk->write(constant, currentLine);
        // chunk->writeConstant(value, currentLine);
    }
    uint8_t identifierConstant(const Token &name) {
        return makeConstant(OBJ_VAL(chunk->objMgr.NewString(name.lexeme)));
    }
    void defineVariable(const uint8_t global) {
        writeOp(OP_DEFINE_GLOBAL);
        chunk->write(global, currentLine);
    }

    // variable getter/setter; namedVariable
    void accessVariable(const OpCode op, const Token &name) {
        auto arg = identifierConstant(name); // string的常量使用了不同的常量index
        writeOp(op);
        chunk->write(arg, currentLine);
    }

    void writeOp(const OpCode op) {
        chunk->write(op, currentLine);
    }
    void writeOp(const OpCode op1, const OpCode op2) {
        writeOp(op1);
        writeOp(op2);
    }
public:
    void visitAssign(Assign *e) {
        currentLine = e->name.line;
        e->value->accept(this);
        accessVariable(OP_SET_GLOBAL, e->name);
    }
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
            // writeConstant(OBJ_VAL(new ObjString(n->v)));
            writeConstant(OBJ_VAL(chunk->objMgr.NewString(n->v))); // 常量的Object由chunk管理（属于代码段）
        }
    }
    void visitLogical(Logical *) {}
    void visitUnary(Unary *e) {
        currentLine = e->op.line;
        e->right->accept(this);
        switch(e->op.type) {
            case BANG: writeOp(OP_NOT); break;
            case MINUS: writeOp(OP_NEGATE); break;
            default: error("compiler error visit non-binary expr.");
        }
    }
    void visitVariable(Variable *e) {
        currentLine = e->name.line;
        accessVariable(OP_GET_GLOBAL, e->name);
    }

    void visitBlock(Block *) {}
    void visitExpression(Expression *s) {
        s->expression->accept(this);
        writeOp(OP_POP);
    }
    void visitFunction(Function *) {}
    void visitReturn(Return *) {}
    void visitClass(Class *) {}
    void visitIf(If *) {}
    void visitPrint(Print *s) {
        s->expression->accept(this);
        writeOp(OP_PRINT);
    }
    void visitVar(Var *s) {
        currentLine = s->name.line;
        if(s->initializer != nullptr) {
            s->initializer->accept(this);
        } else {
            writeOp(OP_NIL);
        }
        auto var = identifierConstant(s->name);
        defineVariable(var);
    }
    void visitWhile(While *) {}

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