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
void ObjOwner::markTable(Table &t) {
    pool.markTable(t);
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
ObjClass *ObjOwner::NewClass(ObjString *name) {
    auto klass = new ObjClass(name);
    pool.insertObj((Obj *)klass);
    return klass;
}
ObjInstance *ObjOwner::NewInstance(ObjClass *klass) {
    auto instance = new ObjInstance(klass);
    pool.insertObj((Obj *)instance);
    return instance;
}
ObjBoundMethod *ObjOwner::NewBoundMethod(Value &receiver, ObjClosure *method) {
    auto bm = new ObjBoundMethod(receiver, method);
    pool.insertObj((Obj*)bm);
    return bm;
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
#ifdef DEBUG_LOG_GC
    std::cout << "trace reference" << std::endl;
#endif
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
        markValue(upvalue->closed);
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
    case OBJ_CLASS: {
        auto klass = (ObjClass*)o;
        markObj((Obj *)klass->name);
        markTable(klass->methods);
        break;
    }
    case OBJ_INSTANCE: {
        auto instance = (ObjInstance*)o;
        markObj((Obj *)instance->klass);
        markTable(instance->fields);
        break;
    }
    case OBJ_BOUND_METHOD: {
        auto method = (ObjBoundMethod*)o;
        markValue(method->receiver);
        markObj((Obj *)method->method);
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
void ObjPool::markTable(Table &t) {
    for (int i = 0; i <= t.capacityMask; ++i) {
        auto entry = &(t.entries)[i];
        markObj((Obj *)entry->key);
        markValue(entry->value);
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
