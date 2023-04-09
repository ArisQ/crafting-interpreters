#include "token.h"


const std::string TokenTypeStr(TokenType t) {
    return t >= typeStr.size() ? "invalid token type" : typeStr[t];
}

std::ostream &operator<<(std::ostream &os, const TokenType &t)
{
    // os << (t >= typeStr.size() ? "invalid token type" : typeStr[t]);
    os << TokenTypeStr(t);
    return os;
}

std::ostream &operator<<(std::ostream &os, const Token &t)
{
    // os << t.toString();
    // os << t.type << " lexeme=" << t.lexeme << " line=" << t.line;
    os << t.line << " | " << std::setw(maxTypeStrLen) << t.type
       << " | " << t.lexeme;
    if (t.literal!=nullptr) {
        os <<" => "<<t.literal->toString();
    }
    return os;
}
