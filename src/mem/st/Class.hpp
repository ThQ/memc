#ifndef _MEM__ST__CLASS__HPP
#define _MEM__ST__CLASS__HPP


#include "mem/st/Type.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace st {


class Class : public Type
{
   // -------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   // -------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Class ();

   /**
    * Destructor.
    */
   virtual
   ~Class();


   // -------------------------------------------------------------------------
   // PUBLIC METHODS
   // -------------------------------------------------------------------------
   public:

   /**
    * Returns the parent class in the type hierarchy.
    */
   Class*
   gParentClass () const { return static_cast<Class*>(this->_parent);}


   /**
    * Checks wether a class depends on another (directly or indirectly).
    */
    bool
    isDependingOn (Class* cls);
};


} }


#endif
