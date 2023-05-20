#include "object.h"
#include "chunk.h"
#include "value.h"

namespace vm {

ObjFunction::ObjFunction() : obj(OBJ_FUNCTION), arity(0), chunk(new Chunk()), name(nullptr), upvalueCount(0) {}

ObjFunction::~ObjFunction() {
    auto n = "script";
    if (name != nullptr) n = name->chars;
    std::cout << "free func " << n <<std::endl;
    delete chunk;
}

ObjUpvalue::ObjUpvalue(Value *loc) : obj(OBJ_UPVALUE), location(loc), next(nullptr), closed(NIL_VAL) {}
ObjUpvalue::~ObjUpvalue() {}

std::ostream &operator<<(std::ostream &os, const Obj * const obj) {
    os << '*';
    switch (obj->type) {
    case OBJ_STRING: os << '"' << ((const ObjString *)(obj))->chars << '"'; break;
    case OBJ_FUNCTION: {
        auto func = (const ObjFunction *)obj;
        if (func->name==nullptr){
            os << "<script>";
        } else {
            os << "<fn " << func->name->chars << ">";
        }
        break;
    }
    case OBJ_CLOSURE: {
        auto closure = (const ObjClosure*)obj;
        os << "closure " << (Obj*)closure->function;
        break;
    }
    case OBJ_UPVALUE: os << "upvalue"; break;
    case OBJ_NATIVE: {
        os << "<native fn>";
        break;
    }
    case OBJ_CLASS: {
        os << "<class "<< ((ObjClass*)obj)->name->chars << ">";
        break;
    }
    case OBJ_INSTANCE: {
        os << "<"<< ((ObjInstance*)obj)->klass->name->chars << " instance>";
        break;
    }
    case OBJ_BOUND_METHOD: {
        auto bound = ((ObjBoundMethod *)obj);
        auto klass = "";
        if(IS_INSTANCE(bound->receiver)) {
            klass = AS_INSTANCE(bound->receiver)->klass->name->chars;
        }
        os << "<" << klass << "::" << bound->method->function->name->chars << " bound method>";
        break;
    }
    default: os << "unknown object type " << obj->type; break;
    }
    return os;
}

}