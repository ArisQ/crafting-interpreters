#include "object.h"
#include "chunk.h"

namespace vm {

ObjFunction::ObjFunction() : obj(OBJ_FUNCTION), arity(0), chunk(new Chunk()), name(nullptr) {}
ObjFunction::~ObjFunction() {
    auto n = "script";
    if (name != nullptr) n = name->chars;
    std::cout << "free func " << n <<std::endl;
    delete chunk;
}

}