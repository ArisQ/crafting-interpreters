#ifndef _VM_VALUE_H_
#define _VM_VALUE_H_

#include <memory>
#include <cstring>

#include "config.h"

namespace vm {

typedef enum {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
    VAL_OBJ,
} ValueType;

struct Obj;

#ifdef NAN_BOXING

#define QNAN      ((uint64_t)0x7ffc000000000000)
#define SIGN_BIT  ((uint64_t)0x8000000000000000)
#define TAG_NIL   ((uint64_t)0b01)
#define TAG_FALSE ((uint64_t)0b10)
#define TAG_TRUE  ((uint64_t)0b11)

typedef uint64_t Value;

static inline Value numToValue(double num) {
    Value value;
    memcpy(&value, &num, sizeof(double));
    return value;
    // union {
    //     Value bits;
    //     double num;
    // } data;
    // data.num = num;
    // return data.bits;
}
static inline double valueToNum(Value value) {
    double num;
    memcpy(&num, &value, sizeof(Value));
    return num;
}

#define NIL_VAL     ((Value)(QNAN | TAG_NIL))
#define FALSE_VAL   ((Value)(QNAN | TAG_FALSE))
#define TRUE_VAL    ((Value)(QNAN | TAG_TRUE))
#define BOOL_VAL(v) ((v) ? TRUE_VAL : FALSE_VAL)

#define NUMBER_VAL(v) numToValue(v)
#define OBJ_VAL(v)    ((Value)(SIGN_BIT | QNAN | (uint64_t)(uintptr_t)(v)))

#define AS_BOOL(v)   ((v) == TRUE_VAL)
#define AS_NUMBER(v) valueToNum(v)
#define AS_OBJ(v)    ((Obj *)((v) & ~(SIGN_BIT | QNAN)))

#define IS_BOOL(v)   (((v) | 1) == TRUE_VAL)
#define IS_NIL(v)    ((v) == NIL_VAL)
#define IS_NUMBER(v) (((v)&QNAN) != QNAN)
#define IS_OBJ(v)    (((v) & (QNAN | SIGN_BIT)) == (QNAN | SIGN_BIT))

#else
struct Value {
    ValueType type;
    union {
        bool boolean;
        double number;
        Obj *obj;
    } as;

    void mark();
};

#define BOOL_VAL(v) ((Value){VAL_BOOL, {.boolean = (v)}})
#define NIL_VAL ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(v) ((Value){VAL_NUMBER, {.number = (v)}})
#define OBJ_VAL(v) ((Value){VAL_OBJ, {.obj = (Obj *)(v)}})

#define AS_BOOL(v) ((v).as.boolean)
#define AS_NUMBER(v) ((v).as.number)
#define AS_OBJ(v) ((v).as.obj)

#define IS_BOOL(v) ((v).type == VAL_BOOL)
#define IS_NIL(v) ((v).type == VAL_NIL)
#define IS_NUMBER(v) ((v).type == VAL_NUMBER)
#define IS_OBJ(v) ((v).type == VAL_OBJ)

bool operator==(const Value l, const Value r);
#endif

class ValuePrinter {
    Value v;
public:
    ValuePrinter(Value v) : v(v) {}
    friend std::ostream &operator<<(std::ostream &os, const ValuePrinter &p);
};
// std::ostream &operator<<(std::ostream &os, const ValuePrinter &v);

class ValueArray {
    friend class ObjPool;

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
