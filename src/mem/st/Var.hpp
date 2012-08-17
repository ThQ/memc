#ifndef _MEM__ST__VAR__HPP
#define _MEM__ST__VAR__HPP


#include "mem/st/Constant.hpp"
#include "mem/st/Symbol.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace st {


class Var : public Symbol
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Var ();

   // Creates a Var based on its name and type.
   Var (std::string name, class Type* type);


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(ConstantValue, Constant*) {return _constant_value;}
   SETTER(ConstantValue, Constant*) {_constant_value = val;}

   // Type
   GETTER(Type, class st::Type*) {return _type;}
   SETTER(Type, class Type*) {_type = val;}
   SETTER(Type, class Symbol*) {_type = static_cast<class Type*>(val);}

   // IsConstant
   GETTER(IsConstant, bool) {return _is_constant;}
   SETTER(IsConstant, bool) {_is_constant = val;}

   // IsGlobal
   GETTER(IsGlobal, bool) {return _is_global;}
   SETTER(IsGlobal, bool) {_is_global = val;}

   virtual Symbol*
   gExprType ();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   static Var*
   create(std::string name, class Type* ty);

   virtual Symbol*
   gEvalType ();

   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   bool _is_global;
   bool _is_constant;
   st::Type* _type;
   st::Constant* _constant_value;
};

Var*
castToVar (Symbol* s);

} }


#endif
