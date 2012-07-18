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

   // ConditionNode
   GETTER(ConditionNode, Node*) {return this->getChild(0);}

   // BodyNode
   GETTER(BodyNode, Node*) {return this->getChild(1);}


   //--------------------------------------------------------------------------
   // PUBLIC METHODS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }


#endif
