#ifndef _MEM__ST__FUNCTION__HPP
#define _MEM__ST__FUNCTION__HPP


#include <vector>
#include "mem/st/Type.hpp"


namespace mem { namespace st {


class Function : public Type
{
   public: std::vector<Symbol*> _params;
   public: Symbol* _return_type;

   public: Function ();
};


} }

#endif
