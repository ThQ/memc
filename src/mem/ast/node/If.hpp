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
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ConditionNode
   GETTER(ConditionNode, node::Node*) {return getChild(0);}

   // IfBlockNode
   GETTER(IfBlockNode, node::Node*) {return static_cast<Block*>(getChild(1));}

   // ElseBlockNode
   GETTER(ElseBlockNode, node::Node*) {return static_cast<Block*>(getChild(2));}

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   inline bool
   hasConditionNode () {return ConditionNode() != NULL;}

   inline bool
   hasElseBlockNode () {return ElseBlockNode() != NULL;}

   virtual void
   isValid (NodeValidator* v);
};

} } }

#endif
