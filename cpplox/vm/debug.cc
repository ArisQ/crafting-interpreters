#include "debug.h"

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
       << std::setfill(' ') << std::setw(4) << uint(constant) << " '"
       << chunk.getConstant(constant) << '\'' << std::endl;
    return offset + 2;
}

size_t disassembleInstruction(std::ostream &os, const Chunk &chunk, size_t offset)
{
    os << std::setfill('0') << std::setw(4) << offset << ' ';
    if(offset>0 && chunk.getLine(offset)==chunk.getLine(offset-1)) {
        os << "   | ";
    } else {
        os << std::setfill(' ') << std::setw(4) << chunk.getLine(offset) << ' ';
    }
    auto instruction = chunk.get(offset);
    switch (instruction)
    {
    case OP_CONSTANT: return constantInstruction(os, "OP_CONSTANT", chunk, offset);
    case OP_NIL: return simpleInstruction(os, "OP_NIL", offset);
    case OP_TRUE: return simpleInstruction(os, "OP_TRUE", offset);
    case OP_FALSE: return simpleInstruction(os, "OP_FALSE", offset);
    case OP_EQUAL: return simpleInstruction(os, "OP_EQUAL", offset);
    case OP_LESS: return simpleInstruction(os, "OP_LESS", offset);
    case OP_GREATER: return simpleInstruction(os, "OP_GREATER", offset);
    case OP_ADD: return simpleInstruction(os, "OP_ADD", offset);
    case OP_SUBSTRACT: return simpleInstruction(os, "OP_SUBSTRACT", offset);
    case OP_MULTIPLY: return simpleInstruction(os, "OP_MULTIPLY", offset);
    case OP_DIVIDE: return simpleInstruction(os, "OP_DIVIDE", offset);
    // unary
    case OP_NEGATE: return simpleInstruction(os, "OP_NEGATE", offset);
    case OP_NOT: return simpleInstruction(os, "OP_NOT", offset);
    case OP_PRINT: return simpleInstruction(os, "OP_PRINT", offset);
    case OP_POP: return simpleInstruction(os, "OP_POP", offset);
    case OP_DEFINE_GLOBAL: return constantInstruction(os, "OP_DEFINE_GLOBAL", chunk, offset);
    case OP_GET_GLOBAL: return constantInstruction(os, "OP_GET_GLOBAL", chunk, offset);
    case OP_SET_GLOBAL: return constantInstruction(os, "OP_SET_GLOBAL", chunk, offset);
    case OP_RETURN: return simpleInstruction(os, "OP_RETURN", offset);
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

std::ostream &operator<<(std::ostream &os, const ChunkDebugName &name) {
    os << "== "<< name.name <<" ==" << std::endl;
    return os;
}

}
