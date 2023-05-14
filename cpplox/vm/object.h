#ifndef _VM_OBJECT_H_
#define _VM_OBJECT_H_

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

namespace vm {

typedef enum {
    OBJ_UNDEFINED,
    OBJ_STRING,
    OBJ_FUNCTION,
    OBJ_NATIVE,
} ObjType;

struct Obj {
    ObjType type;
    Obj *next;

    Obj(ObjType t) : type(t), next(nullptr) {}
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
            fprintf(stderr, "free %s\n", chars);
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
    Chunk *chunk;
    const ObjString *name;

    ~ObjFunction();
private:
    ObjFunction();
    friend class ObjMgr;
};

struct Value;
typedef Value (*NativeFn) (int argCount, Value *args);
struct ObjNative {
    Obj obj;
    NativeFn function;
    ObjNative(NativeFn function) : obj(OBJ_NATIVE), function(function) {}
};

static std::ostream &operator<<(std::ostream &os, const Obj * const obj) {
    os << '*';
    switch (obj->type) {
    case OBJ_STRING: os << '"' << ((const ObjString *)(obj))->chars << '"'; break;
    case OBJ_FUNCTION: {
        auto func = (const ObjFunction *)obj;
        if (func->name==nullptr){
            os << "<script>";
        } else {
            os << "<fn " << func->name->chars << ">";
        }
        break;
    }
    case OBJ_NATIVE: {
        os << "<native fn>";
        break;
    }
    default: os << "unknown object type " << obj->type; break;
    }
    return os;
}

}

#endif // _VM_OBJECT_H_