#ifndef _MEM__AST__NODE__FUNC_TYPE__HPP_
#define _MEM__AST__NODE__FUNC_TYPE__HPP_


#include "mem/ast/node/Id.hpp"
#include "mem/ast/node/FinalId.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class FuncType: public Id
{
   public:
   static const int kTYPE = MetaKind::FUNCTION_TYPE;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   FuncType ();

   // Destructor
   virtual
   ~FuncType ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ChildCount
   GETTER(ChildCount, size_t) {return 2;}

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

   virtual
   GETTER(MemorySize, int) {return sizeof(FuncType);}


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   getChild (size_t i) const;

   virtual void
   setChild (size_t i, Node* n);


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   Node* _nodeParams;
   Node* _nodeReturnType;
};


} } }

#endif
