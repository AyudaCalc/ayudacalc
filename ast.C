#include "ast.h"
#include <iostream>
#include "calculator.h"
#include <sstream>
#include <string>

using namespace std;

// for debug information uncomment
//#define debug

AST::AST() {}

AST::~AST() {}

string AST::getId() { return "";}

BinaryNode::BinaryNode(AST* left, AST* right):
   AST(),
   leftTree(left),
   rightTree(right)
{}

BinaryNode::~BinaryNode() {
#ifdef debug
   cout << "In BinaryNode destructor" << endl;
#endif

   try {
      delete leftTree;
   } catch (...) {}

   try {
      delete rightTree;
   } catch(...) {}
}
   
AST* BinaryNode::getLeftSubTree() const {
   return leftTree;
}

AST* BinaryNode::getRightSubTree() const {
   return rightTree;
}

UnaryNode::UnaryNode(AST* sub):
   AST(),
   subTree(sub)
{}

UnaryNode::~UnaryNode() {
#ifdef debug
   cout << "In UnaryNode destructor" << endl;
#endif

   try {
      delete subTree;
   } catch (...) {}
}
   
AST* UnaryNode::getSubTree() const {
   return subTree;
}

SemicolonNode::SemicolonNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int SemicolonNode::evaluate() { 
   return getLeftSubTree()->evaluate(); 
}

string SemicolonNode::evaluateEwe(){
   return getLeftSubTree()->evaluateEwe()+getRightSubTree()->evaluateEwe()+";";
}

AddNode::AddNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int AddNode::evaluate() {
   return getLeftSubTree()->evaluate() + getRightSubTree()->evaluate();
}

string AddNode::evaluateEwe() {
   return getLeftSubTree()->evaluateEwe()+getRightSubTree()->evaluateEwe()+"+";
}

SubNode::SubNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int SubNode::evaluate() {
   return getLeftSubTree()->evaluate() - getRightSubTree()->evaluate();
}

string SubNode::evaluateEwe() {
   return getLeftSubTree()->evaluateEwe()+getRightSubTree()->evaluateEwe()+"-";
}

TimesNode::TimesNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int TimesNode::evaluate() {
   return getLeftSubTree()->evaluate() * getRightSubTree()->evaluate();
}

string TimesNode::evaluateEwe() {
   return getLeftSubTree()->evaluateEwe()+getRightSubTree()->evaluateEwe()+"*";
}

DivideNode::DivideNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int DivideNode::evaluate() {
   return getLeftSubTree()->evaluate() / getRightSubTree()->evaluate();
}

string DivideNode::evaluateEwe() {
   return getLeftSubTree()->evaluateEwe()+getRightSubTree()->evaluateEwe()+"/";
}

ModNode::ModNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int ModNode::evaluate(){
   return getLeftSubTree()->evaluate() % getRightSubTree()->evaluate();
}

string ModNode::evaluateEwe() {
   return getLeftSubTree()->evaluateEwe()+getRightSubTree()->evaluateEwe()+"%";
}

NumNode::NumNode(int n) :
   AST(),
   val(n)
{}

int NumNode::evaluate() {
   return val;
}

string NumNode::evaluateEwe() {
   stringstream stream;
   int numero = evaluate();
   string operato;
   stream << numero;
   operato = stream.str();
   return "N"+operato;
}

IdentifierNode::IdentifierNode(AST* sub, string lex):
  UnaryNode(sub),
  lex(lex)
{}

int IdentifierNode::evaluate(){
   return getSubTree()->evaluate();
}  

string IdentifierNode::evaluateEwe() {
   return getSubTree()->evaluateEwe()+"I"+lex+" ";
}

string IdentifierNode::getId(){
   return lex;
}

StoreNode::StoreNode(AST* sub) :
  UnaryNode(sub)
{}

int StoreNode::evaluate() {
 int value = getSubTree()->evaluate();
 calc->store(value);
 return value;
} 

string StoreNode::evaluateEwe() {
   return getSubTree()->evaluateEwe()+"S";
}

PlusNode::PlusNode(AST* sub):
  UnaryNode(sub)
{}

int PlusNode::evaluate(){
   return calc->plus(getSubTree()->evaluate());
}

string PlusNode::evaluateEwe() {
   return getSubTree()->evaluateEwe()+"P";
}

MinusNode::MinusNode(AST* sub):
  UnaryNode(sub)
{}

int MinusNode::evaluate(){
   return calc->minus(getSubTree()->evaluate());
}

string MinusNode::evaluateEwe() {
   return getSubTree()->evaluateEwe()+"M";
}

RecallNode::RecallNode() : AST() { }

int RecallNode::evaluate() {
    return calc->recall();
}

string RecallNode::evaluateEwe() {
   return "R";
}

ClearNode::ClearNode() : AST() {}

int ClearNode::evaluate(){
    return calc->clear();
}

string ClearNode::evaluateEwe() {
   return "C";
}
