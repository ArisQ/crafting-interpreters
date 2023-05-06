#include <sysexits.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "interpreter.h"
#include "resolver.h"
#include "lox.h"
#include "parser.h"
#include "scanner.h"
#include "expr.h"
#include "ast_printer.h"

#include "vm/compiler.h"

// TODO: do not using namespace in header
using namespace std;
// using string = std::string;
// using cout = std::cout;

void Lox::report(int line, string level, string where, string message)
{
    cout << "[line " << line << "] "<< level << where << ": " << message << endl;
    hasError = true;
}

void Lox::error(int line, string message)
{
    report(line, "Error","", message);
}

void Lox::error(Token token, std::string message) {
    if(token.type == TOKEN_EOF) {
        report(token.line, "Error", " at end", message);
    } else {
        report(token.line, "Error", " at '"+token.lexeme+"'", message);
    }
}

void Lox::info(int line, string message)
{
    // report(line, "Info ", "", message);
}

void Lox::runtimeError(RuntimeError err) {
    cout << err.what() <<" [line " << err.token.line << "]" << endl;
    hasRuntimeError = true;
}

void Lox::run(const string &s)
{
    // cout << s << endl;
    Scanner scanner(*this, s); // use pointer or reference
    auto tokens = scanner.scanTokens();
    for (const auto &token : tokens) {
        cout << token << endl;
    }

    Parser parser(this, tokens);
    auto stmts = parser.parse();
    if (hasError) {
        return;
    }
    std::cout<< AstPrinter().print(stmts)<<std::endl;

#ifdef INTERPRET_WITH_VM
    try {
        vm::Compiler compiler;
        // auto chunk = compiler.compile(stmts);
        auto chunk = compiler.compile();
        vm.interpret(&chunk);
    } catch (RuntimeError err) {
        runtimeError(err);
    }
#else
    Resolver resolver(this, &interpreter);
    resolver.resolve(stmts);
    if(hasError) return;

    try {
        interpreter.evaluate(stmts);
    } catch (RuntimeError err) {
        runtimeError(err);
    }
#endif

    /* auto v = std::make_shared<NumberValue>(123); */
    /* std::cout<<"v "<< v<<" " << v.get() <<std::endl; */
    /* auto e = std::make_shared<Literal>(v); */
    /* ret = interpreter.evaluate(e); */
    /* /1* std::cout<< ret <<std::endl; *1/ */
    /* std::cout<<"ret "<< ret << " " << ret.get() <<std::endl; */
    /* std::cout<< ret->toString() <<std::endl; */
    /* std::cout<<"ok"<<std::endl; */
}

int Lox::runFile(const string &path)
{
    cout << path << endl;
    fstream fs(path);
    stringstream buf;
    buf << fs.rdbuf();
    run(buf.str());
    return hasError ? EX_DATAERR : (hasRuntimeError?EX_SOFTWARE : EX_OK);
}

int Lox::runPrompt()
{
    string line;
    while (true)
    {
        cout << "> ";
        if (!getline(cin, line))
            break;
        if (line.length() == 0)
            continue;
        run(line);
        hasError = false;
    }
    return EX_OK;
}

