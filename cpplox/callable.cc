#include "callable.h"
#include "interpreter.h"

UserFunction::UserFunction(Function *f): name(f->name), parameters(f->params), body(f->body) {
}

std::shared_ptr<Value> UserFunction::call(Interpreter *interpreter, Token token, std::vector<std::shared_ptr<Value>> arguments) {
    auto environment = std::make_shared<Environment>(interpreter->globals);
    for(int i=0; i<parameters.size(); i++) {
        environment->define(parameters[i].lexeme, arguments[i]);
    }
    interpreter->executeBlock(body, std::make_shared<Environment>(environment));
    return std::make_shared<NilValue>();
}