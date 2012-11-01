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
   static const int kTYPE = MetaKind::FUNCTION;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Func ();

   // Destructor
   virtual
   ~Func ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ChildCount
   GETTER(ChildCount, size_t) {return 5;}

   // BodyNode
   GETTER(BodyNode, Block*) {return _nodeBody;}
   SETTER(BodyNode, Block*) {
      _nodeBody = val;
      if (val != NULL) val->setParent(this);
   }

   // DecoratorNode
   GETTER(DecoratorNode, Decorator*) {return _nodeDecorator;}
   SETTER(DecoratorNode, Decorator*)
   {
      _nodeDecorator = val;
      if (val != NULL) val->setParent(this);
   }

   // NameNode
   GETTER(NameNode, Id*) {return _nodeName;}
   SETTER(NameNode, Id*)
   {
      _nodeName = val;
      if (val != NULL) val->setParent(this);
   }

   // ParamsNode
   GETTER(ParamsNode, Node*) {return _nodeParams;}
   SETTER(ParamsNode, Node*)
   {
      _nodeParams = val;
      if (val != NULL) val->setParent(this);
   }

   // ReturnTypeNode
   GETTER(ReturnTypeNode, Node*) {return _nodeReturnType;}
   SETTER(ReturnTypeNode, Node*)
   {
      _nodeReturnType = val;
      if (val != NULL) val->setParent(this);
   }

   // NextFunction
   GETTER(NextFunction, Func*) {return _next_function;}
   SETTER(NextFunction, Func*) { _next_function = val; }

   virtual
   GETTER(MemorySize, int) {return sizeof(Func);}


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   static node::VarDecl*
   createParameter (std::string name, st::Type* ty);

   virtual Node*
   getChild (size_t i) const;

   virtual void
   isValid (NodeValidator* v);

   bool
   isVirtual ();

   virtual void
   setChild (size_t i, Node* n);


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   Func* _next_function;
   Id* _nodeName;
   Block* _nodeBody;
   Decorator* _nodeDecorator;
   Node* _nodeParams;
   Node* _nodeReturnType;
};


} } }

#endif
