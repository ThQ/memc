#ifndef _MEM__AST__NODE__NEW__HPP_
#define _MEM__AST__NODE__NEW__HPP_


#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class New : public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   New ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}

   // TypeNode
   GETTER(TypeNode, Node*) {return getChild(0);}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }

#endif
