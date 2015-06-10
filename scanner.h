#ifndef scanner_h
#define scanner_h

#include <iostream>
#include "token.h"

class Scanner {
public:
  Scanner(istream* in);
  ~Scanner();

  Token* getToken();
  void putBackToken();
  void setStringStream(string line);
 
private:
  Scanner();

  istream* inStream;
  int lineCount;
  int colCount;

  bool needToken;
  Token* lastToken;
};

extern char** variables;
extern int sizeV;
extern char** globales;
extern int sizeG;

#endif
  
  

