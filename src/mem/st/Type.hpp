#ifndef _MEM__ST__TYPE__HPP_
#define _MEM__ST__TYPE__HPP_


#include "mem/st/Symbol.hpp"


namespace mem { namespace st {

/**
 * A base class for all mem types.
 */
class Type: public Symbol
{
   public: Type* _parent_type;
   public: int _byte_size;

   virtual Symbol*
   gExprType() {return this;}


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(ByteSize, int) {return _byte_size;}
   SETTER(ByteSize, int) {_byte_size = val;}


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Type();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   inline Type*
   gParentType () { return this->_parent_type; }

   inline bool
   hasByteSize() {return _byte_size != -1;}

   inline void
   sParentType (Type* ty) { this->_parent_type = ty;}

   bool
   isSubclass (Type* parent);
};


} }


#endif
