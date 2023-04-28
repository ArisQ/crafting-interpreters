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
class Environment;
class Stmt;
class Function;
class Class;

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

class UserClassInstance;
class UserFunction: public Callable {
    Token name;
    std::vector<Token> parameters;
    std::vector<std::shared_ptr<Stmt>> body;

    std::shared_ptr<Environment> closure;

    bool isInitializer;
public:
    UserFunction(const Function &f, std::shared_ptr<Environment> closure, bool isInitializer = false);
    UserFunction(
        const Token &name,
        const std::vector<Token> &parameters,
        const std::vector<std::shared_ptr<Stmt>> &body,
        std::shared_ptr<Environment> closure,
        bool isInitializer) : name(name), parameters(parameters), body(body), closure(closure), isInitializer(isInitializer)
    {
    }

    std::string toString() { return "<fun "+ name.lexeme +">"; }

    size_t arity() { return parameters.size(); }

    std::shared_ptr<Value> call(Interpreter *interpreter, Token token, std::vector<std::shared_ptr<Value>> arguments);

    std::shared_ptr<UserFunction> bind(const std::shared_ptr<UserClassInstance> &instance);
};

class UserClass: public Callable {
    friend UserClassInstance;

    Token name;
    std::map<std::string, std::shared_ptr<UserFunction>> methods;
public:
    UserClass(Class *k, std::map<std::string, std::shared_ptr<UserFunction>> methods);

    std::string toString() { return "<class "+ name.lexeme +">"; }

    size_t arity() {
        auto initializer = findMethod("init");
        if(initializer!=nullptr) 
            return initializer->arity();
        return 0;
    }

    std::shared_ptr<Value> call(Interpreter *interpreter, Token token, std::vector<std::shared_ptr<Value>> arguments);

    std::shared_ptr<UserFunction> findMethod(const std::string &name) {
        if(methods.contains(name))
            return methods.at(name);
        return nullptr;
    }
};

class UserClassInstance: public Value, public std::enable_shared_from_this<UserClassInstance> {
    UserClass *klass;

    std::map<std::string, std::shared_ptr<Value>> fields;
public:
    // TODO 指针问题
    // Class定义过生命周期后，Instance的引用会有问题
    UserClassInstance(UserClass *klass):klass(klass) {}

    std::string toString() { return "<class "+ klass->name.lexeme +" instance>"; }
    bool operator==(std::shared_ptr<Value>) { return false; } // TODO

    std::shared_ptr<Value> get(const Token &name) {
        auto lexeme = name.lexeme;
        if (fields.contains(lexeme)) {
            return fields.at(lexeme);
        }

        auto method = klass->findMethod(name.lexeme);
        if(method!=nullptr) return method->bind(shared_from_this()); // shared_from_this !!!

        throw RuntimeError(name, "Undefined property '" + lexeme +"'.");
        return std::make_shared<NilValue>();
    }
    void set(Token name, const std::shared_ptr<Value> &value) {
        fields[name.lexeme] = value;
    }
};

#endif // _CALLABLE_H_
