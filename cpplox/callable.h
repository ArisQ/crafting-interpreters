#ifndef _CALLABLE_H_
#define _CALLABLE_H_

#include <vector>
#include <string>
#include <ctime>

#include "value.h"

class Interpreter;
class Callable: public Value {
public:
    std::string toString() { return "function"; }
    bool operator==(std::shared_ptr<Value>) { return false; }

    virtual size_t arity() = 0;
    // std::shared_ptr<Value> Call(std::vector<std::shared_ptr<Value>> arguments) {}
    virtual std::shared_ptr<Value> call(Interpreter *interpreter,std::vector<std::shared_ptr<Value>> arguments) = 0;
};

class NativeFnClock: public Callable {
    std::string toString() { return "<native fn clock>"; }
    size_t arity() { return 0; }
    std::shared_ptr<Value> call(Interpreter *interpreter,std::vector<std::shared_ptr<Value>> arguments) {
        return std::make_shared<NumberValue>(time(nullptr));
    }
};

#endif // _CALLABLE_H_
