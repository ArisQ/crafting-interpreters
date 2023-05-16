#ifndef _VM_OBJECT_MANAGER_H_
#define _VM_OBJECT_MANAGER_H_

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
    ObjFunction *NewFunction(const ObjString *name);
    ObjClosure *NewClosure(ObjFunction *function);
    ObjUpvalue *NewUpvalue(Value *value);
    ObjNative *NewNative(NativeFn function);

    virtual void mark() = 0;

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

    void registerOwner(ObjOwner *o) {
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
            }
            pre = p;
            p = p->next;
        }
        std::cout << "failed to unregister owner " << o <<" : not found"<< std::endl;
    }

    void collectGarbage();
    void markRoots();

public:
    ObjPool() : objects(nullptr) {}
    ~ObjPool() {
        printf("destruct obj pool\n");
        auto object = objects;
        while(object != nullptr) {
            auto next = object->next;
            switch (object->type) {
            case OBJ_STRING: {
                // 转成ObjString再删除，否则析构函数不会被调用
                // 参考多态情况下的虚析构函数
                auto str = (ObjString *)object;
                strings.remove(str);
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
            object = next;
        }
    }

    void insertObj(Obj *o) {
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
