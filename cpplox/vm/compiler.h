#ifndef _VM_COMPILER_H_
#define _VM_COMPILER_H_

#include "../stmt.h"
#include "../expr.h"

#include "chunk.h"

namespace vm {

struct Local {
    Token name;
    int depth;
    Local() : name(Token(TOKEN_EOF, "", -1, nullptr)),
              depth(-1) {}
};

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
        writeOp(OP_CONSTANT);
        writeArg(constant);
        // chunk->writeConstant(value, currentLine);
    }
    uint8_t identifierConstant(const Token &name) {
        return makeConstant(OBJ_VAL(chunk->objMgr.NewString(name.lexeme)));
    }

    // variable getter/setter; namedVariable
    void accessVariable(const Token &name, const bool set = false) {
        OpCode op = set ? OP_SET_LOCAL : OP_GET_LOCAL;
        auto arg = resolveLocal(name);
        if (arg == -1) {
            op = set ? OP_SET_GLOBAL : OP_GET_GLOBAL;
            arg = identifierConstant(name); // NOTE: 同一global的名称string占用了多个常量index
        }
        writeOp(op);
        writeArg(arg);
    }

    void writeArg(const uint8_t arg) {
        chunk->write(arg, currentLine);
    }
    void writeOp(const OpCode op) {
        chunk->write(op, currentLine);
    }
    void writeOp(const OpCode op1, const OpCode op2) {
        writeOp(op1);
        writeOp(op2);
    }
    size_t writeJump(const OpCode op) {
        writeOp(op);
        writeArg(0xFF);
        writeArg(0xFF);
        return chunk->getCount() - 2;
    }
    void patchJump(const size_t offset) {
        // -2 to adjust for the bytecode for the jump offset itself
        auto jump = chunk->getCount() - offset - 2;
        if(jump>UINT16_MAX) {
            error("Too much code to jump over.");
        }
        chunk->writeAt(offset, (jump >> 8) & 0xFF);
        chunk->writeAt(offset + 1, jump & 0xFF);
    }

    // locals
    Local locals[UINT8_MAX + 1];
    size_t localCount = 0;
    int scopeDepth = 0;

    void beginScope() { ++scopeDepth; }
    void endScope() {
        --scopeDepth;
        while (localCount > 0 && locals[localCount - 1].depth > scopeDepth) {
            writeOp(OP_POP);
            --localCount;
        }
    }
    void addLocal(const Token &name) {
        // for (size_t i = localCount - 1; i >= 0; i--) { // unsigned>=0
        for (size_t i = localCount; i-- > 0;) {
            auto local = locals[i];
            if (local.depth != -1 && local.depth < scopeDepth) {
                break;
            }
            if (name.lexeme == local.name.lexeme) { // identifiersEqual
                error("Already variable with this name in this scope.");
                return;
            }
        }
        if (localCount > UINT8_MAX) {
            error("Too many local variable in function.");
            return;
        }
        auto &local = locals[localCount++];
        local.name = name;
        local.depth = -1;
    }
    void markInitialized() {
        locals[localCount-1].depth = scopeDepth;
    }
    size_t resolveLocal(const Token &name) {
        for (size_t i = localCount; i-- > 0;) {
            auto &local = locals[i];
            if (name.lexeme == local.name.lexeme) {
                if (local.depth == -1) {
                    error("Can't read local variable in its own initializer.");
                }
                return i;
            }
        }
        return -1;
    }

public:
    void visitAssign(Assign *e) {
        currentLine = e->name.line;
        e->value->accept(this);
        accessVariable(e->name, true);
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
    void visitLogical(Logical *e) {
        currentLine = e->op.line;
        e->left->accept(this);
        switch (e->op.type)
        {
        case AND: {
            int endJump = writeJump(OP_JUMP_IF_ELSE);
            writeOp(OP_POP);
            e->right->accept(this);
            patchJump(endJump);
            break;
        }
        case OR: {
            int elseJump = writeJump(OP_JUMP_IF_ELSE);
            int endJump = writeJump(OP_JUMP);
            patchJump(elseJump);
            writeOp(OP_POP);
            e->right->accept(this);
            patchJump(endJump);
            break;
        }
        default:
            error("invalid logical op");
            break;
        }
    }
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
        accessVariable(e->name);
    }

    void visitBlock(Block *s) {
        beginScope();
        for(const auto &stmt: s->statements) {
            stmt->accept(this);
        }
        endScope();
    }
    void visitExpression(Expression *s) {
        s->expression->accept(this);
        writeOp(OP_POP);
    }
    void visitFunction(Function *) {}
    void visitReturn(Return *) {}
    void visitClass(Class *) {}
    void visitIf(If *s) {
        s->condition->accept(this);
        auto thenJump = writeJump(OP_JUMP_IF_ELSE);
        writeOp(OP_POP); // OP_JUMP_IF_ELSE不pop condition结果，显式的pop
        s->thenBranch->accept(this);
        auto elseJump = writeJump(OP_JUMP);
        patchJump(thenJump);
        writeOp(OP_POP);
        if(s->elseBranch) {
            s->elseBranch->accept(this);
        }
        patchJump(elseJump);
    }
    void visitPrint(Print *s) {
        s->expression->accept(this);
        writeOp(OP_PRINT);
    }
    void visitVar(Var *s) {
        currentLine = s->name.line;

        if (scopeDepth > 0) {
            // declareVariable
            addLocal(s->name);
        }

        if(s->initializer != nullptr) {
            s->initializer->accept(this);
        } else {
            writeOp(OP_NIL);
        }

        if (scopeDepth > 0) {
            markInitialized();
            return;
        }

        // defineVariable/global
        auto var = identifierConstant(s->name);
        writeOp(OP_DEFINE_GLOBAL);
        writeArg(var);
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