#ifndef _VM_VALUE_H_
#define _VM_VALUE_H_

#include <memory>

namespace vm {

typedef double Value;

class ValueArray {
    int capacity;
    int count;
    Value *values;

    static const auto elementSize = sizeof(Value);
    void grow() {
        capacity = (capacity<8) ? 8 : (capacity<<1);
        values = static_cast<Value*>(realloc(values, elementSize*capacity));
        if (values==nullptr)
            throw std::runtime_error("reallocate value array failed.");
    }
public:
    ValueArray() : count(0), capacity(0), values(nullptr) {}
    ValueArray(const ValueArray &) = delete;
    ValueArray(ValueArray &&c) : count(c.count),
                       capacity(c.capacity),
                       values(c.values)
    {
        c.count = 0;
        c.capacity = 0;
        c.values = nullptr;
    }
    ~ValueArray() {
        free(values);
        values = nullptr;
    }

    void write(Value value) {
        if(capacity<count+1) {
            grow();
        }
        values[count++] = value;
    }
    inline const Value get(const size_t offset) const {
        return values[offset];
    }
    inline const size_t getCount() const {
        return count;
    }
};


}

#endif // _VM_VALUE_H_
