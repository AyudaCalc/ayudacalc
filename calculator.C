#include "calculator.h"
#include "parser.h"
#include "ast.h"
#include "calcex.h"
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
  
ifstream* file;

Calculator::Calculator():
   memory(0),
   cont(0),
   cont2(0),
   cont3(0),
   pas(""),
   archivo(true)
{
   if(sizeA == 0) parser = new Parser(new istringstream(read()));
   else parser = new Parser(new istringstream(read2()));
}

void Calculator::eval() {
   try{
      AST* tree = parser->parse();
      if(comp) generateEwe(tree);
      delete tree;
   }catch(...){}
   delete parser;
}

void Calculator::store(int val) {
   memory = val;
}

int Calculator::plus(int val) {
   memory += val;
   return memory;
}

int Calculator::minus(int val) {
   memory -= val;
   return memory;
}

int Calculator::recall() {
   return memory;
}

int Calculator::clear() {
   return memory = 0;
}

string Calculator::read(){
   cout << "> ";
   getline(cin,line);
   return line;
}

string Calculator::read2(){
   if(archivo){
      file = new ifstream(archivos[cont++]);
      archivo = false;
   }
   if(file->is_open()){
      if(!getline(*file,line)){
         archivo=true;
         delete file;
      }
   }
   else{
      cout << "file " << archivos[cont-1] << " not found" << endl;
      delete file;
      archivo = true;
   }
   return line;
}

bool Calculator::fileExists(const char* fileName)
{
    ifstream file(fileName);
    return file.good();
}

string Calculator::convert(int val){
   stringstream stream;
   string operato;
   stream << val;
   operato = stream.str();
   return operato;
}

