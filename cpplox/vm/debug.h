#ifndef _VM_DEBUG_H_
#define _VM_DEBUG_H_

#include <ostream>
#include <iomanip>

#include "config.h"
#include "chunk.h"

namespace vm {

size_t simpleInstruction(std::ostream &os, const char *name, size_t offset);
size_t constantInstruction(std::ostream &os, const char *name, const Chunk &chunk, size_t offset);
size_t disassembleInstruction(std::ostream &os, const Chunk &chunk, size_t offset);
std::ostream &operator<<(std::ostream &os, const Chunk &chunk);

class ChunkDebugName {
public:
    const char *name;
    ChunkDebugName(const char *name): name(name) {}
};
std::ostream &operator<<(std::ostream &os, const ChunkDebugName &name);

}

#endif // _DEBUG_H_