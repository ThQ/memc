#ifndef _MEM__LANG__TOKEN__HPP_
#define _MEM__LANG__TOKEN__HPP_


#include "mem/lang/TokenKind.hpp"
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
   Token () {_kind = T_YACC_ERROR; _value="";}
   Token (int kind, std::string val) {_kind = kind; _value = val;}
};


} }

#endif
