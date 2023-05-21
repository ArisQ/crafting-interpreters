#include "debug.h"
#include "object.h"

namespace vm {

size_t simpleInstruction(std::ostream &os, const char *name, size_t offset)
{
    os << name << std::endl;
    return offset + 1;
}
size_t byteInstruction(std::ostream &os, const char *name, const Chunk &chunk, size_t offset) {
    uint8_t slot = chunk.get(offset + 1);
    os << std::setfill(' ') << std::setw(16) << std::left << name
       << std::setfill(' ') << std::setw(4) << uint(slot) << std::endl;
    return offset + 2;
}
size_t jumpInstruction(std::ostream &os, const char *name, const Chunk &chunk, size_t offset, int sign = 1) {
    uint8_t high = chunk.get(offset + 1);
    uint8_t low = chunk.get(offset + 2);
    uint16_t jump = (high << 8) + low;
    os << std::setfill(' ') << std::setw(16) << std::left << name
       << std::right
       << std::setfill('0') << std::setw(4) << uint(offset) << " -> "
       << std::setfill('0') << std::setw(4) << uint(offset + 3 + sign * jump)
       << std::endl;
    return offset + 3;
}
size_t constantInstruction(std::ostream &os, const char *name, const Chunk &chunk, size_t offset)
{
    uint8_t constant = chunk.get(offset + 1);
    os << std::setfill(' ') << std::setw(16) << std::left << name
       << std::setfill(' ') << std::setw(4) << uint(constant) << " '"
       << chunk.getConstant(constant) << '\'' << std::endl;
    return offset + 2;
}
size_t invokeInstruction(std::ostream &os, const char *name, const Chunk &chunk, size_t offset)
{
    uint8_t constant = chunk.get(offset + 1);
    uint8_t argCount = chunk.get(offset + 2);
    os << std::setfill(' ') << std::setw(16) << std::left << name
       << std::setfill(' ') << std::setw(4) << uint(constant) << " '"
       << chunk.getConstant(constant) << "' args: "
       << std::setfill(' ') << std::setw(4) << uint(argCount) << " '"
       << std::endl;
    return offset + 3;
}

size_t disassembleInstruction(std::ostream &os, const Chunk &chunk, size_t offset)
{
    os << std::setfill('0') << std::setw(4) << std::right << offset << ' ';
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
    case OP_DEFINE_GLOBAL: return constantInstruction(os, "OP_DEF_GLOBAL", chunk, offset);
    case OP_GET_GLOBAL: return constantInstruction(os, "OP_GET_GLOBAL", chunk, offset);
    case OP_SET_GLOBAL: return constantInstruction(os, "OP_SET_GLOBAL", chunk, offset);
    case OP_GET_LOCAL: return byteInstruction(os, "OP_GET_LOCAL", chunk, offset);
    case OP_SET_LOCAL: return byteInstruction(os, "OP_SET_LOCAL", chunk, offset);
    case OP_GET_UPVALUE: return byteInstruction(os, "OP_GET_UPVALUE", chunk, offset);
    case OP_SET_UPVALUE: return byteInstruction(os, "OP_SET_UPVALUE", chunk, offset);
    case OP_JUMP_IF_ELSE: return jumpInstruction(os, "OP_JUMP_IF_ELSE", chunk, offset);
    case OP_JUMP: return jumpInstruction(os, "OP_JUMP", chunk, offset);
    case OP_LOOP: return jumpInstruction(os, "OP_LOOP", chunk, offset, -1);
    case OP_CALL: return byteInstruction(os, "OP_CALL", chunk, offset);
    case OP_INVOKE: return invokeInstruction(os, "OP_INVOKE", chunk, offset);
    case OP_CLOSURE: {
        // return constantInstruction(os, "OP_CLOSURE", chunk, offset);
        ++offset;
        uint8_t constant = chunk.get(offset++);
        os << std::setfill(' ') << std::setw(16) << std::left << "OP_CLOSURE"
           << std::setfill(' ') << std::setw(4) << uint(constant) << " "
           << chunk.getConstant(constant) << std::endl;
        auto fn = AS_FUNCTION(chunk.getConstant(constant));
        for (int j = 0; j < fn->upvalueCount; ++j) {
            int isLocal = chunk.get(offset++);
            int index = chunk.get(offset++);
            os << std::setfill('0') << std::setw(4) << std::right << offset - 2 << ' '
               << "   |                     " << (isLocal ? "local" : "upvalue")
               << " " << index << std::endl;
        }
        return offset;
    }
    case OP_CLOSE_UPVALUE: return simpleInstruction(os, "OP_CLOSE_UPVALUE", offset);
    case OP_RETURN: return simpleInstruction(os, "OP_RETURN", offset);
    case OP_CLASS: return constantInstruction(os, "OP_CLASS", chunk, offset);
    case OP_METHOD: return constantInstruction(os, "OP_METHOD", chunk, offset);
    case OP_GET_PROPERTY: return constantInstruction(os, "OP_GET_PROPERTY", chunk, offset);
    case OP_SET_PROPERTY: return constantInstruction(os, "OP_SET_PROPERTY", chunk, offset);
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
