#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <string>
#include <vector>
#include <iostream>

#include "token.h"
#include "lox.h"

// class Token {};
// typedef std::string Token;

class Scanner {
private:
  Lox &lox;
  const std::string &s;
  std::vector<Token> tokens;
  size_t start = 0, current = 0, line = 1;

  char advance() {
    // current++;
    // return s.at(current-1);
    return s.at(current++);
  }
  char peek() {
    if(isAtEnd()) return '\0';
    return s.at(current);
  }
  char peekNext() {
    if(current+1>=s.length()) return '\0';
    return s.at(current+1);
  }
  bool match(char expected) {
    if (isAtEnd()) return false;
    // if(s.at(current)!=expected) return false;
    // current++;
    // return true;
    auto match = s.at(current)==expected;
    if (match) current++;
    return match;
  }
  bool isDigit(char c) {
    return c>='0' && c<='9';
  }
  bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
  }
  bool isAlphaNumberic(char c) {
    // return (c >= 'a' && c <= 'z') ||
    //        (c >= 'A' && c <= 'Z') ||
    //        (c >= '0' && c <= '9') ||
    //        c == '_' ;
    return isDigit(c) || isAlpha(c);
  }
  void scanToken() {
    auto c = advance();
    switch (c)
    {
    case LEFT_PAREN_V: addToken(LEFT_PAREN); break;
    case RIGHT_PAREN_V: addToken(RIGHT_PAREN); break;
    case LEFT_BRACE_V: addToken(LEFT_BRACE); break;
    case RIGHT_BRACE_V: addToken(RIGHT_BRACE); break;
    case COMMA_V: addToken(COMMA); break;
    case DOT_V: addToken(DOT); break;
    case MINUS_V: addToken(MINUS); break;
    case PLUS_V: addToken(PLUS); break;
    case SEMICOLON_V: addToken(SEMICOLON); break;
    case STAR_V: addToken(STAR); break;
    case '!': addToken(match('=')?BANG_EQUAL:BANG); break;
    case '=': addToken(match('=')?EQUAL_EQUAL:EQUAL); break;
    case '<': addToken(match('=')?LESS_EQUAL:LESS); break;
    case '>': addToken(match('=')?GREATER_EQUAL:GREATER); break;
    case SLASH_V:
      if(match(SLASH_V)) { // comment
        while(peek()!='\n' && !isAtEnd()) advance();
      } else {
        addToken(SLASH);
      }
      break;
    case ' ': case '\r': case '\t': break;
    case '\n': line++; break;
    case '"': string(); break;
    default:
      if(isDigit(c)) {
        number();
      } else if(isAlpha(c)) {
        identifier();
      } else{
        lox.error(line, "Unexpected character: '" + std::string(1, c) + "'");
      }
      break;
    }
  }
  void string() {
    while(peek()!='"' && !isAtEnd()) {
      if (peek()=='\n') line++;
      advance();
    }
    if(isAtEnd()) {
      lox.error(line, "Unterminated string.");
      return;
    }

    advance(); // closing "
    auto value = s.substr(start+1, current-start-2);
    // std::cerr << "string literal "<<value<<std::endl;
    addToken(STRING, std::make_shared<StringValue>(value));
  }
  void number() {
    while(isDigit(peek())) advance();
    if(peek()=='.' && isDigit(peekNext())) {
      advance();
      while(isDigit(peek())) advance();
    }
    auto val = s.substr(start, current-start);
    addToken(NUMBER, std::make_shared<NumberValue>(std::stod(val)));
  }
  void identifier() {
    while(isAlphaNumberic(peek())) advance();
    auto val = s.substr(start, current-start);
    auto type = IDENTIFIER;
    std::shared_ptr<Value> literal = nullptr;
    if (keywords.contains(val)) {
      auto k = keywords.at(val);
      type = k.first;
      literal = k.second;
    }
    addToken(type, literal);
  }

  void addToken(TokenType type) {
    addToken(type, nullptr);
  }
  void addToken(TokenType type, std::shared_ptr<Value> literal) {
    auto text= s.substr(start,current-start);
    lox.info(line, string_format("add token s[%d,%d): ", start, current) + text);
    tokens.push_back(Token(type, text,line, literal));

    // auto token = Token(type, s.substr(start,current),line);
    // tokens.push_back(token);

    // tokens.push_back(Token(type, s.substr(start,current),line));
  }

  bool isAtEnd() {
    return current >= s.length();
  }
public:
  Scanner(Lox &lox,const std::string &s) :lox(lox), s(s) {}
  std::vector<Token> scanTokens() {
    while(!isAtEnd()) { // !isAtEnd()
      start = current;
      scanToken();
    }
    tokens.push_back(Token(TOKEN_EOF,"",line,nullptr));
    return tokens;
  }
};

#endif // _SCANNER_H_
