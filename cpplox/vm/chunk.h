#ifndef _VM_CHUNK_H_
#define _VM_CHUNK_H_

#include <cstddef>
#include <cstdint>
#include <memory>

#include "value.h"

namespace vm {

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

class Chunk {
    size_t count;
    size_t capacity;
    uint8_t *code;
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
    }
public:
    Chunk() : count(0), capacity(0), code(nullptr) {}
    Chunk(const Chunk &) = delete;
    Chunk(Chunk &&c) : count(c.count),
                       capacity(c.capacity),
                       code(c.code)
    {
        c.count = 0;
        c.capacity = 0;
        c.code = nullptr;
    }
    ~Chunk() {
        free(code);
        code = nullptr;
    }

    void write(uint8_t byte) {
        if(capacity<count+1) {
            grow();
        }
        code[count++] = byte;
    }
    const uint8_t &get(const size_t offset) const {
        return code[offset];
    }

    size_t addConstant(const Value value) {
        constants.write(value);
        return constants.getCount() - 1;
    }
    const Value getConstant(const size_t index) const {
        return constants.get(index);
    }

    friend std::ostream &operator<<(std::ostream &os, const Chunk &chunk);
    class Iterator
    {
    };
};

}

#endif // _VM_CHUNK_H_
