#ifndef _LANG__MEM__TOKEN__HPP_
#define _LANG__MEM__TOKEN__HPP_


#include "langmem/TokenKind.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/ss.hpp"


namespace langmem {


class Token
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   Token () {_kind = T_YACC_ERROR; _value="";}

   Token (int kind, std::string val) {_kind = kind; _value = val;}


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:


   GETTER(Kind, int) {return _kind;}
   SETTER(Kind, int) {_kind = val;}

   GETTER_REF(Location, mem::fs::position::Range) {return _location;}
   SETTER(Location, mem::fs::position::Range) {_location = val;}

   GETTER(Value, std::string) {return _value;}
   SETTER(Value, std::string) {_value = val;}


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:
   int _kind;
   std::string _value;
   mem::fs::position::Range _location;
};


}

#endif