void Calculator::generateEwe(AST* f){
   string stack = f->evaluateEwe();
   cout << stack << endl;
/*  
   istream* in = new istringstream(stack);

   ofstream file;
   
   if(sizeA==0){
      string name2 = "a"+convert(cont2++)+".ewe";
      const char* name = name2.c_str();
      file.open(name);
   }
   else{
//      char* array2 = archivos[cont2];
//      string new1 = array2;
//      if (new1.compare(pas) == 0) cont2++;
//      pas = new1;
      char* array = archivos[cont2];
      int a = 0;
      string ans = "";
      while(array[a]!='.' || array[a+1] != 'c' || array[a+2] != 'a' || array[a+3] != 'l' || array[a+4] != 'c'){
         ans += array[a];
         a++;
      }
      string ans2 = "";
      ans2 += ans+".ewe";
      const char* name = ans2.c_str();
      if(fileExists(name)) ans+=convert(++cont3);
      ans+=".ewe";
      name = ans.c_str();
      file.open(name); 
   }

   //instructions before examining the tree
   //if an extra identifier is needed see example 4
   file << "start:\n"
        << "#Instructions before examining the tree \n"
        << "\t sp \t := 1000 \n"
        << "\t one \t := 1 \n"
        << "\t zero \t := 0 \n";
   
   file << "\t memory  := zero \n\n";

   //start examinig the tree
   file << "#start examining the tree\n";

   int c = 0;
   int d = stack.length();
   char a;
   int option;
   string number;
   string num = "";
   string id = "";
   bool boolean = true;

   while(true){
      a = in->get();    
      
      if(in->eof() || a == -1) break;
      else if(a == 'N'){
         option = 0;
         a = in->get();
         num += a;
         while(boolean){
            a = in->peek();
	    if(a>='0' && a<='9'){
               a = in->get();
               num += a;
            }else boolean = false;
         }
         number = num;
         num = "";
         boolean = true;
      }
      else if(a == 'I'){
         option = 1;
         a = in->get();
         num += a;
         while(boolean){
            a = in->peek();
            if(a != ' ' && (a>='a' && a<='z' || a>='A' && a<='Z')){
               a = in->get();
	       num += a;
            }else boolean = false; 
         }
         id = num;
         num = "";
         boolean = true;
      }
      else if(a == 'R') option = 2;
      else if(a == 'C') option = 3;
      else if(a == 'S') option = 4;
      else if(a == 'M') option = 5;
      else if(a == 'P') option = 6;
      else if(a == '*') option = 7;
      else if(a == '+') option = 8;
      else if(a == '-') option = 9;
      else if(a == '/') option = 10;
      else if(a == '%') option = 11;

      switch(option){
         case 0:
            //push(number)
            file << "#push(number)\n"
                 << "\t sp \t   := sp - one \n"
                 << "\t operator1 := " << number << " \n"
                 << "\t M[sp+0]   := operator1 \n\n";
            break;
         case 1:
            //Assign
            file << "#Assign\n"
                 << "\t " << id << " \t   := M[sp+0] \n\n";
            break;
         case 2:
            //Recall
            file << "#Recall\n"
                 << "\t sp \t   := sp - one \n"
                 << "\t M[sp+0]   := memory \n\n";
            break;
         case 3:
            //Clear
            file << "#Clear\n"
                 << "\t memory    := zero \n"
                 << "\t sp \t   := sp - one \n"
                 << "\t M[sp+0]   := memory \n\n";
            break;
         case 4:
            //Store
            file << "#Store\n"
                 << "\t memory    := M[sp+0] \n\n";
            break;
         case 5:
            //Memory minus
            file << "#Memory minus\n"
                 << "\t operator2 := M[sp+0] \n"
                 << "\t memory    := memory - operator2 \n"
                 << "\t M[sp+0]   := memory \n\n";
            break;
         case 6:
            //Memory plus
            file << "#Memory plus\n"
                 << "\t operator2 := M[sp+0] \n"
                 << "\t memory    := memory + operpator2 \n"
                 << "\t M[sp+0]   := memory \n\n";
            break;
         case 7:
            //Times
            file << "#Times\n"
                 << "\t operator2 := M[sp+0] \n"
                 << "\t operator1 := M[sp+1] \n"
                 << "\t operator1 := operator1 * operator2 \n"
                 << "\t sp \t   := sp + one \n"
                 << "\t M[sp+0]   := operator1 \n\n";
            break;
         case 8:
            //Add
            file << "#Add\n"
                 << "\t operator2 := M[sp+0] \n"
                 << "\t operator1 := M[sp+1] \n"
                 << "\t operator1 := operator1 + operator2 \n"
                 << "\t sp \t   := sp + one \n"
                 << "\t M[sp+0]   := operator1 \n\n";
            break;
         case 9:
            //Sub
            file << "#Sub\n"
                 << "\t operator2 := M[sp+0] \n"
                 << "\t operator1 := M[sp+1] \n"
                 << "\t operator1 := operator1 - operator2 \n"
                 << "\t sp \t   := sp + one \n"
                 << "\t M[sp+0]   := operator1 \n\n";
            break;
         case 10:
            //Divide
            file << "#Divide\n"
                 << "\t operator2 := M[sp+0] \n"
                 << "\t operator1 := M[sp+1] \n"
                 << "\t operator1 := operator1 / operator2 \n"
                 << "\t sp \t   := sp + one \n"
                 << "\t M[sp+0]   := operator1 \n\n";
            break;
         case 11:
            //Mod
            file << "#Mod\n"
                 << "\t operator2 := M[sp+0] \n"
                 << "\t operator1 := M[sp+1] \n"
                 << "\t operator1 := operator1 % operator2 \n"
                 << "\t sp \t   := sp + one \n"
                 << "\t M[sp+0]   := operator1 \n\n";
            break;
      }
   }

   //Write result
   file << "#Write result\n"
   << "\t operator1 := M[sp+0] \n"
   << "\t sp \t   := sp - one \n"
   << "\t writeInt(operator1) \n\n";

   //End of the program
   file << "#End of the program\n"
   << "end: \t halt\n\n";

   //equs
   file << "#equs\n"
   << "equ \t memory \t M[0] \n"
   << "equ \t one \t\t M[1] \n"
   << "equ \t zero \t\t M[2] \n"
   << "equ \t operator1 \t M[3] \n"
   << "equ \t operator2 \t M[4] \n"
   << "equ \t sp \t\t M[5] \n"
   << "equ \t IDENTIFIER \t M[6] \n"
   << "equ \t stack \t\t M[1000]";

   file.close();
   delete in;
*/
}
