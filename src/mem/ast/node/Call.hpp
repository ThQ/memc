#ifndef _MEM__AST__NODE__CALL__HPP_
#define _MEM__AST__NODE__CALL__HPP_


#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/NodeList.hpp"


namespace mem { namespace ast { namespace node {


class Call : public Node
{
   public:
   static const int kTYPE = MetaKind::CALL;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Call ();

   // Destructor
   virtual
   ~Call ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // Caller
   GETTER(Caller, st::Symbol*) {return _symCaller;}
   SETTER(Caller, st::Symbol*) {_symCaller = val;}

   // CallerNode
   GETTER(CallerNode, Node*) {return _nodeCaller;}
   SETTER(CallerNode, Node*)
   {
      _nodeCaller = val;
      if (val != NULL) val->setParent(this);
   }

   // ChildCount
   virtual
   GETTER (ChildCount, size_t) {return 2;}

   // IsInstanceCall
   GETTER(IsInstanceCall, bool) {return _is_instance_call;}
   SETTER(IsInstanceCall, bool) {_is_instance_call = val;}

   // MemorySize
   virtual
   GETTER(MemorySize, int) {return sizeof(Call);}

   // ParamsNode
   GETTER(ParamsNode, NodeList*) {return _nodeParams;}
   SETTER(ParamsNode, NodeList*)
   {
      _nodeParams = val;
      if (val != NULL) val->setParent(this);
   }


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   bool
   hasParamsNode() {return ChildCount()==2;}

   virtual Node*
   getChild (size_t i) const;

   void
   insertParam (Node* node);

   virtual void
   isValid(NodeValidator* vld);

   virtual void
   setChild (size_t i, Node* n);


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   bool _is_instance_call;
   Node* _nodeCaller;
   NodeList* _nodeParams;
   st::Symbol* _symCaller;
};


} } }


#endif
