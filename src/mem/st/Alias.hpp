#ifndef _MEM__ST__ALIAS__HPP_
#define _MEM__ST__ALIAS__HPP_


#include "mem/st/Namespace.hpp"


namespace mem { namespace st {


class Alias : public Symbol
{
   protected:

   Namespace* _aliased;


   // -------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   // -------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Alias();

   // -------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   // -------------------------------------------------------------------------
   public:

   GETTER(Aliased, Namespace*) {return _aliased;}
   SETTER(Aliased, Namespace*) {_aliased = val;}


   // -------------------------------------------------------------------------
   // PUBLIC METHODS
   // -------------------------------------------------------------------------
   public:

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Alias");return false;}

   virtual Symbol*
   getChild (std::string name);
};

} }


#endif
