#ifndef ast_h
#define ast_h

#include <string>

using namespace std;

class AST {
 public:
   AST();
   virtual ~AST() = 0;
   virtual int evaluate() = 0;
   virtual string evaluateEwe() = 0;
   virtual string getId();
};

class BinaryNode : public AST {
 public:
   BinaryNode(AST* left, AST* right);
   ~BinaryNode();

   AST* getLeftSubTree() const;
   AST* getRightSubTree() const;

 private:
   AST* leftTree;
   AST* rightTree;
};

class UnaryNode : public AST {
 public:
   UnaryNode(AST* sub);
   ~UnaryNode();

   AST* getSubTree() const;

 private:
   AST* subTree;
};

class SemicolonNode : public BinaryNode{
  public:
   SemicolonNode(AST* left, AST* right);

   int evaluate();
   string evaluateEwe();
};

class AddNode : public BinaryNode {
 public:
   AddNode(AST* left, AST* right);
   
   int evaluate();
   string evaluateEwe();
};

class SubNode : public BinaryNode {
 public:
   SubNode(AST* left, AST* right);

   int evaluate();
   string evaluateEwe();
};

class TimesNode : public BinaryNode {
 public:
   TimesNode(AST* left, AST* right);
   
   int evaluate();
   string evaluateEwe();
};

class DivideNode : public BinaryNode {
 public:
   DivideNode(AST* left, AST* right);
   
   int evaluate();
   string evaluateEwe();
};

class ModNode : public BinaryNode{
 public:
   ModNode(AST* left, AST* right);

   int evaluate();
   string evaluateEwe();
};

class NumNode : public AST {
 public:
   NumNode(int n);

   int evaluate();
   string evaluateEwe();

 private:
   int val;
};

class RecallNode : public AST{
 public:
   RecallNode();

   int evaluate();
   string evaluateEwe();   
};

class ClearNode : public AST{
 public:
   ClearNode();

   int evaluate();
   string evaluateEwe();
};

class IdentifierNode : public UnaryNode{
   string lex;
 public:
   IdentifierNode(AST* sub, string lex);
 
   int evaluate();
   string evaluateEwe();  
   string getId();
};


class StoreNode : public UnaryNode {
 public:
  StoreNode(AST* sub);

  int evaluate();
  string evaluateEwe();
};  

class PlusNode : public UnaryNode {
 public:
   PlusNode(AST* sub);

   int evaluate();
   string evaluateEwe();
};

class MinusNode : public UnaryNode {
 public:
   MinusNode(AST* sub);

   int evaluate();
   string evaluateEwe();
};

#endif

