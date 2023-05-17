#include "vm.h"
#include "compiler.h"
#include "object_manager.h"

namespace vm {

ObjOwner::ObjOwner(ObjPool &pool) : pool(pool) {
    pool.registerOwner(this);
}
ObjOwner::~ObjOwner() {
    pool.unregisterOwner(this);
}
void ObjOwner::markObj(Obj *o) {
    pool.markObj(o);
}
void ObjOwner::markValue(Value &v) {
    pool.markValue(v);
}

const ObjString *ObjOwner::NewString(const ObjString *const a, const ObjString *const b) {
    return pool.internedString(new ObjString(a, b));
}
const ObjString *ObjOwner::NewString(const std::string &s) {
    return pool.internedString(new ObjString(s));
}
ObjFunction *ObjOwner::NewFunction() {
    auto func = new ObjFunction();
    pool.insertObj((Obj *)func);
    return func;
}
ObjClosure *ObjOwner::NewClosure(ObjFunction *function) {
    auto closure = new ObjClosure(function);
    pool.insertObj((Obj*)closure);
    return closure;
}
ObjUpvalue *ObjOwner::NewUpvalue(Value *value) {
    auto upvalue = new ObjUpvalue(value);
    pool.insertObj((Obj*)upvalue);
    return upvalue;
}
ObjNative *ObjOwner::NewNative(NativeFn function) {
    auto native = new ObjNative(function);
    pool.insertObj((Obj*)native);
    return native;
}


Table ObjPool::strings;

void ObjPool::collectGarbage() {
#ifdef DEBUG_LOG_GC
    std::cout << "-- gc begin" << std::endl;
    size_t before = bytesAllocated;
#endif
    markRoots();
    traceReferences();
    sweep();
    nextGC = bytesAllocated * 2; // GC_HEAP_GROW_FACTOR=2
#ifdef DEBUG_LOG_GC
    std::cout << "-- gc end" << std::endl;
    std::cout << "   collect " << before - bytesAllocated
              << " bytes (from " << before
              << " to " << bytesAllocated
              << ") next at " << nextGC << std::endl;
#endif
}

void ObjPool::markRoots() {
    auto p = owners;
    while (p != nullptr) {
        p->mark();
        p = p->next;
    }
}

void ObjPool::traceReferences() {
    std::cout << "trace reference" << std::endl;
    while(grayCount>0) {
        Obj *obj = grayStack[--grayCount];
        // std::cout<<obj<< std::endl;
        blackenObject(obj);
    }
}
void ObjPool::blackenObject(Obj *o) {
#ifdef DEBUG_LOG_GC
    std::cout << (void *)o << " blacken " << o << std::endl;
#endif
    switch (o->type)
    {
    case OBJ_NATIVE:
    case OBJ_STRING:
        break;
    case OBJ_UPVALUE: {
        auto upvalue = (ObjUpvalue *)o;
        // upvalue的closed是指针，未closed时可能是nullptr
        if (upvalue->closed != nullptr) {
            markValue(*upvalue->closed);
        }
        break;
    }
    case OBJ_FUNCTION: {
        auto fn = (ObjFunction*)o;
        markObj((Obj*)fn->name);
        markArray(&fn->chunk->constants);
        break;
    }
    case OBJ_CLOSURE: {
        auto closure = (ObjClosure*)o;
        markObj((Obj*)closure->function);
        for(int i=0;i<closure->upvalueCount;i++) {
            markObj((Obj*)closure->upvalues[i]);
        }
        break;
    }
    default:
        break;
    }
}
void ObjPool::sweep() {
#ifdef DEBUG_LOG_GC
    std::cout << "sweep" << std::endl;
#endif
    Obj* pre = nullptr;
    Obj* obj = objects;
    while(obj!=nullptr) {
        if(obj->isMarked) {
            obj->isMarked = false;
            pre = obj;
            obj = obj->next;
        } else {
            auto unreached = obj;
            obj = obj->next;
            if (pre != nullptr) {
                pre->next = obj;
            } else {
                objects = obj;
            }
            freeObj(unreached);
        }
    }
}

void ObjPool::markObj(Obj *o) {
    if (o == nullptr) return;
    if (o->isMarked) return;
    o->mark();
    addGray(o);
}
void ObjPool::markValue(Value &v) {
    if (!IS_OBJ(v)) return;
    markObj(AS_OBJ(v));
}
void ObjPool::markArray(ValueArray *a) {
    for(int i =0;i<a->count;i++) {
        markValue(a->values[i]);
    }
}
void ObjPool::addGray(Obj *o) {
    if (grayCapacity < grayCount + 1) {
        grayCapacity = grayCapacity < 8 ? 8 : (grayCapacity << 1);
        grayStack = (Obj **)realloc(grayStack, sizeof(Obj *) * grayCapacity);
        if (grayStack == nullptr)
        {
            exit(1); // realloc failed
        }
    }
    grayStack[grayCount++] = o;
}
}
