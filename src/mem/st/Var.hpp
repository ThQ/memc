#ifndef _MEM__ST__VAR__HPP
#define _MEM__ST__VAR__HPP


#include "mem/st/Symbol.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace st {


class Var : public Symbol
{
   Type* _type;

   // -------------------------------------------------------------------------
   // PROPERTIES
   // -------------------------------------------------------------------------
   public:

   // PROPERTY : Type
   GETTER(Type, class Type*) {return _type;}
   SETTER(Type, class Type*) {_type = val;}
   SETTER(Type, class Symbol*) {_type = static_cast<class Type*>(val);}

   virtual Symbol*
   gExprType ();

   // -------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   // -------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Var ();

   /**
    * Creates a Var based on its name and type.
    */
   Var (std::string name, class Type* type);


   // -------------------------------------------------------------------------
   // PUBLIC METHODS
   // -------------------------------------------------------------------------
   public:

   static Var*
   create(std::string name, class Type* ty);

   virtual Symbol*
   gEvalType ();
};


} }


#endif
