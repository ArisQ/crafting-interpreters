#ifndef _VM_VALUE_H_
#define _VM_VALUE_H_

#include <memory>

#include "object.h"

namespace vm {

typedef enum {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
    VAL_OBJ,
} ValueType;

typedef struct {
    ValueType type;
    union {
        bool boolean;
        double number;
        Obj *obj;
    } as;
} Value;

#define BOOL_VAL(v) ((Value){VAL_BOOL, {.boolean = v}})
#define NIL_VAL ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(v) ((Value){VAL_NUMBER, {.number = v}})
#define OBJ_VAL(v) ((Value){VAL_OBJ, {.obj = (Obj *)v}})

#define AS_BOOL(v) ((v).as.boolean)
#define AS_NUMBER(v) ((v).as.number)
#define AS_OBJ(v) ((v).as.obj)

#define IS_BOOL(v) ((v).type == VAL_BOOL)
#define IS_NIL(v) ((v).type == VAL_NIL)
#define IS_NUMBER(v) ((v).type == VAL_NUMBER)
#define IS_OBJ(v) ((v).type == VAL_OBJ)

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}
#define IS_STRING(v) isObjType(v, OBJ_STRING)
#define AS_STRING(v) ((ObjString*)AS_OBJ(v))
#define AS_CSTRING(v) (((ObjString*)AS_OBJ(v))->chars)


std::ostream &operator<<(std::ostream &os, const Value &v);
bool operator==(const Value l, const Value r);
bool valuesEqual(const Value l, const Value r);

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
