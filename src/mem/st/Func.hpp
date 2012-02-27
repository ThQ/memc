#ifndef _MEM__ST__FUNC__HPP
#define _MEM__ST__FUNC__HPP


#include <vector>
#include "mem/st/FunctionSignature.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace st {


class Func: public Type
{
   public: std::vector<Symbol*> _params;
   public: Symbol* _return_type;

   public: Func();
   public: inline Symbol* gReturnType () { return this->_return_type;}
   public: inline void sReturnType (Symbol* ret_type) {this->_return_type = ret_type;}
};


} }

#endif
