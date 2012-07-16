#ifndef _MEM__AST__NODE__WHILE__HPP_
#define _MEM__AST__NODE__WHILE__HPP_


#include <string>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class While : public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   While ();


   //--------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   //--------------------------------------------------------------------------
   public:

   Node*
   ConditionNode () {return this->getChild(0);}

   Node*
   BodyNode () {return this->getChild(1);}


   //--------------------------------------------------------------------------
   // PUBLIC METHODS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }


#endif
