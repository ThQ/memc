#ifndef _MEM__ST__VAR__HPP
#define _MEM__ST__VAR__HPP


#include "mem/st/Symbol.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace st {


class Var : public Symbol
{
   // -------------------------------------------------------------------------
   // PROPERTIES
   // -------------------------------------------------------------------------
   public:

   // PROPERTY : Type
   Type* _type;

   inline Type* gType() {return _type;}
   inline void sType (Symbol* type) {this->_type = static_cast<Type*>(type);}

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
   Var (std::string name, Type* type);


   // -------------------------------------------------------------------------
   // PUBLIC METHODS
   // -------------------------------------------------------------------------
   public:

   static Var*
   create(std::string name, Type* ty);

   virtual Symbol*
   gEvalType ();
};


} }


#endif
