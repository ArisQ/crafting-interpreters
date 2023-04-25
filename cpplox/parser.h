#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdexcept>
#include <vector>

#include "lox.h"
#include "token.h"
#include "expr.h"
#include "stmt.h"

struct ParseError: public std::runtime_error {
public:
    ParseError():std::runtime_error("parser error") {
        /* std::runtime_error(); */
    }
    /* const char* what() const throw() { */
    /*     return "Parser error."; */
    /* }; */
};

class Parser {
    Lox *lox;
    std::vector<Token> tokens; // TODO: tokens are copied.
    size_t current = 0;

    // expressions
    std::shared_ptr<Expr> expression() {
        return assignment();
    }
    std::shared_ptr<Expr> assignment() {
        auto expr = logicalOr();
        if (match(EQUAL)) {
            auto equal = previous();
            auto var = std::dynamic_pointer_cast<Variable>(expr); // 解析到了Variable，最后返回的AST是Assign
            if (var!=nullptr) {
                return std::make_shared<Assign>(var->name, equality());
            }
            throw RuntimeError(equal, "Invalid assignment target");
        }
        return expr;
    }
    std::shared_ptr<Expr> logicalOr() {
        auto expr = logicalAnd();
        while(match(OR)) {
            Token op = previous();
            auto right = logicalAnd();
            expr = std::make_shared<Logical>(expr, op, right);
        }
        return expr;
    }
    std::shared_ptr<Expr> logicalAnd() {
        auto expr = equality();
        while(match(AND)) {
            Token op = previous();
            auto right = equality();
            expr = std::make_shared<Logical>(expr, op, right);
        }
        return expr;
    }
    std::shared_ptr<Expr> equality() {
        auto expr = comparison();
        while(match({BANG_EQUAL, EQUAL_EQUAL})) {
            Token op = previous();
            auto right = comparison();
            expr = std::make_shared<Binary>(expr, op, right);
        }
        return expr;
    }
    std::shared_ptr<Expr> comparison() {
        auto expr = term();
        while(match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
            Token op = previous();
            auto right = term();
            expr = std::make_shared<Binary>(expr, op, right);
        }
        return expr;
    }
    std::shared_ptr<Expr> term() {
        auto expr = factor();
        while(match({MINUS, PLUS})) {
            Token op = previous();
            auto right = factor();
            expr = std::make_shared<Binary>(expr, op, right);
        }
        return expr;
    }
    std::shared_ptr<Expr> factor() {
        auto expr = unary();
        while(match({SLASH, STAR})) {
            Token op = previous();
            auto right = unary();
            expr = std::make_shared<Binary>(expr, op, right);
        }
        return expr;
    }
    std::shared_ptr<Expr> unary() {
        if(match({BANG, MINUS})) {
            Token op = previous();
            auto right = unary();
            return std::make_shared<Unary>(op, right);
        }
        return call();
    }
    std::shared_ptr<Expr> call() {
        auto expr = primary();
        while(true) {
            if(match(LEFT_PAREN)) {
                expr = finishCall(expr);
            } else {
                break;
            }
        }
        return expr;
    }
    std::shared_ptr<Expr> finishCall(std::shared_ptr<Expr> callee) {
        std::vector<std::shared_ptr<Expr>> argments;
        if(!check(RIGHT_PAREN)) {
            do {
                if(argments.size() >= 255) {
                    lox->error(peek(), "Can't have more than 255 arguments.");
                }
                argments.push_back(expression());
            } while(match(COMMA));
        }
        auto paren = consume(RIGHT_PAREN, "Expect ')' after arguments.");
        return std::make_shared<Call>(callee, paren , argments);
    }
    std::shared_ptr<Expr> primary() {
        /* if(match(FALSE)) return std::make_shared<Literal>(previous().literal); */
        /* if(match(TRUE)) return std::make_shared<Literal>(previous().literal); */
        /* if(match(NIL)) return std::make_shared<Literal>(previous().literal); */
        /* if(match({NUMBER, STRING})) return std::make_shared<Literal>(previous().literal); */
        if(match({FALSE, TRUE, NIL, NUMBER, STRING}))
            return std::make_shared<Literal>(previous().literal);

        if(match(IDENTIFIER)) {
            return std::make_shared<Variable>(previous());
        }

        if(match({LEFT_PAREN})) {
            auto expr = expression();
            consume(RIGHT_PAREN, "Expect')' after expression.");
            return std::make_shared<Grouping>(expr);
        }
        throw error(peek(), "Expect expression.");
    }

