#ifndef _MEM__ST__TYPE__HPP_
#define _MEM__ST__TYPE__HPP_


#include "mem/st/Symbol.hpp"


namespace mem { namespace st {

/**
 * A base class for all mem types.
 */
class Type: public Symbol
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Type();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(ByteSize, int) {return _byte_size;}
   SETTER(ByteSize, int) {_byte_size = val;}

   GETTER(ParentType, Type*) {return _parent_type;}
   SETTER(ParentType, Type*) {_parent_type = val;}

   virtual Symbol*
   gExprType() {return this;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   inline bool
   hasByteSize() {return _byte_size != -1;}

   bool
   isSubclass (Type* parent);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   Type* _parent_type;
   int _byte_size;
};


} }


#endif
