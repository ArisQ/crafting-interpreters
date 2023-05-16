#ifndef _VM_OBJECT_H_
#define _VM_OBJECT_H_

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

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

struct Obj {
    ObjType type;
    Obj *next;

    bool isMarked = false; // gc mark

    Obj(ObjType t) : type(t), next(nullptr) {
#ifdef DEBUG_LOG_GC
        std::cout << "new " << t << " " << this << std::endl;
#endif
    }
    ~Obj() {
#ifdef DEBUG_LOG_GC
        std::cout << "free " << type << " " << this << std::endl;
#endif
    }
    void mark() {
        // if (obj == nullptr) return;
#ifdef DEBUG_LOG_GC
        std::cout << (void*)this <<" mark " << this << std::endl;
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
    int upvalueCount;
    Chunk *chunk;
    const ObjString *name;

    ~ObjFunction();
private:
    ObjFunction(const ObjString *name = nullptr);
    friend class ObjMgr;
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
    Value *closed;
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
    case OBJ_CLOSURE: {
        auto closure = (const ObjClosure*)obj;
        os << "closure " << (Obj*)closure->function;
        break;
    }
    case OBJ_UPVALUE: os << "upvalue"; break;
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