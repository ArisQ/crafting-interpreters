#ifndef _VM_OBJECT_H_
#define _VM_OBJECT_H_

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

#include "config.h"
#include "table.h"

#ifdef DEBUG_LOG_GC
#include <map>
#endif

namespace vm {

typedef enum {
    OBJ_UNDEFINED,
    OBJ_STRING,
    OBJ_FUNCTION,
    OBJ_CLOSURE,
    OBJ_UPVALUE,
    OBJ_NATIVE,
    OBJ_CLASS,
    OBJ_INSTANCE,
    OBJ_BOUND_METHOD,
} ObjType;

#ifdef DEBUG_LOG_GC
static std::map<ObjType, std::string> objTypeStr{
    {OBJ_UNDEFINED, "OBJ_UNDEFINED"},
    {OBJ_STRING, "OBJ_STRING"},
    {OBJ_FUNCTION, "OBJ_FUNCTION"},
    {OBJ_CLOSURE, "OBJ_CLOSURE"},
    {OBJ_UPVALUE, "OBJ_UPVALUE"},
    {OBJ_NATIVE, "OBJ_NATIVE"},
};
static std::ostream &operator<<(std::ostream &os, ObjType t) {
    if (objTypeStr.contains(t))
        os << objTypeStr.at(t);
    else
        os << "object" << int(t);
    return os;
}
#endif

struct Obj;
std::ostream &operator<<(std::ostream &os, const Obj * const obj);


struct Obj {
    ObjType type;
    Obj *next;

    bool isMarked = false; // gc mark

    Obj(ObjType t) : type(t), next(nullptr) {
#ifdef DEBUG_LOG_GC
        // 构造时，子struct还未创建
        std::cout << "new " << t << " " << (void*)this << std::endl;
#endif
    }
    ~Obj() {
#ifdef DEBUG_LOG_GC
        std::cout << "free " << type << " " << (void*)this << std::endl;
#endif
    }
    void mark() {
#ifdef DEBUG_LOG_GC
        std::cout << (void *)this << " mark " << this << std::endl;
#endif
        isMarked = true;
    }
};

#define OBJ_TYPE(v) (AS_OBJ(v)->type)

#define ALLOCATE(type, count) (type *)malloc(sizeof(type) * (count))

struct ObjString {
    Obj obj;
    size_t length;
    const char *chars;

    uint32_t hash;

    ~ObjString() {
        if (chars!=nullptr) {
#ifdef DEBUG_LOG_GC
            fprintf(stderr, "free str %s\n", chars);
#endif
            free((void *)chars);
        }
    }

    ObjString(const ObjString &) = delete;
    ObjString(ObjString && o) = delete;
    // ObjString(ObjString && o) {
    //     printf("move constructor for ObjString %s\n", o.chars);
    //     obj = o.obj;
    //     length = o.length;
    //     chars = o.chars;
    //     o.chars = nullptr;
    //     o.length = 0;
    // }

    ObjString *operator+(const ObjString &r) {
        return new ObjString(this, &r);
    }

    friend class ObjMgr;
    friend class ObjOwner;

private:
    // 私有constructor，只有ObjMgr能够构造

    // new ObjString == copyString/allocateString
    ObjString(const char *c, size_t len) : obj(OBJ_STRING) {
        char *heapChars = ALLOCATE(char, len+1);
        memcpy(heapChars, c, len);
        heapChars[len] = '\0';
        length = len;
        chars =heapChars;
        buildHash();
    }
    // concatenate and takeString
    ObjString(const ObjString *const a, const ObjString *const b) : obj(OBJ_STRING) {
        int len = a->length + b->length;
        auto heapChars = ALLOCATE(char, len+1);
        memcpy(heapChars, a->chars, a->length);
        memcpy(heapChars + a->length, b->chars, b->length);
        heapChars[len] = '\0';
        length = len;
        chars = heapChars;
        buildHash();
    }
    ObjString(const char *c) : ObjString(c, strlen(c)) {}
    ObjString(const std::string &s) : ObjString(s.c_str(), s.size()) {} // used by compiler to convert from StringValue

    void buildHash() {
        // FNV-1a hash function
        hash = 2166136261u;
        for(int i=0;i <length;i++) {
            hash ^= chars[i];
            hash *= 16777619;
        }
    }
};

class Chunk;
struct ObjFunction {
    Obj obj;
    int arity;
    int upvalueCount;
    Chunk *chunk;
    const ObjString *name;

    ~ObjFunction();
private:
    ObjFunction();
    friend class ObjMgr;
    friend class ObjOwner;
};

struct Value;
typedef Value (*NativeFn) (int argCount, Value *args);
struct ObjNative {
    Obj obj;
    NativeFn function;
    ObjNative(NativeFn function) : obj(OBJ_NATIVE), function(function) {}
};

struct ObjUpvalue {
    Obj obj;
    Value *location;
    Value closed;
    ObjUpvalue *next;

    ObjUpvalue(Value *loc = nullptr);
    ~ObjUpvalue();
};

struct ObjClosure {
    Obj obj;
    ObjFunction *function;

    ObjUpvalue **upvalues;
    int upvalueCount;

    ObjClosure(ObjFunction *function) : obj(OBJ_CLOSURE), function(function) {
        upvalueCount=function->upvalueCount;
        upvalues = new ObjUpvalue*[upvalueCount];
        for(int i=0;i<upvalueCount;++i) {
            upvalues[i] = nullptr;
        }
    }
    ~ObjClosure() {
        delete[] upvalues;
    }
};

struct ObjClass {
    Obj obj;
    ObjString *name;
    Table methods;

    ObjClass(ObjString *name) : obj(OBJ_CLASS), name(name) {}
};

struct ObjInstance {
    Obj obj;
    ObjClass *klass;
    Table fields;

    ObjInstance(ObjClass *klass) : obj(OBJ_INSTANCE), klass(klass) {}
};

struct ObjBoundMethod {
    Obj obj;
    Value receiver;
    ObjClosure *method;

    ObjBoundMethod(Value &receiver, ObjClosure *method) : obj(OBJ_BOUND_METHOD), receiver(receiver), method(method) {}
};

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}
#define IS_STRING(v) isObjType(v, OBJ_STRING)
#define IS_FUNCTION(v) isObjType(v, OBJ_FUNCTION)
#define IS_CLOSURE(v) isObjType(v, OBJ_CLOSURE)
#define IS_NATIVE(v) isObjType(v, OBJ_NATIVE)
#define IS_CLASS(v) isObjType(v, OBJ_CLASS)
#define IS_INSTANCE(v) isObjType(v, OBJ_INSTANCE)
#define IS_BOUND_METHOD(v) isObjType(v, OBJ_BOUND_METHOD)
#define AS_STRING(v) ((ObjString*)AS_OBJ(v))
#define AS_CSTRING(v) (((ObjString*)AS_OBJ(v))->chars)
#define AS_FUNCTION(v) ((ObjFunction*)AS_OBJ(v))
#define AS_CLOSURE(v) ((ObjClosure*)AS_OBJ(v))
#define AS_NATIVE(v) (((ObjNative*)AS_OBJ(v))->function)
#define AS_CLASS(v) ((ObjClass*)AS_OBJ(v))
#define AS_INSTANCE(v) ((ObjInstance*)AS_OBJ(v))
#define AS_BOUND_METHOD(v) ((ObjBoundMethod*)AS_OBJ(v))

}

#endif // _VM_OBJECT_H_