#ifndef _MEM__AST__NODE__TUPLE_TYPE__HPP_
#define _MEM__AST__NODE__TUPLE_TYPE__HPP_


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
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   virtual
   GETTER(MemorySize, int) {return sizeof(TupleType);}
};


} } }

#endif
