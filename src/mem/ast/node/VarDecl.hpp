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
   static const int kTYPE = Kind::VARIABLE_DECLARATION;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   VarDecl ();

   // Destructor
   virtual
   ~VarDecl ();


   //--------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER (ChildCount, size_t) {return 3;}

   virtual
   GETTER (MemorySize, int) {return sizeof(VarDecl);}

   // Name
   GETTER (Name, std::string) {return NameNode()->_value;}

   // NameCstr
   GETTER (NameCstr, const char*) {return Name().c_str();}

   // NameNode
   GETTER (NameNode, FinalId*) {return _name_node;}
   SETTER (NameNode, FinalId*)
   {
      _name_node = val;
      if (val != NULL) val->setParent(this);
   }

   // TypeNode
   GETTER (TypeNode, Node*) {return _type_node;}
   SETTER (TypeNode, Node*)
   {
      _type_node = val;
      if (val != NULL) val->setParent(this);
   }

   // ValueNode
   GETTER (ValueNode, Node*) {return _value_node;}
   SETTER (ValueNode, Node*)
   {
      _value_node = val;
      if (val != NULL) val->setParent(this);
   }


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   getChild (size_t i) const;

   virtual void
   isValid (NodeValidator* v);

   virtual void
   setChild (size_t i, Node* n);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   FinalId* _name_node;
   Node* _type_node;
   Node* _value_node;
};


} } }


#endif
