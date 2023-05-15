#include "object.h"
#include "chunk.h"
#include "value.h"

namespace vm {

ObjFunction::ObjFunction(const ObjString *name) : obj(OBJ_FUNCTION), arity(0), chunk(new Chunk()), name(name), upvalueCount(0) {}

ObjFunction::~ObjFunction() {
    auto n = "script";
    if (name != nullptr) n = name->chars;
    std::cout << "free func " << n <<std::endl;
    delete chunk;
}

ObjUpvalue::ObjUpvalue(Value *loc) : obj(OBJ_UPVALUE), location(loc), next(nullptr), closed(nullptr) {}
ObjUpvalue::~ObjUpvalue() {
    if(closed!=nullptr) {
        delete closed;
    }
}

}