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
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}

   // NameNode
   GETTER(NameNode, Text*) {return static_cast<Text*>(getChild(0));}

   // ValueNode
   GETTER(ValueNode, Node*) {return getChild(1);}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);
};


} } }

#endif
