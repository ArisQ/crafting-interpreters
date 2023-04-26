#ifndef _CALLABLE_H_
#define _CALLABLE_H_

#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <fstream>
#include <sstream>

#include "value.h"
#include "error.h"

class Interpreter;
class Stmt;
class Function;

class Callable: public Value {
public:
    std::string toString() { return "function"; }
    bool operator==(std::shared_ptr<Value>) { return false; }

    virtual size_t arity() = 0;
    // std::shared_ptr<Value> Call(std::vector<std::shared_ptr<Value>> arguments) {}
    virtual std::shared_ptr<Value> call(Interpreter *interpreter,Token token, std::vector<std::shared_ptr<Value>> arguments) = 0;
};

class NativeClock: public Callable {
    std::string toString() { return "<native fun clock>"; }
    size_t arity() { return 0; }
    std::shared_ptr<Value> call(Interpreter *interpreter, Token token, std::vector<std::shared_ptr<Value>> arguments) {
        using namespace std::chrono;
        uint64_t ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        return std::make_shared<NumberValue>(ms/1000.0);
        // return std::make_shared<NumberValue>(time(nullptr));
    }
};

class NativeRead: public Callable {
    std::string toString() { return "<native fun read>"; }
    size_t arity() { return 1; }
    std::shared_ptr<Value> call(Interpreter *interpreter,Token token, std::vector<std::shared_ptr<Value>> arguments) {
        auto path = std::dynamic_pointer_cast<StringValue> (arguments[0]);
        if (path == nullptr) {
            throw RuntimeError(token, "read path must be string.");
        }
        std::ifstream fs(path->v);
        std::stringstream buffer;
        buffer << fs.rdbuf();
        return std::make_shared<StringValue>(buffer.str());
    }
};

class UserFunction: public Callable {
    Token name;
    std::vector<Token> parameters;
    std::vector<std::shared_ptr<Stmt>> body;
public:
    UserFunction(Token name, std::vector<Token> parameters, std::vector<std::shared_ptr<Stmt>> body): name(name), parameters(parameters), body(body) {}
    UserFunction(Function *f);

    std::string toString() { return "<fun "+ name.lexeme +">"; }

    size_t arity() { return parameters.size(); }

    std::shared_ptr<Value> call(Interpreter *interpreter, Token token, std::vector<std::shared_ptr<Value>> arguments);
};
#endif // _CALLABLE_H_
