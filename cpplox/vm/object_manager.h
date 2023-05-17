#ifndef _VM_OBJECT_MANAGER_H_
#define _VM_OBJECT_MANAGER_H_

#include "config.h"
#include "object.h"
#include "table.h"

namespace vm {

class ObjPool;
class ObjOwner {
    friend class ObjPool;

    ObjOwner *next;
protected:
    ObjPool &pool;

    const ObjString *NewString(const ObjString *const a, const ObjString *const b);
    const ObjString *NewString(const std::string &s);
    // ObjFunction *NewFunction(const ObjString *name);
    ObjFunction *NewFunction();
    ObjClosure *NewClosure(ObjFunction *function);
    ObjUpvalue *NewUpvalue(Value *value);
    ObjNative *NewNative(NativeFn function);

    virtual void mark() = 0;

    void markObj(Obj *o);
    void markValue(Value &v);
public:
    ObjOwner(ObjPool &);
    ~ObjOwner();
};

// object pool
class ObjPool {
    friend class ObjOwner;

    Obj *objects;
    ObjOwner *owners = nullptr;
    static Table strings; // string interning

    int grayCount = 0;
    int grayCapacity = 0;
    Obj **grayStack = nullptr;

    size_t bytesAllocated = 0;
    size_t nextGC = 1024 * 1024;

    void registerOwner(ObjOwner *o) {
        std::cout << "register owner " << o << std::endl;
        auto pre = owners;
        o->next = pre;
        owners = o;
    }
    void unregisterOwner(ObjOwner *o) {
        ObjOwner *pre = nullptr;
        auto p = owners;
        while (p != nullptr) {
            if (p == o) {
                if(pre==nullptr) {
                    owners = p->next;
                } else {
                    pre->next=p->next;
                }
                return;
            }
            pre = p;
            p = p->next;
        }
        std::cout << "failed to unregister owner " << o <<" : not found"<< std::endl;
    }

    void collectGarbage();
    void markRoots();
    void traceReferences();
    void blackenObject(Obj *o);
    void sweep();

    void markObj(Obj *o);
    void markValue(Value &v);
    void markArray(ValueArray *a);
    void addGray(Obj *o);

    void freeObj(Obj *object) {
        bytesAllocated -= objSize(object);
        switch (object->type) {
        case OBJ_STRING: {
            // 转成ObjString再删除，否则析构函数不会被调用
            // 参考多态情况下的虚析构函数
            auto str = (ObjString *)object;
            strings.remove(str); // tableRemoveWhite here
            delete str;
            break;
        }
        case OBJ_FUNCTION: {
            auto func = (ObjFunction *)object;
            delete func;
            break;
        }
        case OBJ_NATIVE: {
            auto native = (ObjNative *)object;
            delete native;
            break;
        }
        default: break;
        }
    }
public:
    ObjPool() : objects(nullptr) {}
    ~ObjPool() {
        printf("destruct obj pool\n");
        free(grayStack);
        auto object = objects;
        while(object != nullptr) {
            auto next = object->next;
            freeObj(object);
            object = next;
        }
    }

    static size_t objSize(Obj *o) {
        switch (o->type) {
        case OBJ_STRING: return sizeof(ObjString) + ((ObjString *)o)->length * sizeof(char);
        case OBJ_FUNCTION: return sizeof(ObjFunction);
        case OBJ_CLOSURE: return sizeof(ObjClosure);
        case OBJ_UPVALUE: return sizeof(ObjUpvalue);
        case OBJ_NATIVE: return sizeof(ObjNative);
        default: return 0;
        }
    }

    void insertObj(Obj *o) {
        bytesAllocated += objSize(o);
        if (bytesAllocated > nextGC)
            collectGarbage();
        o->next = objects;
        objects = o; 
    }

    const ObjString *internedString(ObjString *str) {
        auto interned = strings.findString(str);
        if(interned!=nullptr) {
            delete str;
            return interned;
        }
        strings.set(str, NIL_VAL);
        insertObj((Obj*)str);
        return str;
    }
};

}

#endif // _VM_OBJECT_MANAGER_H_