    // declaration
    std::shared_ptr<Stmt> declaration() {
        try {
            if(match(VAR)) {
                return varDeclaration();
            }
            return statement();
        } catch (const ParseError &e) {
            synchronize();
            return nullptr;
        }
    }
    std::shared_ptr<Stmt> varDeclaration() {
        Token name = consume(IDENTIFIER, "Expect variable name.");
        std::shared_ptr<Expr> initializer = nullptr;
        if(match(EQUAL)) {
            initializer = expression();
        }
        consume(SEMICOLON, "Exepct ';' after variable declaration.");
        return std::make_shared<Var>(name, initializer);
    }
    // statements
    std::shared_ptr<Stmt> statement() {
        if(match(IF)) { return ifStatement(); }
        if(match(WHILE)) { return whileStatement(); }
        if(match(FOR)) { return forStatement(); }
        if(match(PRINT)) { return printStatement(); }
        if(match(LEFT_BRACE)) { return blockStatement(); }
        return expressionStatement();
    }
    std::shared_ptr<Stmt> printStatement() {
        auto right = expression();
        consume(SEMICOLON, "Expect ';' after value.");
        return std::make_shared<Print>(right);
    }
    std::shared_ptr<Stmt> expressionStatement() {
        auto expr = expression();
        consume(SEMICOLON, "Expect ';' after expression;");
        return std::make_shared<Expression>(expr);
    }
    std::shared_ptr<Stmt> blockStatement() {
        std::vector<std::shared_ptr<Stmt>> stmts;
        while (!check(RIGHT_BRACE) && !isAtEnd()) {
            stmts.push_back(declaration());
        }
        consume(RIGHT_BRACE, "Expect '}' after block;");
        return std::make_shared<Block>(stmts);
    }
    std::shared_ptr<Stmt> ifStatement() {
        consume(LEFT_PAREN, "Expect '(' after if.");
        auto condition = expression();
        consume(RIGHT_PAREN, "Expect ')' after if condition.");

        auto thenBranch = statement();
        std::shared_ptr<Stmt> elseBranch = nullptr;
        if(match(ELSE)) {
            elseBranch = statement();
        }
        return std::make_shared<If>(condition,thenBranch,elseBranch);
    }
    std::shared_ptr<Stmt> whileStatement() {
        consume(LEFT_PAREN, "Expect '(' after while.");
        auto condition = expression();
        consume(RIGHT_PAREN, "Expect ')' after while condition.");

        auto body = statement();
        return std::make_shared<While>(condition, body);
    }
    std::shared_ptr<Stmt> forStatement() {
        consume(LEFT_PAREN, "Expect '(' after for.");

        std::shared_ptr<Stmt> initializer;
        if(match(SEMICOLON)) {
            initializer = nullptr;
        } else if (match(VAR)) {
            initializer = varDeclaration();
        } else {
            initializer= expressionStatement();
        }

        std::shared_ptr<Expr> condition = nullptr;
        if(!check(SEMICOLON)) {
            condition = expression();
        }
        consume(SEMICOLON, "Expect ';' after loop condition.");

        std::shared_ptr<Expr> increment = nullptr;
        if(!check(RIGHT_PAREN)) {
            increment = expression();
        }
        consume(RIGHT_PAREN, "Expect ')' after for condition.");

        auto body = statement();
        if(increment!=nullptr) {
            body = std::make_shared<Block>(std::vector<std::shared_ptr<Stmt>>{
                body,
                std::make_shared<Expression>(increment),
            });
        }
        if(condition==nullptr) {
            condition = std::make_shared<Literal>(std::make_shared<BoolValue>(true));
        }
        body = std::make_shared<While>(condition, body);

        if (initializer!=nullptr) {
            body = std::make_shared<Block>(std::vector<std::shared_ptr<Stmt>>{
                initializer,
                body,
            });
        }

        return body;
    }

    // overload for single type
    bool match(TokenType type) {
        return match({type});
    }
    bool match(std::initializer_list<TokenType> types) {
        for(auto type: types) {
            if(check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }
    Token consume(TokenType type, std::string message) {
        if (check(type)) return advance();
        throw error(peek(), message);
    }
    bool check(TokenType type) {
        if(isAtEnd()) return false;
        return peek().type == type;
    }
    bool isAtEnd() {
        return peek().type == TOKEN_EOF;
    }
    Token previous() {
        return tokens.at(current - 1);
    }
    Token peek() {
        return tokens.at(current);
    }
    Token advance() {
        if (!isAtEnd()) current++;
        return previous();
    }
    ParseError error(Token token, std::string message) {
        lox->error(token, message);
        return ParseError();
    }

    void synchronize() {
        advance();
        while(!isAtEnd()) {
            if(previous().type == SEMICOLON) return;
            switch (peek().type) {
                case CLASS:
                case FUN:
                case VAR:
                case FOR:
                case IF:
                case WHILE:
                case PRINT:
                case RETURN:
                    return;
                default: break;
            }
            advance();
        }
    }
public:
    Parser(Lox *lox, std::vector<Token> tokens): lox(lox), tokens(tokens) {}
    std::vector<std::shared_ptr<Stmt>> parse() {
        std::vector<std::shared_ptr<Stmt>> stmts;
        while(!isAtEnd()) {
            // 解析失败也push，不应该被执行
            stmts.push_back(declaration());
        }
        return stmts;
    }
};

#endif // _PARSER_H_

