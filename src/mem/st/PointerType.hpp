#ifndef _MEM__ST__PTR__HPP
#define _MEM__ST__PTR__HPP


#include "mem/st/Type.hpp"


namespace mem { namespace st {


/**
 * A base class for pointer types.
 */
class PointerType : public Type
{
   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   Type* _pointed_type;
   int _ptr_level;


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // BaseType
   GETTER(PointedType, Type*) {return _pointed_type;}
   SETTER(PointedType, Type*)
   {
      _pointed_type = val;
      if(val->isPointerType())
      {
         _ptr_level = static_cast<PointerType*>(val)->IndirectionLevel() + 1;
      }
   }

   // IndirectionLevel
   GETTER(IndirectionLevel, int) {return _ptr_level;}
   SETTER(IndirectionLevel, int) {_ptr_level = val;}


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   PointerType ();

   /**
    * Destructor.
    */
   virtual
   ~PointerType ();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
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
   getChild (std::string name) {return _pointed_type->getChild(name);}

   Type*
   getNonPointerParent ();
};


} }

#endif
