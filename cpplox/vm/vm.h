#ifndef _VM_H_
#define _VM_H_

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

    inline const uint8_t readByte() { return *ip++; }
    inline const Value readConstant() { return chunk->getConstant(readByte()); }

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
#define BINARY_OP(op)   \
    do {                \
        auto b = pop(); \
        auto a = pop(); \
        push(a op b);   \
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
            // case OP_ADD: binaryOp(std::plus<double>()); break;
            // case OP_ADD: BINARY_OP(+); break;
            // case OP_SUBSTRACT: BINARY_OP(-); break;
            // case OP_MULTIPLY: BINARY_OP(*); break;
            // case OP_DIVIDE: BINARY_OP(/); break;
            // case OP_NEGATE: push(-pop()); break;
            case OP_NEGATE:
                if (!IS_NUMBER(peek(0))) {
                    runtimeError("Operand must be number.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                push(NUMBER_VAL(-AS_NUMBER(pop())));
                break;
            case OP_RETURN: {
                auto ret = pop();
#ifdef DEBUG_TRACE_EXECUTION
                std::cout << ret << std::endl;
#endif
                return INTERPRET_OK;
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