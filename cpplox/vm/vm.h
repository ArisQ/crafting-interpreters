#ifndef _VM_H_
#define _VM_H_

#include <cstdarg>

#include "chunk.h"
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

static const size_t STACK_MAX = 256;

class VM {
    const Chunk *chunk;
    uint8_t *ip; // instruction pointer or program counter
    Value stack[STACK_MAX];
    Value *stackTop;
    ObjMgr objMgr;
    Table globals;

    inline const uint8_t readByte() { return *ip++; }
    inline const uint16_t readShort() { return (readByte() << 8) + readByte(); }
    inline const Value readConstant() { return chunk->getConstant(readByte()); }
    inline const ObjString *readString() { return AS_STRING(readConstant()); }

    void resetStack() {}
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
        size_t instruction = ip - chunk->code -1;
        int line = chunk->lines[instruction];
        fprintf(stderr, "[line %d] in script\n", line);
        resetStack();
    }

    static inline bool isFalsey(const Value value) {
        return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value));
    }
public:
    // VM() { stackTop = stack; }
    InterpretResult interpret(const Chunk *k) {
        chunk = k;
        ip = k->code;
        stackTop = stack;
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
            disassembleInstruction(std::cout, *chunk, (size_t)(ip - chunk->code));
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
                push(stack[readByte()]);
                break;
            }
            case OP_SET_LOCAL: {
                stack[readByte()] = peek(0);
                break;
            }
            case OP_JUMP_IF_ELSE: {
                uint16_t offset = readShort();
                if (isFalsey(peek(0))) { // 不pop
                    ip += offset;
                }
                break;
            }
            case OP_JUMP: {
                uint16_t offset = readShort();
                ip += offset;
                break;
            }
            case OP_LOOP: {
                uint16_t offset = readShort();
                ip -= offset;
                break;
            }
            case OP_RETURN:
                return INTERPRET_OK;
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