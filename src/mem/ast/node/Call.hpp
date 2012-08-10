#ifndef _MEM__AST__NODE__CALL__HPP_
#define _MEM__AST__NODE__CALL__HPP_


#include <string>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class Call : public Node
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Call ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // Caller
   GETTER(Caller, st::Symbol*) {return _caller;}
   SETTER(Caller, st::Symbol*) {_caller = val;}

   // CallerNode
   GETTER(CallerNode, Node*) {return getChild(0);}

   // IsInstanceCall
   GETTER(IsInstanceCall, bool) {return _is_instance_call;}
   SETTER(IsInstanceCall, bool) {_is_instance_call = val;}

   // ParamsNode
   GETTER(ParamsNode, Node*) {return getChild(1);}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   bool
   hasParamsNode() {return ChildCount()==2;}

   virtual void
   isValid(NodeValidator* vld);


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   st::Symbol* _caller;
   bool _is_instance_call;
};


} } }


#endif
