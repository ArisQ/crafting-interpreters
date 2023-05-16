#ifndef _LOX_H_
#define _LOX_H_

#include <string>

#include "vm/config.h"
#include "token.h"
#include "interpreter.h"
#include "vm/vm.h"

class Lox
{
    friend class Scanner;
    friend class Parser;
    friend class Interpreter;
    friend class Resolver;

    bool hasError = false;
    void report(int line, std::string level, std::string where, std::string message);
    void error(int line, std::string message);
    void error(Token token, std::string message);
    void info(int line, std::string message);

#ifndef INTERPRET_WITH_VM
    Interpreter interpreter;
#endif
    bool hasRuntimeError = false;
    void runtimeError(RuntimeError err);
public:
    void run(const std::string &s);
    int runFile(const std::string &path);
    int runPrompt();
};

#endif // _LOX_H_
