#ifndef _VALUE_H_
#define _VALUE_H_

#include <string>
#include <memory>
/* #include <iostream> */
#include "utils/string_format.h"

class Value { // literal lexeme/value
public:
    virtual std::string toString() = 0;
    virtual bool operator==(std::shared_ptr<Value>) = 0;
};

template<typename T>
class Val: public Value{
public:
    T v;
    Val(T v): v(v) {}
    std::string toString();
    bool operator==(std::shared_ptr<Value> t) {
        auto tp = std::dynamic_pointer_cast<Val<T>>(t);
        if (!tp) return false;
        return tp->v == v;
    }
};

template<> std::string Val<std::string>::toString();
template<> std::string Val<double>::toString();
template<> std::string Val<bool>::toString();

template<>
class Val<std::nullptr_t>: public Value{
public:
    Val() {}
    std::string toString() { return "nil"; }
    bool operator==(std::shared_ptr<Value> t) {
        auto tv = std::dynamic_pointer_cast<Val<std::nullptr_t>>(t);
        return tv != nullptr;
    }
};

using StringValue = Val<std::string>;
using NumberValue = Val<double>;
using BoolValue = Val<bool>;
using NilValue = Val<std::nullptr_t>;

#endif // _VALUE_H_
