#ifndef _MEM__AST__NODE__CALL__HPP_
#define _MEM__AST__NODE__CALL__HPP_


#include <string>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class Call : public Node
{
   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   Node*
   gCallerNode () {return this->getChild(0);}

   Node*
   gParamsNode () {return this->getChild(1);}

   bool
   hasParamsNode() {return this->gChildCount()==2;}

   //--------------------------------------------------------------------------
   // Constructors / Destrutors
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Call ();

   //--------------------------------------------------------------------------
   // PUBLIC METHODS
   //--------------------------------------------------------------------------
   public:

   virtual void isValid(NodeValidator* vld);
};


} } }


#endif
