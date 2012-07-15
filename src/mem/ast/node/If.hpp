#ifndef _MEM__AST__NODE__IF__HPP_
#define _MEM__AST__NODE__IF__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


/**
 * An if node represents a condition and an associated block. It can have an
 * optional else condition block associated.
 *
 * > if <bool expression>
 * >    <block>
 * > else
 * >    <block>
 */
class If: public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   If();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   inline node::Node*
   gConditionNode () {return getChild(0);}

   inline node::Node*
   gIfBlockNode () {return static_cast<Block*>(getChild(1));}

   inline node::Block*
   gElseBlockNode () {return static_cast<Block*>(getChild(2));}

   inline bool
   hasConditionNode () {return gConditionNode() != NULL;}

   inline bool
   hasElseBlockNode () {return gElseBlockNode() != NULL;}

   virtual void
   isValid (NodeValidator* v);
};

} } }

#endif
