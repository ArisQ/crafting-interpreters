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

const ObjString *ObjOwner::NewString(const ObjString *const a, const ObjString *const b) {
    return pool.internedString(new ObjString(a, b));
}
const ObjString *ObjOwner::NewString(const std::string &s) {
    return pool.internedString(new ObjString(s));
}
ObjFunction *ObjOwner::NewFunction(const ObjString *name) {
    auto func = new ObjFunction(name);
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
#endif
    markRoots();
#ifdef DEBUG_LOG_GC
    std::cout << "-- gc end" << std::endl;
#endif
}
void ObjPool::markRoots() {
    // for (auto slot = vm->stack; slot < vm->stackTop; ++slot) {
    //     slot->mark();
    // }
    // for (int i = 0; i < vm->frameCount; ++i) {
    //     ((Obj *)vm->frames[i].closure)->mark();
    // }
    // for (ObjUpvalue *v = vm->openUpvalues; v != nullptr; v = v->next) {
    //     ((Obj*)v)->mark();
    // }
    // vm->globals.mark();
    // compiler->mark();
}
}
