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
} ObjType;

struct Obj {
    ObjType type;
    Obj *next;
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
    ObjString(const char *c, size_t len) {
        char *heapChars = ALLOCATE(char, len+1);
        memcpy(heapChars, c, len);
        heapChars[len] = '\0';
        obj.type = OBJ_STRING;
        length = len;
        chars =heapChars;
        buildHash();
    }
    // concatenate and takeString
    ObjString(const ObjString *const a, const ObjString *const b) {
        int len = a->length + b->length;
        auto heapChars = ALLOCATE(char, len+1);
        memcpy(heapChars, a->chars, a->length);
        memcpy(heapChars + a->length, b->chars, b->length);
        heapChars[len] = '\0';
        obj.type = OBJ_STRING;
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

static std::ostream &operator<<(std::ostream &os, const Obj * const obj) {
    os << '*';
    switch (obj->type) {
    case OBJ_STRING: os << '"' << ((const ObjString *)(obj))->chars << '"'; break;
    default: os << "unknown object type " << obj->type; break;
    }
    return os;
}

}

#endif // _VM_OBJECT_H_