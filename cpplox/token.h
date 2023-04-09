#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <map>
#include <vector>
#include <array>
#include <string>
#include <ostream>
#include <iomanip>
#include "value.h"
#include "utils/string_format.h"

// namespace lox{
// enum class TokenType
enum TokenType
{
    // single character tokens
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens;
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // literals
    IDENTIFIER,
    STRING,
    NUMBER,

    // keywords
    //     AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    //  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
    AND, OR,
    VAR, CLASS, SUPER, THIS, FUN, RETURN,
    IF, ELSE, FOR, WHILE,
    TRUE, FALSE, NIL,
    PRINT,

    TOKEN_EOF
};

// static const std::array<const std::string,10> typeStr{
static const std::vector<std::string> typeStr{
    "LEFT_PAREN",
    "RIGHT_PAREN",
    "LEFT_BRACE",
    "RIGHT_BRACE",
    "COMMA",
    "DOT",
    "MINUS",
    "PLUS",
    "SEMICOLON",
    "SLASH",
    "STAR",

    "BANG",
    "BANG_EQUAL",
    "EQUAL",
    "EQUAL_EQUAL",
    "GREATER",
    "GREATER_EQUAL",
    "LESS",
    "LESS_EQUAL",

    "IDENTIFIER",
    "STRING",
    "NUMBER",

    "AND",
    "OR",
    "VAR",
    "CLASS",
    "SUPER",
    "THIS",
    "FUN",
    "RETURN",
    "IF",
    "ELSE",
    "FOR",
    "WHILE",
    "TRUE",
    "FALSE",
    "NIL",
    "PRINT",

    "TOKEN_EOF",
};
const std::string TokenTypeStr(TokenType t);

static size_t maxTypeStrLen = [](){ // TODO
    size_t len = 0;
    for(const auto &s:typeStr) {
        len=s.length()>len?s.length():len;
    }
    // for(size_t i=0;i<typeStr.size() ;++i) {
    //     const auto l = typeStr[i].length();
    //     len=l>len?l:len;
    // }
    return len;
}();

const char LEFT_PAREN_V = '(';
const char RIGHT_PAREN_V = ')';
const char LEFT_BRACE_V = '{';
const char RIGHT_BRACE_V = '}';
const char COMMA_V = ',';
const char DOT_V = '.';
const char MINUS_V = '-';
const char PLUS_V = '+';
const char SEMICOLON_V = ';';
const char SLASH_V = '/';
const char STAR_V = '*';

#define KEYWORD_KV(k) {#k, k}
static const std::map<std::string, std::pair<TokenType, std::shared_ptr<Value>>> keywords{
    {"and", {AND, nullptr}},
    {"or", {OR, nullptr}},
    {"var", {VAR, nullptr}},
    {"class", {CLASS, nullptr}},
    {"super", {SUPER, nullptr}},
    {"this", {THIS, nullptr}},
    {"fun", {FUN, nullptr}},
    {"return", {RETURN, nullptr}},
    {"if", {IF, nullptr}},
    {"else", {ELSE, nullptr}},
    {"for", {FOR, nullptr}},
    {"while", {WHILE, nullptr}},
    {"true", {TRUE, std::make_shared<BoolValue>(true)}},
    {"false", {FALSE, std::make_shared<BoolValue>(false)}},
    {"nil", {NIL, std::make_shared<NilValue>()}},
    {"print", {PRINT, nullptr}},
};

class Token
{
public:
    TokenType type;
    std::string lexeme;
    std::shared_ptr<Value> literal;
    int line;

    // Token(const TokenType type, const std::string lexeme, int line) : type(type), lexeme(lexeme), line(line) {}

    Token(const TokenType type, const std::string lexeme, int line, std::shared_ptr<Value> literal) : type(type), lexeme(lexeme), line(line),literal(literal) {}


    std::string toString() const
    {
        // return string_format("%s %s %d", type,lexeme,line);
        return string_format("%s", type) + lexeme + string_format("%d", line);
    }

    friend std::ostream &operator<<(std::ostream &os, const Token &t);
};


#endif // _TOKEN_H_
