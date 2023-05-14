#ifndef _VM_H_
#define _VM_H_

#include <cstdarg>

#include "chunk.h"
#include "object_manager.h"
#include "debug.h"

#define DEBUG_TRACE_EXECUTION

#ifdef DEBUG_TRACE_EXECUTION
#include <iostream>
#endif

namespace vm {

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

static const size_t FRAMES_MAX = 64;
static const size_t STACK_MAX = (FRAMES_MAX * (UINT8_MAX + 1));

struct CallFrame {
    ObjFunction *function;
    uint8_t *ip;
    Value *slots; // pointer to stack frame base
};

class VM {
    CallFrame frames[FRAMES_MAX];
    int frameCount;
    CallFrame *frame;

    Value stack[STACK_MAX];
    Value *stackTop;
    ObjMgr &objMgr;
    Table globals;

    inline const uint8_t readByte() { return *frame->ip++; }
    inline const uint16_t readShort() { return (readByte() << 8) + readByte(); }
    inline const Value readConstant() { return frame->function->chunk->getConstant(readByte()); }
    inline const ObjString *readString() { return AS_STRING(readConstant()); }

    void resetStack() {
        stackTop = stack;
        frameCount = 0;
    }
    inline void push(Value value) { *stackTop++ = value; }
    inline Value pop() { return *--stackTop; }
    inline Value peek(int distance) { return stackTop[-1-distance]; }
    // inline void binaryOp(std::function<double(double,double)> op) {
    //     push(op(pop(), pop()));
    // }

    void runtimeError(const char* format, ...) {
        va_list args;
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);

        fputs("\n", stderr);
        for (int i = frameCount - 1; i >= 0; --i) {
            auto frame = &frames[i];
            auto function = frame->function;
            auto instruction = frame->ip - frame->function->chunk->code -1;
            fprintf(stderr, "[line %d] in ", function->chunk->lines[instruction]);
            if(function->name==nullptr) {
                fprintf(stderr, "scripts\n");
            } else {
                fprintf(stderr, "%s()\n",function->name->chars);
            }
        }
        resetStack();
    }

    static inline bool isFalsey(const Value value) {
        return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value));
    }

    bool callValue(Value callee, int argCount) {
        if(IS_OBJ(callee)) {
            switch (OBJ_TYPE(callee)) {
            case OBJ_FUNCTION: return call(AS_FUNCTION(callee), argCount);
            default: break;
            }
        }
        runtimeError("Can only call functions and classes.");
        return false;
    }
    bool call(ObjFunction *function, int argCount) {
        if(argCount!=function->arity) {
            runtimeError("Expect %d arguments but got %d.", function->arity, argCount);
            return false;
        }
        if(frameCount==FRAMES_MAX) {
            runtimeError("Stack overflow.");
            return false;
        }
        frame = &frames[frameCount++];
        frame->function = function;
        frame->ip = function->chunk->code;
        frame->slots = stackTop - argCount - 1;
        return true;
    }
