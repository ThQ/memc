#ifndef _MEM__AST__NODE__FUNC__HPP_
#define _MEM__AST__NODE__FUNC__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Decorator.hpp"
#include "mem/ast/node/FinalId.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class Func: public Text
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   Func();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   node::Block*
   BodyNode ();

   Node*
   ParamsNode ();

   Node*
   ReturnTypeNode ();

   GETTER(DecoratorNode, Decorator*);

   GETTER(NextFunction, Func*) {return _next_function;}
   SETTER(NextFunction, Func*) {_next_function = val;}

   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   static node::Node*
   createParameter (std::string name, st::Type* ty);

   bool
   isVirtual ();

   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:
   Func* _next_function;
};

Func*
castToFunc (Node* n);


} } }

#endif
