#ifndef _MEM__AST__NODE__VAR_ASSIGN__HPP_
#define _MEM__AST__NODE__VAR_ASSIGN__HPP_


#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class VarAssign : public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   VarAssign ();

   //--------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   //--------------------------------------------------------------------------
   public:

   inline Text*
   NameNode() {return static_cast<Text*>(getChild(0));}

   inline Node*
   ValueNode() {return getChild(1);}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }

#endif
