#ifndef _VM_CHUNK_H_
#define _VM_CHUNK_H_

#include <cstddef>
#include <cstdint>
#include <memory>

#include "value.h"

namespace vm {

typedef enum {
    OP_CONSTANT,
    OP_NIL,
    OP_TRUE,
    OP_FALSE,
    OP_NEGATE,
    OP_NOT,
    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_ADD,
    OP_SUBSTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,

    OP_POP,
    OP_PRINT,
    OP_DEFINE_GLOBAL,
    OP_GET_GLOBAL,
    OP_SET_GLOBAL,
    OP_GET_LOCAL,
    OP_SET_LOCAL,
    OP_JUMP_IF_ELSE,
    OP_JUMP,
    OP_LOOP,
    OP_CALL,
    OP_RETURN,
} OpCode;

class Chunk {
    size_t count;
    size_t capacity;
    uint8_t *code;
    int *lines;
    ValueArray constants;

    static const auto elementSize = sizeof(uint8_t);
    // static void *reallocate(void *ptr, size_t oldSize, size_t newSize) {
    //     if(newSize==0) {
    //         free(ptr);
    //         return nullptr;
    //     }
    //     auto result = realloc(ptr, newSize);
    //     return result;
    // }

    void grow() {
        capacity = (capacity<8) ? 8 : (capacity<<1);

        code = static_cast<uint8_t*>(realloc(code, elementSize*capacity));
        if (code==nullptr)
            throw std::runtime_error("reallocate chunk failed.");

        lines = static_cast<int*>(realloc(lines, sizeof(int)*capacity));
        if (lines==nullptr)
            throw std::runtime_error("reallocate lines failed.");
    }
public:
    Chunk() : count(0), capacity(0), code(nullptr), lines(nullptr) {}
    Chunk(const Chunk &) = delete;
    Chunk(Chunk &&c) : count(c.count),
                       capacity(c.capacity),
                       code(c.code),
                       lines(c.lines)
    {
        c.count = 0;
        c.capacity = 0;
        c.code = nullptr;
        c.lines = nullptr;
    }
    ~Chunk() {
        free(code);
        free(lines);
        code = nullptr;
        lines = nullptr;
    }

    void write(uint8_t byte, int line) {
        if(capacity<count+1) {
            grow();
        }
        code[count] = byte;
        lines[count] = line;
        count++;
    }
    void writeAt(size_t offset, uint8_t byte) {
        code[offset] = byte;
    }
    inline const uint8_t get(const size_t offset) const {
        return code[offset];
    }
    inline const int getLine(const size_t offset) const {
        return lines[offset];
    }

    size_t addConstant(const Value value) {
        constants.write(value);
        return constants.getCount() - 1;
    }
    inline const Value getConstant(const size_t index) const {
        return constants.get(index);
    }

    void writeConstant(const Value value, int line) {
        write(OP_CONSTANT, line);
        write(addConstant(value), line);
    }

    size_t getCount() { return count; }

    friend std::ostream &operator<<(std::ostream &os, const Chunk &chunk);
    friend class VM;
    class Iterator
    {
    };
};

}

#endif // _VM_CHUNK_H_
