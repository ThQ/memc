#ifndef _MEM__LANG__TOKEN__HPP_
#define _MEM__LANG__TOKEN__HPP_


#include "mem/ss.hpp"


namespace mem { namespace lang {

class Token
{
   protected:
   int _kind;
   std::string _value;

   GETTER(Kind, int) {return _kind;}
   SETTER(Kind, int) {_kind = val;}

   GETTER(Value, std::string) {return _value;}
   SETTER(Value, std::string) {_value = val;}
};


} }

#endif
