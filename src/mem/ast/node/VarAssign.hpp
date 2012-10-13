#ifndef _MEM__AST__NODE__VAR_ASSIGN__HPP_
#define _MEM__AST__NODE__VAR_ASSIGN__HPP_


#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class VarAssign : public Node
{
   public:
   static const int kTYPE = MetaKind::VARIABLE_ASSIGNMENT;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   VarAssign ();

   // Destructor
   virtual
   ~VarAssign ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ChildCount
   virtual
   GETTER (ChildCount, size_t) {return 2;}

   // MemorySize
   virtual
   GETTER (MemorySize, int) {return sizeof(VarAssign);}

   // NameNode
   GETTER (NameNode, Node*) {return _name_node;}
   SETTER (NameNode, Node*)
   {
      _name_node = val;
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

   Node* _name_node;
   Node* _value_node;
};


} } }

#endif
