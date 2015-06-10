#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include "calculator.h"
#include "scanner.h"
#include "parser.h"

using namespace std;

Calculator* calc;

char** variables;   
char** globales;
char** archivos;
int sizeV;
int sizeG;
int sizeA;
bool comp;

bool assign(char* assign){
   istream* in = new istringstream(assign);
   Scanner* scan = new Scanner(in);
   bool result = true;

   Token* t = scan->getToken();

   if(t->getType() == identifier){
      t = scan->getToken();
   }else result = false;
   
   if(result && t->getType() == equals){
      t = scan->getToken();
   } else result = false;
  
   if(result && t->getType() == number){
      t = scan->getToken();
   }else result = false;
   
   if(result && t->getType() != eol) result = false;
   
   delete scan;
   delete t;
   return result;
}

int main(int argc, char *argv[], char *envp[]){

   variables = new char*[argc];   
   globales = new char*[10];
   archivos = new char*[argc];
   sizeV = 0;
   sizeG = 0;
   sizeA = 0;
   comp = false;
   
   bool up = false; 

   for (int c=0; envp[c]; c++){
      if(strstr(envp[c],"CALCVAL_")){
	 envp[c] = envp[c] + 8;
         globales[sizeG++] = envp[c];
      }      
   }

   for(int c=1;c<argc;c++){
      if(strstr("-v",argv[c])){
	 if(c+1 < argc && assign(argv[c+1])) variables[sizeV++] = argv[++c];
         else up = true;
      }
      else if(strstr("-c",argv[c])) comp = true;
      else if(strstr(argv[c],".calc")) archivos[sizeA++] = argv[c];
      else up = true;
   }
   
   if(!up){
      calc = new Calculator(); 
      calc->eval();
      delete calc;
   }
   else cout << "missing or unknown parameter" << endl;

   delete variables;
   delete globales;
   delete archivos;
}
