#ifndef _RETURN_H_
#define _RETURN_H_

#include <stdexcept>

#include "value.h"

struct ReturnException: public std::runtime_error {
public:
    std::shared_ptr<Value> val;
    ReturnException(std::shared_ptr<Value> val): val(val), std::runtime_error("return") { }
};

#endif // _RETURN_H_