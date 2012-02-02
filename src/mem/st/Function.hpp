#ifndef _MEM__ST__FUNCTION__HPP
#define _MEM__ST__FUNCTION__HPP


#include "mem/st/Symbol.hpp"


namespace mem { namespace st {


class Function : public Symbol
{
   public: Symbol* _return_type;
   public: Function ();
   public: virtual void print ();
};


} }

#endif
