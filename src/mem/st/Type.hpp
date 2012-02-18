#ifndef _MEM__ST__TYPE__HPP_
#define _MEM__ST__TYPE__HPP_


#include "mem/st/Symbol.hpp"


namespace mem { namespace st {


class Type: public Symbol
{
   public: Type* _parent_type;

   public: Type();
   public: bool is_subclass (Type* parent);
};


} }

#endif
