#ifndef _MEM__AST__NODE__CALL__HPP_
#define _MEM__AST__NODE__CALL__HPP_


#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/NodeList.hpp"


namespace mem { namespace ast { namespace node {


class Call : public Node
{
   public:
   static const int kTYPE = Kind::CALL;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Call ();

   // Destructor
   virtual
   ~Call ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // Caller
   GETTER(Caller, st::Symbol*) {return _caller;}
   SETTER(Caller, st::Symbol*) {_caller = val;}

   // CallerNode
   GETTER(CallerNode, Node*) {return _caller_node;}
   SETTER(CallerNode, Node*)
   {
      _caller_node = val;
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
   GETTER(ParamsNode, NodeList*) {return _params_node;}
   SETTER(ParamsNode, NodeList*)
   {
      _params_node = val;
      if (val != NULL) val->setParent(this);
   }


   //--------------------------------------------------------------------------
   // FUNCTIONS
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


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   st::Symbol* _caller;
   Node* _caller_node;
   bool _is_instance_call;
   NodeList* _params_node;
};


} } }


#endif
