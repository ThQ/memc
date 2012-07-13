#ifndef _MEM__ST__TYPE__HPP_
#define _MEM__ST__TYPE__HPP_


#include "mem/st/Symbol.hpp"


namespace mem { namespace st {


class Type: public Symbol
{
   public: Type* _parent_type;

   virtual Symbol*
   gExprType() {return this;}

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

   inline void
   sParentType (Type* ty) { this->_parent_type = ty;}

   bool
   isSubclass (Type* parent);
};


} }


#endif
