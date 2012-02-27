#ifndef _MEM__ST__FUNCTION_SIGNATURE__HPP_
#define _MEM__ST__FUNCTION_SIGNATURE__HPP_


#include "mem/st/Type.hpp"


namespace mem { namespace st {


class FunctionSignature : public Type
{
   public:
      FunctionSignature* _overridden_func;
      std::vector<Symbol*> _params;

   public:
      FunctionSignature ();
      bool canOverride (FunctionSignature* func_sign);
      inline FunctionSignature* gOverriddenFunc() {return this->_overridden_func;}
      inline void sOverriddenFunc(FunctionSignature* func) {assert(func!=this);this->_overridden_func = func;}

      std::string gSignature();

};

} }


#endif