public:
    VM(ObjMgr &objMgr) : objMgr(objMgr) { stackTop = stack; }
    InterpretResult interpret(ObjFunction *function) {
        resetStack();
        auto objFunc = OBJ_VAL(function);
        push(objFunc);
        callValue(objFunc, 0);
        return run();
    }
    InterpretResult run() {
// #define BINARY_OP(op) push(pop() op pop())
#define BINARY_OP(valueType, op)   \
    do {                \
        if(!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
            runtimeError("Operands must be number"); \
            return INTERPRET_RUNTIME_ERROR; \
        } \
        auto b = AS_NUMBER(pop()); \
        auto a = AS_NUMBER(pop()); \
        push(valueType(a op b));   \
    } while (false)

        for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
            std::cout << "          ";
            for (Value *slot = stack; slot < stackTop; slot++) {
                std::cout << "[ " << *slot << " ]";
            }
            std::cout << std::endl;
            disassembleInstruction(std::cout, *frame->function->chunk, (size_t)(frame->ip - frame->function->chunk->code));
#endif
            uint8_t instruction;
            switch (instruction=readByte()) {
            case OP_CONSTANT: {
                push(readConstant());
                break;
            }
            case OP_NIL: push(NIL_VAL); break;
            case OP_TRUE: push(BOOL_VAL(true)); break;
            case OP_FALSE: push(BOOL_VAL(false)); break;
            // case OP_ADD: binaryOp(std::plus<double>()); break;
            case OP_EQUAL: {
                auto b = pop();
                auto a = pop();
                push(BOOL_VAL(a==b)); // push(BOOL_VAL(valuesEqual(a, b)));
                break;
            }
            case OP_LESS: BINARY_OP(BOOL_VAL, <); break;
            case OP_GREATER: BINARY_OP(BOOL_VAL, >); break;
            case OP_ADD: {
                if(IS_STRING(peek(0)) && IS_STRING(peek(1))) {
                    auto b = AS_STRING(pop());
                    auto a = AS_STRING(pop());
                    push(OBJ_VAL(objMgr.NewString(a, b)));
                    // push(OBJ_VAL((*a) + (*b)));
                } else if(IS_NUMBER(peek(0)) && IS_NUMBER(peek(1))) {
                    auto b = AS_NUMBER(pop());
                    auto a = AS_NUMBER(pop());
                    push(NUMBER_VAL(a + b));
                } else {
                    runtimeError("Operands must be two numbers or two strings.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_SUBSTRACT: BINARY_OP(NUMBER_VAL, -); break;
            case OP_MULTIPLY: BINARY_OP(NUMBER_VAL, *); break;
            case OP_DIVIDE: BINARY_OP(NUMBER_VAL, /); break;
            case OP_NEGATE:
                if (!IS_NUMBER(peek(0))) {
                    runtimeError("Operand must be number.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                push(NUMBER_VAL(-AS_NUMBER(pop())));
                break;
            case OP_NOT:
                push(BOOL_VAL(isFalsey(pop())));
                break;
            case OP_PRINT:
                std::cout << pop() << std::endl;
                break;
            case OP_POP: pop(); break;
            case OP_DEFINE_GLOBAL: {
                auto name = readString();
                globals.set(name, peek(0));
                pop();
                break;
            }
            case OP_GET_GLOBAL: {
                auto name = readString();
                Value v;
                if(!globals.get(name, &v)) {
                    runtimeError("Undefined variable '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }
                push(v);
                break;
            }
            case OP_SET_GLOBAL: {
                auto name = readString();
                Value v;
                if(globals.set(name, peek(0))) {
                    // delete会产生tombstone，采用get&set?
                    // 大部分情况key都存在，不存在是异常，会返回runtime error
                    // 因此直接set比较好
                    globals.remove(name);
                    runtimeError("Undefined variable '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_GET_LOCAL: {
                push(frame->slots[readByte()]);
                break;
            }
            case OP_SET_LOCAL: {
                frame->slots[readByte()] = peek(0);
                break;
            }
            case OP_JUMP_IF_ELSE: {
                uint16_t offset = readShort();
                if (isFalsey(peek(0))) { // 不pop
                    frame->ip += offset;
                }
                break;
            }
            case OP_JUMP: {
                uint16_t offset = readShort();
                frame->ip += offset;
                break;
            }
            case OP_LOOP: {
                uint16_t offset = readShort();
                frame->ip -= offset;
                break;
            }
            case OP_CALL: {
                auto argCount = readByte();
                if(!callValue(peek(argCount), argCount)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_RETURN: {
                auto result = pop();
                --frameCount;
                if(frameCount == 0 ) {
                    pop();
                    return INTERPRET_OK;
                }
                stackTop = frame->slots;
                push(result);
                frame = &frames[frameCount - 1];
                break;
            }
            default:
                runtimeError("Invalid instruction %d", instruction);
                return INTERPRET_RUNTIME_ERROR;
            }
        }
    }
#undef BINARY_OP
};

}

#endif // _VM_H_