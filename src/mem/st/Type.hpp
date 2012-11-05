#ifndef _MEM__ST__TYPE__HPP_
#define _MEM__ST__TYPE__HPP_


#include <vector>
#include "mem/st/Symbol.hpp"


namespace mem { namespace st {


// A base class for all mem types.
class Type: public Symbol
{
   public:
   static const int kTYPE = MetaKind::TYPE;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Type();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ParentType
   GETTER(ParentType, Type*) {return _parent_type;}
   SETTER(ParentType, Type*) {_parent_type = val;}

   virtual Symbol*
   gExprType() {return this;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual bool
   canCastTo (Type* symDestType) const {
      DEBUG_PRINTF("canCast %s to %s ?\n", _name.c_str(), symDestType->gQualifiedNameCstr());
      return this->isSubTypeOf(symDestType);
   }


   inline bool
   hasByteSize() {return ByteSize() > 0;}

   bool
   isSubTypeOf (Type* parent) const;


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   Type* _parent_type;
};

typedef std::vector<st::Type*> TypeVector;

} }


#endif
