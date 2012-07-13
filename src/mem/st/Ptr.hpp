#ifndef _MEM__ST__PTR__HPP
#define _MEM__ST__PTR__HPP


#include "mem/st/Type.hpp"


namespace mem { namespace st {


/**
 * A symbol to represent pointers.
 */
class Ptr : public Type
{
   public:

   int _ptr_level;
   Type* _base_type;

   inline Type*
   gBaseType() {return _base_type;}

   inline void
   sBaseType (Type* base_type) {_base_type = base_type;}


   // -------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   // -------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Ptr ();

   /**
    * Destructor.
    */
   virtual
   ~Ptr ();

   // -------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   // -------------------------------------------------------------------------
   public:

   /**
    * Returns a child by its name.
    *
    * We have to override Symbol::getChild here because a pointer does not have
    * children of its own, instead it returns its base type's children. It acts
    * as a proxy.
    */
   inline Symbol*
   getChild (std::string name) {return this->_base_type->getChild(name);}
};


} }

#endif
