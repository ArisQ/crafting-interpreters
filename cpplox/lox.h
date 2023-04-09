#ifndef _LOX_H_
#define _LOX_H_

#include <string>
#include "token.h"
#include "interpreter.h"

class Lox
{
    friend class Scanner;
    friend class Parser;
    friend class Interpreter;

    bool hasError = false;
    void report(int line, std::string level, std::string where, std::string message);
    void error(int line, std::string message);
    void error(Token token, std::string message);
    void info(int line, std::string message);

    Interpreter interpreter;
    bool hasRuntimeError = false;
    void runtimeError(RuntimeError err);
public:
    void run(const std::string &s);
    int runFile(const std::string &path);
    int runPrompt();
};

#endif // _LOX_H_
