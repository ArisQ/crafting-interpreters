#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdexcept>

#include "token.h"

struct RuntimeError: public std::runtime_error {
public:
    Token token;
    RuntimeError(const Token &op, const std::string &msg):
        token(op), std::runtime_error(msg) { }

    static RuntimeError NumberOperand(const Token &op) {
        return RuntimeError(op, "Operand must be a number.");
    }
    static RuntimeError NumberStringOperand(const Token &op) {
        return RuntimeError(op, "Operands must be numbers or strings.");
    }
};

#endif // _ERROR_H_