#ifndef _MEM__ST__FUNC__HPP
#define _MEM__ST__FUNC__HPP


#include <vector>
#include "mem/st/Arg.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace st {


/**
 * A symbol to represent functions.
 *
 * Several properties :
 * - Functions have parameters, each having the type Arg
 * - Functions have a return type
 * - Functions can have children, first each parameter is added as a child,
 *   then each variable at the top of the function body is also listed.
 */
class Func: public Type
{
   // -------------------------------------------------------------------------
   // FIELDS
   // -------------------------------------------------------------------------
   public:

   bool _is_entry_point;
   std::vector<Arg*> _params;
   //Func* _overloaded_func;
   Type* _return_type;


   // -------------------------------------------------------------------------
   // PROPERTIES
   // -------------------------------------------------------------------------
   public:

   // IsEntryPoint
   GETTER(IsEntryPoint, bool) {return _is_entry_point;}
   SETTER(IsEntryPoint, bool) {_is_entry_point = val;}

   // ParamCount
   GETTER(ParamCount, size_t) {return _params.size();}

   // ReturnType
   GETTER(ReturnType, Type*) {return _return_type;}
   SETTER(ReturnType, Type*) {_return_type = val;}


   // -------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   // -------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Func();

   /**
    * Default destructor.
    */
   ~Func();


   // -------------------------------------------------------------------------
   // PUBLIC METHODS
   // -------------------------------------------------------------------------
   public:

   /**
    * Add a function parameter given its name and type.
    */
   st::Arg*
   addParam (std::string name, st::Type* ty);

   /**
    * Return the Nth parameter.
    */
   st::Var*
   getParam (int i);
};


} }

#endif
