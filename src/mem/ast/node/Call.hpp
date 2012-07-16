#ifndef _MEM__AST__NODE__CALL__HPP_
#define _MEM__AST__NODE__CALL__HPP_


#include <string>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class Call : public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Call ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   Node*
   CallerNode () {return this->getChild(0);}

   Node*
   ParamsNode () {return this->getChild(1);}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   bool
   hasParamsNode() {return this->gChildCount()==2;}

   virtual void
   isValid(NodeValidator* vld);
};


} } }


#endif
