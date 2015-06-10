#ifndef token_h
#define token_h

#include <string>
using namespace std;

enum TokenType {
   identifier,keyword,number,equals,semicolon,add,sub,times,divide,mod,lparen,rparen,eof,eol,unrecognized
};

class Token {
public:

  Token();
  Token(TokenType typ, int line, int col);
  virtual ~Token();

  TokenType getType() const;
  int getLine() const;
  int getCol() const;
  virtual string getLex() const;
  virtual string getVal() const;

private:
  TokenType type;
  int line,col;
};

class LexicalToken: public Token {
 public:
   LexicalToken(TokenType typ, string* lex, string* val, int line, int col);
   ~LexicalToken();

   virtual string getLex() const;
   virtual string getVal() const;

 private:
   string* lexeme;
   string* val;
};

#endif




