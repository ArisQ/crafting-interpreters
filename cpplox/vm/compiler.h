#ifndef _VM_COMPILER_H_
#define _VM_COMPILER_H_

#include "chunk.h"

namespace vm {
class Compiler {
public:
    Chunk compile() {
        Chunk chunk;
        chunk.writeConstant(3.14, 2);
        chunk.writeConstant(1024, 2);
        chunk.write(OP_NEGATE, 2);
        chunk.write(OP_ADD, 2);
        chunk.write(OP_RETURN, 3);
        return chunk;
    }
};
}

#endif // _VM_COMPILER_H_