#ifndef _VM_OBJECT_H_
#define _VM_OBJECT_H_

#include <cstddef>

namespace vm {

typedef enum {
    OBJ_STRING,
} ObjType;

struct Obj {
    ObjType type;
};

#define OBJ_TYPE(v) (AS_OBJ(v)->type)

#define ALLOCATE(type, count) (type *)malloc(sizeof(type) * (count))

struct ObjString {
    Obj obj;
    size_t length;
    const char *chars;

    ObjString(const char *c, size_t len) {
        char *heapChars = ALLOCATE(char, len);
        memcpy(heapChars, c, len);
        obj.type = OBJ_STRING;
        length = len;
        chars =heapChars;
    }
    ObjString(const char *c): ObjString(c, strlen(c)) { }
    ~ObjString() {
        if (chars!=nullptr)
            free((void *)chars);
    }

    ObjString(const ObjString &) = delete;
    ObjString(ObjString && o) {
        printf("move constructor for ObjString %s\n", o.chars);
        obj = o.obj;
        length = o.length;
        chars = o.chars;
        o.chars = nullptr;
        o.length = 0;
    }
};

}

#endif // _VM_OBJECT_H_