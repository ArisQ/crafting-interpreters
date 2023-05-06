#include <sysexits.h>

#include <iostream>

#define DEBUG_TRACE_EXECUTION

#include "lox.h"
#include "vm/vm.h"
#include "vm/chunk.h"
#include "vm/debug.h"

using namespace std;
using namespace vm;

int main(int argc, char *argv[])
{
    cout << "lox implemented by c++!" << endl;
    // unsaved

    Chunk chunk;
    chunk.writeConstant(3.14, 2);
    chunk.writeConstant(1024, 2);
    chunk.write(OP_NEGATE, 2);
    chunk.write(OP_ADD, 2);
    chunk.write(OP_RETURN, 3);
    cout << ChunkDebugName("test chunk") << chunk << endl;

    VM vm(chunk);
    vm.run();
    return 0;

    Lox lox;
    if (argc > 2)
    {
        cout << "Usage: cpplox [script]";
        return EX_USAGE;
    }
    else if (argc == 2)
    {
        return lox.runFile(string(argv[1]));
    }
    else
    {
        // return lox.runFile("../1.lox");
        // return lox.runFile("1.lox");
        return lox.runPrompt();
    }
}
