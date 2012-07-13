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
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid(NodeValidator* v);

   inline Node*
   gTypeNode() {return getChild(0);}
};


} } }

#endif
