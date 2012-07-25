#ifndef _MEM__AST__NODE__ARRAY__HPP_
#define _MEM__AST__NODE__ARRAY__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Text.hpp"


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


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};

} } }

#endif
