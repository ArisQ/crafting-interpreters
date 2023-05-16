#include "vm.h"
#include "compiler.h"
#include "object_manager.h"

namespace vm {

Table ObjMgr::strings;

void ObjMgr::collectGarbage() {
#ifdef DEBUG_LOG_GC
    std::cout << "-- gc begin" << std::endl;
#endif
    markRoots();
#ifdef DEBUG_LOG_GC
    std::cout << "-- gc end" << std::endl;
#endif
}
void ObjMgr::markRoots() {
    for (auto slot = vm->stack; slot < vm->stackTop; ++slot) {
        slot->mark();
    }
    for (int i = 0; i < vm->frameCount; ++i) {
        ((Obj *)vm->frames[i].closure)->mark();
    }
    for (ObjUpvalue *v = vm->openUpvalues; v != nullptr; v = v->next) {
        ((Obj*)v)->mark();
    }
    // vm->globals.mark();
    // compiler->mark();
}
}
