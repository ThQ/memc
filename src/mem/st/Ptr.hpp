#ifndef _MEM__ST__PTR__HPP
#define _MEM__ST__PTR__HPP


#include "mem/st/Type.hpp"


namespace mem { namespace st {


/**
 * A symbol to represent pointers.
 */
class Ptr : public Type
{
   // -------------------------------------------------------------------------
   // FIELDS
   // -------------------------------------------------------------------------
   public:

   Type* _base_type;
   int _ptr_level;


   // -------------------------------------------------------------------------
   // PROPERTIES
   // -------------------------------------------------------------------------
   public:

   // BaseType
   GETTER(BaseType, Type*) {return _base_type;}
   SETTER(BaseType, Type*) {_base_type = val;}

   // IndirectionLevel
   GETTER(IndirectionLevel, int) {return _ptr_level;}
   SETTER(IndirectionLevel, int) {_ptr_level = val;}


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

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Ptr");return false;}

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
