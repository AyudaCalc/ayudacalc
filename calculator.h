#ifndef calculator_h
#define calculator_h

#include <string>
#include "parser.h"
 
using namespace std;

class Calculator {
 public:
   Calculator();
   void eval();
   void store(int val);
   int plus(int val);
   int minus(int val);
   int recall();
   int clear();
   void generateEwe(AST* e);
   string read();
   string read2();
   bool fileExists(const char* fileName);
   string convert(int val);

 private:
   int memory;
   int cont;
   int cont2;
   int cont3;
   bool archivo;
   string line;
   string pas;
   Parser* parser;
};

extern Calculator* calc;
extern bool parar;

#endif

