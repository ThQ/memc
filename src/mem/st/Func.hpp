#ifndef _MEM__ST__FUNC__HPP
#define _MEM__ST__FUNC__HPP


#include <vector>
#include "mem/st/Arg.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace st {


// A symbol to represent functions.
//
// Several properties :
// - Functions have parameters, each having the type Arg
// - Functions have a return type
// - Functions can have children, first each parameter is added as a child,
//   then each variable at the top of the function body is also listed.
//
// Functions are nodes of a linked list which lists all functions. This is
// useful when code generating.
class Func: public Type
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Func();

   // Default destructor.
   ~Func();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // HasBody
   GETTER(HasBody, bool) {return _has_body;}
   SETTER(HasBody, bool) {_has_body = val;}

   // IsEntryPoint
   GETTER(IsEntryPoint, bool) {return _is_entry_point;}
   SETTER(IsEntryPoint, bool) {_is_entry_point = val;}

   GETTER(IsExternal, bool) {return _is_external;}
   SETTER(IsExternal, bool) {_is_external = val;}

   // NextFunction
   GETTER(NextFunction, Func*) {return _next_function;}
   SETTER(NextFunction, Func*) {_next_function = val;}

   // ParamCount
   GETTER(ParamCount, size_t) {return _params.size();}

   // ReturnType
   GETTER(ReturnType, Type*) {return _return_type;}
   SETTER(ReturnType, Type*) {_return_type = val;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   // Add a function parameter given its name and type.
   st::Arg*
   addParam (std::string name, st::Type* ty);

   // Return the Nth parameter.
   st::Var*
   getParam (int i);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   bool _has_body;
   bool _is_entry_point;
   bool _is_external;
   std::vector<Arg*> _params;
   Type* _return_type;
   Func* _next_function;
};


} }

#endif
