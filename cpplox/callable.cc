#include "callable.h"
#include "return.h"
#include "interpreter.h"

UserFunction::UserFunction(const Function &f, std::shared_ptr<Environment> closure, bool isInit): closure(closure),name(f.name), parameters(f.params), body(f.body), isInitializer(isInit) {
}

std::shared_ptr<Value> UserFunction::call(Interpreter *interpreter, Token token, std::vector<std::shared_ptr<Value>> arguments) {
    auto environment = std::make_shared<Environment>(closure);
    for(int i=0; i<parameters.size(); i++) {
        environment->define(parameters[i].lexeme, arguments[i]);
    }
    try {
        interpreter->executeBlock(body, environment);
    } catch (const ReturnException &r) {
        if(isInitializer) return closure->getAt(0, "this");
        return r.val;
    }
    if(isInitializer) return closure->getAt(0, "this");
    return std::make_shared<NilValue>();
}

std::shared_ptr<UserFunction> UserFunction::bind(const std::shared_ptr<UserClassInstance> &instance) {
    auto env = std::make_shared<Environment>(closure);
    env->define("this", instance);
    return std::make_shared<UserFunction>(name, parameters, body, env, isInitializer);
}


UserClass::UserClass(Class *k, std::shared_ptr<UserClass> superclass, std::map<std::string, std::shared_ptr<UserFunction>> methods): name(k->name), superclass(superclass),methods(methods) {}

std::shared_ptr<Value> UserClass::call(Interpreter *interpreter, Token token, std::vector<std::shared_ptr<Value>> arguments) {
    // TODO class会应shared_ptr循环引用而保留，解决后需要处理class的生命周期问题
    auto instance = std::make_shared<UserClassInstance>(this);
    auto initializer = findMethod("init");
    if (initializer!=nullptr) {
        initializer->bind(instance)->call(interpreter, token, arguments);
    }
    return instance;
}
