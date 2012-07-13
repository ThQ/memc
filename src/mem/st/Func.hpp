#ifndef _MEM__ST__FUNC__HPP
#define _MEM__ST__FUNC__HPP


#include <vector>
#include "mem/st/Type.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace st {


/**
 * A symbol to represent functions.
 *
 * Several properties :
 * - Functions have parameters, each having the type Var
 * - Functions have a return type
 * - Functions can have children, first each parameter is added as a child,
 *   then each variable at the top of the function body is also listed.
 */
class Func: public Type
{
   public: std::vector<Var*> _params;
   protected: Func* _overloaded_func;


   // -------------------------------------------------------------------------
   // PROPERTIES
   // -------------------------------------------------------------------------

   // PROPERTY : IsEntryPoint
   public: bool _is_entry_point;
   public: inline bool gIsEntryPoint() const {return _is_entry_point;}
   public: inline void sIsEntryPoint(bool is) {_is_entry_point = is;}

   // PROPERTY : ParamCount
   public: inline size_t gParamCount() const {return this->_params.size();}

   // PROPERTY : ReturnType
   public: Symbol* _return_type;
   public: inline Symbol* gReturnType () const { return this->_return_type;}
   public: inline void sReturnType (Symbol* ret_type) {this->_return_type = ret_type;}

   public: inline Func* gOverloadedFunc() { return this->_overloaded_func;}
   public: inline void sOverloadedFunc(Func* overloaded_func) {
      assert(overloaded_func->is(st::FUNCTION));
      this->_overloaded_func = overloaded_func;
      }

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
    * Adds a function parameter given its name and type.
    */
   st::Var*
   addParam (std::string name, st::Type* ty);

   /**
    * Returns the Nth parameter.
    */
   st::Var*
   getParam (int i);
};


} }

#endif
