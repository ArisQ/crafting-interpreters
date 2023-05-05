#ifndef _VM_DEBUG_H_
#define _VM_DEBUG_H_

#include <ostream>
#include <iomanip>

#include "chunk.h"

namespace vm {

size_t simpleInstruction(std::ostream &os, const char *name, size_t offset)
{
    os << name << std::endl;
    return offset + 1;
}
size_t constantInstruction(std::ostream &os, const char *name, const Chunk &chunk, size_t offset)
{
    uint8_t constant = chunk.get(offset + 1);
    os << name << " "
       << std::setfill(' ') << std::setw(4) << constant << " '"
       << chunk.getConstant(constant) << '\'' << std::endl;
    return offset + 2;
}

size_t disassembleInstruction(std::ostream &os, const Chunk &chunk, size_t offset)
{
    os << std::setfill('0') << std::setw(4) << offset << ' ';
    auto instruction = chunk.get(offset);
    switch (instruction)
    {
    case OP_CONSTANT:
        return constantInstruction(os, "OP_CONSTANT", chunk, offset);
    case OP_RETURN:
        return simpleInstruction(os, "OP_RETURN", offset);
    default:
        os << "Unknown opcode " << instruction << std::endl;
        return offset + 1;
    }
}

std::ostream &operator<<(std::ostream &os, const Chunk &chunk) {
    for (size_t offset = 0; offset < chunk.count;) {
        offset = disassembleInstruction(os, chunk, offset);
    }
    return os;
}

class ChunkDebugName {
public:
    const char *name;
    ChunkDebugName(const char *name): name(name) {}
};

std::ostream &operator<<(std::ostream &os, const ChunkDebugName &name) {
    os << "== "<< name.name <<" ==" << std::endl;
    return os;
}

}

#endif // _DEBUG_H_