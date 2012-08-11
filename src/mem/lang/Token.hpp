#ifndef _MEM__LANG__TOKEN__HPP_
#define _MEM__LANG__TOKEN__HPP_


#include "mem/fs/position/Range.hpp"
#include "mem/lang/TokenKind.hpp"
#include "mem/ss.hpp"


namespace mem { namespace lang {

class Token
{
   protected:
   int _kind;
   std::string _value;
   fs::position::Range _location;

   GETTER(Kind, int) {return _kind;}
   SETTER(Kind, int) {_kind = val;}

   GETTER_REF(Location, fs::position::Range) {return _location;}
   SETTER(Location, fs::position::Range) {_location = val;}

   GETTER(Value, std::string) {return _value;}
   SETTER(Value, std::string) {_value = val;}
   Token () {_kind = T_YACC_ERROR; _value="";}
   Token (int kind, std::string val) {_kind = kind; _value = val;}
};


} }

#endif
