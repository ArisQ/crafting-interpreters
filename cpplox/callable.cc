#include "callable.h"
#include "return.h"
#include "interpreter.h"

UserFunction::UserFunction(const Function &f, std::shared_ptr<Environment> closure): closure(closure),name(f.name), parameters(f.params), body(f.body) {
}

std::shared_ptr<Value> UserFunction::call(Interpreter *interpreter, Token token, std::vector<std::shared_ptr<Value>> arguments) {
    auto environment = std::make_shared<Environment>(closure);
    for(int i=0; i<parameters.size(); i++) {
        environment->define(parameters[i].lexeme, arguments[i]);
    }
    try {
        interpreter->executeBlock(body, environment);
    } catch (const ReturnException &r) {
        return r.val;
    }
    return std::make_shared<NilValue>();
}

UserClass::UserClass(Class *k, std::map<std::string, std::shared_ptr<UserFunction>> methods): name(k->name), methods(methods) {}

std::shared_ptr<Value> UserClass::call(Interpreter *interpreter, Token token, std::vector<std::shared_ptr<Value>> arguments) {
    // TODO class会应shared_ptr循环引用而保留，解决后需要处理class的生命周期问题
    return std::make_shared<UserClassInstance>(this);
}