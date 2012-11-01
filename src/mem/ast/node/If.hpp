#ifndef _MEM__AST__NODE__IF__HPP_
#define _MEM__AST__NODE__IF__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


// An if node represents a condition and an associated block. It can have an
// optional else condition block associated.
//
// Syntax:
//    if <Condition>
//       <IfBlock>
//    else
//       [ElseBlock]
class If: public Node
{
   public:
   static const int kTYPE = MetaKind::IF;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   If ();

   // Destructor
   virtual
   ~If ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ChildCount
   GETTER(ChildCount, size_t) {return 3;}

   // ConditionNode
   GETTER(ConditionNode, node::Node*) {return _nodeCondition;}
   SETTER(ConditionNode, node::Node*)
   {
      _nodeCondition = val;
      if (val != NULL) val->setParent(this);
   }

   // IfBlockNode
   GETTER(IfBlockNode, node::Block*) {return _nodeIfBlock;}
   SETTER(IfBlockNode, node::Block*)
   {
      _nodeIfBlock = val;
      if (val != NULL) val->setParent(this);
   }

   // ElseBlockNode
   GETTER(ElseBlockNode, node::Block*) {return _nodeElseBlock;}
   SETTER(ElseBlockNode, node::Block*)
   {
      _nodeElseBlock = val;
      if (val != NULL) val->setParent(this);
   }

   virtual
   GETTER(MemorySize, int) {return sizeof(If);}


   //==========================================================================
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   getChild (size_t i) const;

   inline bool
   hasConditionNode () {return ConditionNode() != NULL;}

   inline bool
   hasElseBlockNode () {return ElseBlockNode() != NULL;}

   virtual void
   isValid (NodeValidator* v);

   virtual void
   setChild (size_t i, Node* n);


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   node::Node* _nodeCondition;
   node::Block* _nodeIfBlock;
   node::Block* _nodeElseBlock;
};

} } }

#endif
