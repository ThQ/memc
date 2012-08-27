#ifndef _MEM__AST__NODE__FUNC__HPP_
#define _MEM__AST__NODE__FUNC__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Decorator.hpp"
#include "mem/ast/node/Id.hpp"
#include "mem/ast/node/FinalId.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/VarDecl.hpp"


namespace mem { namespace ast { namespace node {


class Func: public Text
{
   public:
   static const int kTYPE = Kind::FUNCTION;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Func ();

   // Destructor
   virtual
   ~Func ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ChildCount
   GETTER(ChildCount, size_t) {return 5;}

   // BodyNode
   GETTER(BodyNode, Block*) {return _body_node;}
   SETTER(BodyNode, Block*) {
      _body_node = val;
      if (val != NULL) val->setParent(this);
   }

   // DecoratorNode
   GETTER(DecoratorNode, Decorator*) {return _decorator_node;}
   SETTER(DecoratorNode, Decorator*)
   {
      _decorator_node = val;
      if (val != NULL) val->setParent(this);
   }

   // NameNode
   GETTER(NameNode, Id*) {return _name_node;}
   SETTER(NameNode, Id*)
   {
      _name_node = val;
      if (val != NULL) val->setParent(this);
   }

   // ParamsNode
   GETTER(ParamsNode, Node*) {return _params_node;}
   SETTER(ParamsNode, Node*)
   {
      _params_node = val;
      if (val != NULL) val->setParent(this);
   }

   // ReturnTypeNode
   GETTER(ReturnTypeNode, Node*) {return _return_type_node;}
   SETTER(ReturnTypeNode, Node*)
   {
      _return_type_node = val;
      if (val != NULL) val->setParent(this);
   }

   // NextFunction
   GETTER(NextFunction, Func*) {return _next_function;}
   SETTER(NextFunction, Func*) { _next_function = val; }

   virtual
   GETTER(MemorySize, int) {return sizeof(Func);}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   static node::VarDecl*
   createParameter (std::string name, st::Type* ty);

   virtual Node*
   getChild (size_t i) const;

   bool
   isVirtual ();

   virtual void
   setChild (size_t i, Node* n);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   Id* _name_node;
   Func* _next_function;
   Block* _body_node;
   Decorator* _decorator_node;
   Node* _params_node;
   Node* _return_type_node;
};


} } }

#endif
