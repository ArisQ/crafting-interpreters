#include <sysexits.h>

#include <iostream>

#include "lox.h"
#include "vm/chunk.h"
#include "vm/debug.h"

using namespace std;
using namespace vm;

int main(int argc, char *argv[])
{
    cout << "lox implemented by c++!" << endl;
    // unsaved

    Chunk chunk;
    chunk.write(OP_RETURN);
    chunk.write(OP_CONSTANT);
    chunk.write(chunk.addConstant(1));
    chunk.write(OP_CONSTANT);
    chunk.write(chunk.addConstant(1));
    cout << ChunkDebugName("test chunk") << chunk << endl;
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
