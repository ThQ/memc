#ifndef _MEM__AST__NODE__VARDECL__HPP_
#define _MEM__AST__NODE__VARDECL__HPP_


#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/FinalId.hpp"


namespace mem { namespace ast { namespace node {

// A node for variable declarations
//
// Syntax:
//    <Name> :[Type] = [Value]
//
// Ex:
//    my_int :int = 1
class VarDecl : public Node
{
   public:
   static const int kTYPE = MetaKind::VARIABLE_DECLARATION;


   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   VarDecl ();

   // Destructor
   virtual
   ~VarDecl ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER (ChildCount, size_t) {return 3;}

   virtual
   GETTER (MemorySize, int) {return sizeof(VarDecl);}

   // Name
   GETTER (Name, std::string) {return NameNode()->Value();}

   // NameCstr
   GETTER (NameCstr, const char*) {return Name().c_str();}

   // NameNode
   GETTER (NameNode, FinalId*) {return _nodeName;}
   SETTER (NameNode, FinalId*)
   {
      _nodeName = val;
      if (val != NULL) val->setParent(this);
   }

   // TypeNode
   GETTER (TypeNode, Node*) {return _nodeType;}
   SETTER (TypeNode, Node*)
   {
      _nodeType = val;
      if (val != NULL) val->setParent(this);
   }

   // ValueNode
   GETTER (ValueNode, Node*) {return _nodeValue;}
   SETTER (ValueNode, Node*)
   {
      _nodeValue = val;
      if (val != NULL) val->setParent(this);
   }


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   getChild (size_t i) const;

   virtual void
   isValid (NodeValidator* v);

   virtual void
   setChild (size_t i, Node* n);


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   FinalId* _nodeName;
   Node* _nodeType;
   Node* _nodeValue;
};


} } }


#endif
