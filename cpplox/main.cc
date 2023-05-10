#include <sysexits.h>

#include <iostream>

#define DEBUG_TRACE_EXECUTION

#include "lox.h"
#include "vm/vm.h"
#include "vm/chunk.h"
#include "vm/debug.h"
#include "vm/object.h"

using namespace std;
using namespace vm;

int main(int argc, char *argv[])
{
    // Obj obj;
    // ObjString str("xxx");
    // Obj *p;
    // cout<<sizeof(obj) <<endl;
    // cout<<sizeof(p) <<endl;
    // cout<<sizeof(str) <<endl;
    // p = &obj;
    // cout << *(uint64_t*)(&obj) <<endl;
    // cout << *(uint64_t*)(&str) <<endl;
    // ObjString str2("yyy");
    // ObjString str3(std::move(str));
    // cout << *(uint64_t*)(&str2) <<endl;
    // return 0;
    cout << "lox implemented in c++!" << endl;

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
