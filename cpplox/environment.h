#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <map>
#include "value.h"
#include "token.h"
#include "error.h"

class Environment {
    std::map<std::string, std::shared_ptr<Value>> values;
    std::shared_ptr<Environment> enclosing;
public:
    Environment(const Environment&) = delete;
    Environment(std::shared_ptr<Environment> enclosing=nullptr): enclosing(enclosing) { }
    void define(std::string name, std::shared_ptr<Value> v) {
        values[name] = v;
    }
    void assign(Token name, std::shared_ptr<Value> v) {
        auto n = name.lexeme;
        if (values.contains(n)) {
            values[n] = v;
            return;
        }
        if (enclosing!=nullptr) {
            return enclosing->assign(name, v);
        }
        throw RuntimeError(name, "Undefine variable '" + n + "'.");
    }
    std::shared_ptr<Value> get(Token name) {
        auto n = name.lexeme;
        if (values.contains(n)) {
            return values.at(n);
        }
        if (enclosing!=nullptr) {
            return enclosing->get(name);
        }
        throw RuntimeError(name, "Undefine variable '" + n + "'.");
    }
};

#endif // _ENVIRONMENT_H_
