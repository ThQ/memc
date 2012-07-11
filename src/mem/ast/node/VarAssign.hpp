#ifndef _MEM__AST__NODE__VAR_ASSIGN__HPP_
#define _MEM__AST__NODE__VAR_ASSIGN__HPP_


#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class VarAssign : public Node
{

   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   Node* gNameNode() {return getChild(0);}
   Node* gValueNode() {return getChild(1);}

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   VarAssign ();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual bool
   isValid();
};


} } }

#endif
