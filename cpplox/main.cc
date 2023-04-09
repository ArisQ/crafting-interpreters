#include <sysexits.h>

#include <iostream>

#include "lox.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "lox implemented by c++!" << endl;
    // unsaved

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
