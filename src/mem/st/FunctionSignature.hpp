#ifndef _MEM__ST__FUNCTION_SIGNATURE__HPP_
#define _MEM__ST__FUNCTION_SIGNATURE__HPP_


#include "mem/st/Type.hpp"


namespace mem { namespace st {


class FunctionSignature : public Type
{
   public: std::vector<Symbol*> _params;

   public: FunctionSignature ();

   public: std::string gSignature();

};

} }


#endif
