#ifndef _VM_COMPILER_H_
#define _VM_COMPILER_H_

#include "../stmt.h"
#include "../expr.h"

#include "config.h"
#include "debug.h"
#include "chunk.h"
#include "object_manager.h"

namespace vm {

typedef enum {
    TYPE_FUNCTION,
    TYPE_METHOD,
    TYPE_SCRIPT,
} FunctionType;

struct Local {
    std::string name;
    int depth;
    bool isCaptured;
    Local()
        : name(""),
          depth(-1),
          isCaptured(false) {}
};
struct Upvalue {
    bool isLocal;
    uint8_t index;
};

class Compiler: public ExprVisitor<void>, public StmtVisitor<void>, public ObjOwner {
    Compiler *enclosing = nullptr;

    ObjFunction *function;
    FunctionType type;
    Chunk *chunk;

    Token *klass = nullptr;

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
        return makeConstant(OBJ_VAL(NewString(name.lexeme)));
    }

    // variable getter/setter; namedVariable
    void accessVariable(const Token &name, const bool set = false) {
        OpCode op;
        auto arg = resolveLocal(name);
        if (arg != RESOLVE_NOT_FOUND) {
            op = set ? OP_SET_LOCAL : OP_GET_LOCAL;
        } else if ((arg = resolveUpvalue(name)) != RESOLVE_NOT_FOUND) {
            op = set ? OP_SET_UPVALUE : OP_GET_UPVALUE;
        } else {
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
    void writeLoop(const size_t offset) {
        writeOp(OP_LOOP);
        auto jump = chunk->getCount() - offset + 2;
        if(jump>UINT16_MAX) {
            error("Loop body too large.");
        }
        writeArg((jump >> 8) & 0xFF);
        writeArg(jump & 0xFF);
    }

    // locals
    Local locals[UINT8_MAX + 1];
    size_t localCount = 0;
    int scopeDepth = 0;
    void beginScope() { ++scopeDepth; }
    void endScope() {
        --scopeDepth;
        while (localCount > 0 && locals[localCount - 1].depth > scopeDepth) {
            if (locals[localCount - 1].isCaptured) {
                writeOp(OP_CLOSE_UPVALUE);
            } else {
                writeOp(OP_POP);
            }
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
            if (name.lexeme == local.name) { // identifiersEqual
                error("Already variable with this name in this scope.");
                return;
            }
        }
        if (localCount > UINT8_MAX) {
            error("Too many local variable in function.");
            return;
        }
        auto &local = locals[localCount++];
        local.name = name.lexeme;
        local.depth = -1;
    }
    void markInitialized() {
        // local, return if scopeDepth==0
        locals[localCount-1].depth = scopeDepth;
    }
    static constexpr size_t RESOLVE_NOT_FOUND = -1;
    size_t resolveLocal(const Token &name) {
        for (size_t i = localCount; i-- > 0;) {
            auto &local = locals[i];
            if (name.lexeme == local.name) {
                if (local.depth == -1) {
                    error("Can't read local variable in its own initializer.");
                }
                return i;
            }
        }
        return RESOLVE_NOT_FOUND;
    }

    // upvalue
    Upvalue upvalues[UINT8_MAX + 1];
    size_t resolveUpvalue(const Token &name) {
        if(enclosing==nullptr) return RESOLVE_NOT_FOUND;
        int local = enclosing->resolveLocal(name);
        if (local != RESOLVE_NOT_FOUND) {
            enclosing->locals[local].isCaptured = true;
            return addUpvalue(local, true);
        }
        int upvalue = enclosing->resolveUpvalue(name);
        if (upvalue != RESOLVE_NOT_FOUND) {
            return addUpvalue(upvalue, false);
        }
        return RESOLVE_NOT_FOUND;
    }
    size_t addUpvalue(uint8_t index, bool isLocal) {
        int upvalueCount = function->upvalueCount;
        // find existing
        for (int i = 0; i < upvalueCount; ++i) {
            auto upvalue = &upvalues[i];
            if (upvalue->index == index && upvalue->isLocal == isLocal) return i;
        }
        if (upvalueCount == (UINT8_MAX + 1)) {
            error("Too many closure variables in function");
            return 0;
        }
        upvalues[upvalueCount].isLocal = isLocal;
        upvalues[upvalueCount].index = index;
        return function->upvalueCount++;
    }

    // build function
    ObjFunction *buildFunction(Function *f) {
        beginScope();
        // parameter list
        if(f->params.size()>255) {
            error("Can't have more than 255 parameters.");
        }
        function->arity = f->params.size();
        for (const auto &p : f->params) {
            addLocal(p);
            markInitialized();
        }
        //body
        compile(f->body);
        endScope();
        return function;
    }

    void mark() {
        markObj((Obj*)function);
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
    void visitCall(Call *e) {
        e->callee->accept(this);
        auto argCount = e->arguments.size();
        if(argCount>=255) {
            error("Can't have more than 255 arguments.");
        }
        for (const auto &arg : e->arguments) {
            arg->accept(this);
        }
        writeOp(OP_CALL);
        writeArg(argCount);
    }
    void visitGet(Get *e) {
        currentLine = e->name.line;
        e->object->accept(this);
        auto name = identifierConstant(e->name);
        writeOp(OP_GET_PROPERTY);
        writeArg(name);
    }
    void visitSet(Set *e) {
        currentLine = e->name.line;
        e->object->accept(this);
        auto name = identifierConstant(e->name);
        e->value->accept(this);
        writeOp(OP_SET_PROPERTY);
        writeArg(name);
    }
    void visitThis(This *e) {
        currentLine = e->keyword.line;
        accessVariable(e->keyword);
    }
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
            writeConstant(OBJ_VAL(NewString(n->v))); // 常量的Object由chunk管理（属于代码段）
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
    void visitFunction(Function *s) {
        currentLine = s->name.line;
        if (klass == nullptr) emitFunction(s);
        else emitMethod(s);
    }
    void emitFunction(Function *s) {
        uint8_t var; //global var
        if (scopeDepth > 0) { // local
            addLocal(s->name); // declareVariable
            markInitialized();
        } else {
            var = identifierConstant(s->name);
        }

        // function(TYPE_FUNCTION);
        Compiler compiler(pool, TYPE_FUNCTION, s->name.lexeme);
        compiler.enclosing = this;
        compiler.currentLine = currentLine;
        auto f = compiler.buildFunction(s);
        writeOp(OP_CLOSURE);
        writeArg(makeConstant(OBJ_VAL(f)));
        for (int i = 0; i < f->upvalueCount; ++i) {
            writeArg(compiler.upvalues[i].isLocal?1:0);
            writeArg(compiler.upvalues[i].index);
        }

        if (scopeDepth == 0) { // global
            writeOp(OP_DEFINE_GLOBAL);
            writeArg(var);
        }
    }
    void emitMethod(Function *s) {
        accessVariable(*klass);
        auto name = identifierConstant(s->name);

        // method (TYPE_FUNCTION);
        Compiler compiler(pool, TYPE_METHOD, s->name.lexeme);
        compiler.enclosing = this;
        compiler.currentLine = currentLine;
        auto f = compiler.buildFunction(s);
        writeOp(OP_CLOSURE);
        writeArg(makeConstant(OBJ_VAL(f)));
        for (int i = 0; i < f->upvalueCount; ++i) {
            writeArg(compiler.upvalues[i].isLocal?1:0);
            writeArg(compiler.upvalues[i].index);
        }

        writeOp(OP_METHOD);
        writeArg(name);
        writeOp(OP_POP); // pop class name
    }
    void visitReturn(Return *s) {
        if (type == TYPE_SCRIPT) {
            error("Can't return from top-level code.");
        }
        if(s->value != nullptr) {
            s->value->accept(this);
        } else {
            writeOp(OP_NIL);
        }
        writeOp(OP_RETURN);
    }
    void visitClass(Class *s) {
        /*
            declareVariable: addLocal，全局变量直接返回
            defineVariable: 局部变量调用markInitialized，全局变量写入OP_DEFINE_GLOBAL
            markInitialized: 标记局部变量depth，全局变量直接返回
            identifierConstant: 增加string常量
        */
        currentLine = s->name.line;
        auto name = identifierConstant(s->name);
        if (scopeDepth > 0) {                      // local
            addLocal(s->name); // declareVariable
        }
        writeOp(OP_CLASS);
        writeArg(name);

        if (scopeDepth > 0) {
            markInitialized();
        } else {
            writeOp(OP_DEFINE_GLOBAL);
            writeArg(name);
        }

        klass = &s->name;
        for (auto &m : s->methods) {
            m->accept(this);
        }
        klass = nullptr;
    }
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
    void visitWhile(While *s) {
        auto loopStart = chunk->getCount();
        s->condition->accept(this);
        auto exitJump = writeJump(OP_JUMP_IF_ELSE);
        writeOp(OP_POP);
        s->body->accept(this);
        writeLoop(loopStart);
        patchJump(exitJump);
        writeOp(OP_POP);
    }

    Compiler(ObjPool &objPool, FunctionType type = TYPE_SCRIPT, const std::string &name = "") : ObjOwner(objPool), function(nullptr) {
        // 需要先初始化为nullptr再NewFuntion
        // 否则NewFunction的时候，compiler会mark未知的function
        function = NewFunction();

        // name string需要在function后创建
        // 否则创建function时，gc会回收name
        if (type != TYPE_SCRIPT) {
            // name string需要在function前创建
            // 否则ObjPool析构的时候会先析构string，导致function中的name指向无效，function析构时输出的函数名不正确
            // 先不管析构，先创建function，以后可以优化为先创建string且mark时保持，或者ObjPool析构时处理依赖关系
            function->name = NewString(name);
        }
        type = type;
        chunk = function->chunk;

        auto &local = locals[localCount++];
        local.depth = 0;
        local.name = "";
        local.isCaptured = false;
        if (type == TYPE_METHOD) {
            local.name = "this";
        }
    }

    ObjFunction *compile(std::vector<std::shared_ptr<Stmt>> stmts) {
        for(const auto stmt: stmts) {
            stmt->accept(this);
        }
        currentLine++;
        writeOp(OP_NIL);
        writeOp(OP_RETURN);
#ifdef DEBUG_PRINT_CODE
        std::cout << ChunkDebugName(function->name == nullptr ? "<script>" : function->name->chars) << *chunk << std::endl;
#endif
        return function;
    }

    inline bool hasError() { return _hasError; }
};
}

#endif // _VM_COMPILER_H_