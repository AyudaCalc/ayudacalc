#include "token.h"

Token::Token() :
  type(eof),
  line(0),
  col(0)
{}

Token::~Token() {}

Token::Token(TokenType typ, int lineNum, int colNum) : 
  type(typ),
  line(lineNum),
  col(colNum)
{}

TokenType Token::getType() const {
  return type;
}

int Token::getLine() const {
  return line;
}

int Token::getCol() const {
  return col;
}

string Token::getLex() const { return ""; }

string Token::getVal() const { return ""; }

LexicalToken::LexicalToken(TokenType typ, string* lex, string* val, int lineNum, int colNum) :
   Token(typ,lineNum,colNum),
   lexeme(lex),
   val(val)
{}

LexicalToken::~LexicalToken() {
   try {
      delete lexeme;
      delete val;
   } catch (...) {}
}

string LexicalToken::getLex() const {
  return *lexeme;
}

string LexicalToken::getVal() const {
  return *val;
}
