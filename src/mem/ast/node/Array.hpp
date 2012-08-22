#ifndef _MEM__AST__NODE__ARRAY__HPP_
#define _MEM__AST__NODE__ARRAY__HPP_


#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class Array: public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Array();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------

   GETTER(TypeNode, Node*) {return getChild(0);}
   GETTER(LengthNode, Node*) {return getChild(1);}

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}

   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};

static Array*
castToArray (Node* n);

} } }

#endif
