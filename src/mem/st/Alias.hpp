#ifndef _MEM__ST__ALIAS__HPP_
#define _MEM__ST__ALIAS__HPP_


#include "mem/st/Namespace.hpp"


namespace mem { namespace st {


// A symbol that aliases a namespace.
//
// This is currently used to use only the last name part of the module imported.
// > use m.io.File
// can then be used as `File.xxx'.
//
// FIXME: Should be extended to alias any symbol.
class Alias : public Symbol
{
   public:
   static const int kTYPE = MetaKind::ALIAS;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Alias();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(Aliased, Namespace*) {return _aliased;}
   SETTER(Aliased, Namespace*) {_aliased = val;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Alias");return false;}

   virtual Symbol*
   getChild (std::string name);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   Namespace* _aliased;
};

} }


#endif
