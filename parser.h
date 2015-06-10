#ifndef parser_h
#define parser_h

#include "ast.h"
#include "scanner.h"
#include <string>

class Parser {
 public:
   Parser(istream* in);
   ~Parser();

   AST* parse();
   AST* getInfo(AST* e);

 private:
   AST* Prog();
   AST* Stmts(AST* e);
   AST* Stmt();
   AST* Expr();
   AST* RestExpr(AST* e);
   AST* Term();
   AST* RestTerm(AST* e);
   AST* Storable();
   AST* MemOperation(AST* e);
   AST* Factor();

   Scanner* scan;
   bool inicio;
};

extern bool comp;
extern char** archivos;
extern int sizeA;


class Var {
public:
   string id;
   int val;
   Var* past;

   Var(string id, int val);
   ~Var();
};

#endif   
