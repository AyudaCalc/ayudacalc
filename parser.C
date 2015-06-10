#include "parser.h"
#include "calcex.h"
#include "calculator.h"
#include <string>
#include <sstream>

Parser::Parser(istream* in):
  inicio(true)
{
   scan = new Scanner(in);
}
       
Parser::~Parser() {
   try {   
      delete scan;
   } catch (...) {}
}     

AST* Parser::parse(){
   return Prog();
}

AST* Parser::Prog(){
   AST* result = Stmts(NULL);
   Token* t = scan->getToken();

   if(t->getType() != eol){
      cout << "* Syntax Error: Expected EOF, found token at column " 
	   << t->getCol()
	   << endl;
      throw ParseError;
   }else cout << "\b\b" << endl;

   return result;
}

AST* Parser::getInfo(AST* e){
   if(!comp){
      cout << "= " 
           << e->getId()
           << "<-"
           << e->evaluate() << endl;
   }

   if(sizeA == 0) scan->setStringStream(calc->read());
   else scan->setStringStream(calc->read2());
}

AST* Parser::Stmts(AST* e){
   Token* t = scan->getToken();
   
   if(t->getType() != eol){
      scan->putBackToken();
      AST* a = Stmt();
      getInfo(a);
      //Var* past;
      //string id = a->getId();
      //int val = a->evaluate();
      //Var* var = new Var(id,val);
      //if(inicio) past = var;
      //else var->past = past;
      return new SemicolonNode(a,Stmts(NULL));
   }

   scan->putBackToken();
   return e;
}

AST* Parser::Stmt(){
   Token* t2 = scan->getToken();

   if(t2->getType() != identifier){
      cout << "* Expected IDENTIFIER found "
	   << t2->getType() << " at line: "
	   << t2->getLine() << " col: "
	   << t2->getCol()
	   << endl;
      throw ParseError;
   }   

   Token* t = scan->getToken();

   if(t->getType() != equals){
      cout << "* Expected EQUALS found "
	   << t->getType() << " at line: "
	   << t->getLine() << " col: "
	   << t->getCol()
	   << endl;
      throw ParseError;
   }

   AST* result = Expr();
   
   t = scan->getToken();
   
   if(t->getType() != semicolon){
      cout << "* Expected SEMICOLON found "
	   << t->getType() << " at line: "
	   << t->getLine() << " col: "
	   << t->getCol()
	   << endl;
      throw ParseError;
   }

   t = scan->getToken();

   if(t->getType() != eol){
      cout << "Syntax Error: Expected EOL, found token at column "  
   	     << t->getCol()
           << endl;
      throw ParseError;
   }

   return new IdentifierNode(result,t2->getLex());
}

AST* Parser::Expr(){
   return RestExpr(Term());
}

AST* Parser::RestExpr(AST* e){
   Token* t = scan->getToken();
   
   if(t->getType() == add){
      return RestExpr(new AddNode(e,Term()));
   }

   if(t->getType() == sub){
      return RestExpr(new SubNode(e,Term()));
   }

   scan->putBackToken();

   return e;
}

AST* Parser::Term(){
   return RestTerm(Storable());
}

AST* Parser::RestTerm(AST* e){
   Token* t = scan->getToken();

   if(t->getType() == times){
      return RestTerm(new TimesNode(e,Term()));
   }

   if(t->getType() == divide){
      return RestTerm(new DivideNode(e,Term()));
   }

   if(t->getType() == mod){
      return RestTerm(new ModNode(e,Term()));
   }

   scan->putBackToken();

   return e;
}

AST* Parser::Storable(){
   return MemOperation(Factor());
}

AST* Parser::MemOperation(AST* e){
   Token* t = scan->getToken();

   if(t->getLex().compare("S") == 0){
      return new StoreNode(e);
   }

   else if(t->getLex().compare("P") == 0){
      return new PlusNode(e);   
   }

   else if(t->getLex().compare("M") == 0){
      return new MinusNode(e);
   }
  
   scan->putBackToken();

   return e;
}

AST* Parser::Factor(){
   Token* t = scan->getToken();

   if(t->getType() == number){
      istringstream in(t->getLex());
      int val;
      in >> val;
      return new NumNode(val);
   }
  
   if(t->getType() == identifier){
      istringstream  in(t->getVal());
      int val;
      in >> val;
      return new IdentifierNode(new NumNode(val), t->getLex());
   }

   if(t->getType() == keyword){
      if(t->getLex().compare("R") == 0){
         return new RecallNode();
      }

      if(t->getLex().compare("C") == 0){
         return new ClearNode();
      }
   }

   if(t->getType() == lparen){
      AST* result = Expr();
      t = scan->getToken();
      if(t->getType() == rparen){
         return result;
      }
      else{
         cout << "* Expected ) found: "
              << t->getType() << " at line: "
	      << t->getLine() << " col: "
    	      << t->getCol()
 	      << endl;
         throw ParseError;
      }
   }

   cout << "* Expected number, identifier, R, C or ( found: "
      << t->getType() << " at line "
      << t->getLine() << " col: "
      << t->getCol()
      << endl;
   throw ParseError;
}

Var::Var(string id, int val):
  id(id),
  val(val)
{}
 
Var::~Var(){
   delete past;
}
