#ifndef _MEM__AST__NODE__RETURN__HPP_
#define _MEM__AST__NODE__RETURN__HPP_


#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class Return : public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Return ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}

   // ValueNode
   GETTER(ValueNode, Node*) {return getChild(0);}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }

#endif
