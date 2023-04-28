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
    Environment(const std::shared_ptr<Environment> &enclosing=nullptr): enclosing(enclosing) { }
    void define(const std::string &name, const std::shared_ptr<Value> &v) {
        values[name] = v;
    }
    void assign(const Token &name, const std::shared_ptr<Value> &v) {
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
    std::shared_ptr<Value> get(const Token &name) {
        auto n = name.lexeme;
        if (values.contains(n)) {
            return values.at(n);
        }
        if (enclosing!=nullptr) {
            return enclosing->get(name);
        }
        throw RuntimeError(name, "Undefine variable '" + n + "'.");
    }
    std::shared_ptr<Value> getAt(int distance, const Token &name) {
        return ancestor(distance).values.at(name.lexeme);
    }
    void assignAt(int distance, const Token &name, const std::shared_ptr<Value> &v) {
        ancestor(distance).values[name.lexeme] = v;
    }
    Environment &ancestor(int distance) {
        if (distance==0) {
            return *this;
        }
        auto env = this->enclosing;
        for(int i=1;i<distance;i++) {
            env = env->enclosing;
        }
        return *env;
    }

    static void dump(std::shared_ptr<Environment> &env) {
        int d = 0;
        std::cout << "==========ENV==========" << std::endl;
        while (env != nullptr) {
            std::cout << d << "----------" << std::endl;
            for (const auto &k : env->values) {
                std::cout << k.first << ": " << k.second->toString() << std::endl;
            }
            env = env->enclosing;
            d++;
        }
        std::cout << "=======================" << std::endl;
    }
};

#endif // _ENVIRONMENT_H_
