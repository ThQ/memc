#ifndef _MEM__AST__NODE__WHILE__HPP_
#define _MEM__AST__NODE__WHILE__HPP_


#include <string>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class While : public Node
{
   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   Node*
   gConditionNode () {return this->getChild(0);}

   Node*
   gBodyNode () {return this->getChild(1);}

   //--------------------------------------------------------------------------
   // Constructors / Destrutor
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   While ();

   //--------------------------------------------------------------------------
   // PUBLIC METHODS
   //--------------------------------------------------------------------------
   public:

   virtual bool isValid();
};


} } }


#endif
