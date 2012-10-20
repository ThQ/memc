#ifndef _MEM__AST__NODE__TUPLE_TYPE__HPP_
#define _MEM__AST__NODE__TUPLE_TYPE__HPP_


#include "mem/ast/node/NodeList.hpp"
#include "mem/ast/node/Type.hpp"


namespace mem { namespace ast { namespace node {

// A tuple type declaration
//
// Syntax:
//    (type1, type2, ..., typeN)
// Ex:
//    (int, char, long)
class TupleType : public Type
{
   public:
   static const int kTYPE = MetaKind::TUPLE_TYPE;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   TupleType ();


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   virtual void
   addChild (Node* n);

   virtual Node*
   getChild (size_t i) const;

   void
   insertChild (Node* n);


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(ChildCount, size_t) {return _types.size();}

   virtual
   GETTER(MemorySize, int) {return sizeof(TupleType);}


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   std::vector<Node*> _types;
};


} } }

#endif
