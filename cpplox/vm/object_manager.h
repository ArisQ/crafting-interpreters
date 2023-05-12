#ifndef _VM_OBJECT_MANAGER_H_
#define _VM_OBJECT_MANAGER_H_

#include "object.h"
#include "table.h"

namespace vm {

class ObjMgr {
    Obj *objects;

    static Table strings; // string interning

public:
    ObjMgr() : objects(nullptr) {}
    ~ObjMgr() {
        printf("destruct obj mgr\n");
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
            default: break;
            }
            object = next;
        }
    }

#define INSERT_OBJ(o) \
    auto obj = o; \
    obj->obj.next = objects; \
    objects = (Obj *)obj; \
    return obj;

    const ObjString *internedString(ObjString *str) {
        auto interned = strings.findString(str);
        if(interned!=nullptr) {
            delete str;
            return interned;
        }
        strings.set(str, NIL_VAL);
        INSERT_OBJ(str);
    }
    const ObjString *NewString(const ObjString *const a, const ObjString *const b) {
        return internedString(new ObjString(a, b));
    }
    const ObjString *NewString(const std::string &s) {
        return internedString(new ObjString(s));
    }
#undef INSERT_OBJ
};

}

#endif // _VM_OBJECT_MANAGER_H_
