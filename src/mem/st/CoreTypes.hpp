#ifndef _MEM__MEM__ST__CORE_TYPES__HPP_
#define _MEM__MEM__ST__CORE_TYPES__HPP_

#include "mem/st/IntType.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace st {

class CoreTypes
{
   public:
   IntType* _long;
   Type* _bug_type;
   IntType* _i64;
   IntType* _i32;
   IntType* _i16;
   IntType* _i8;
   // -------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   // -------------------------------------------------------------------------
   public:

   // PROPERTY : BoolTy
   Type* _bool;
   inline Type* gBoolTy() {return this->_bool;}

   // PROPERTY : CharTy
   Type* _char;
   inline Type* gCharTy() {return this->_char;}

   // PROPERTY : IntTy
   Type* _int;
   inline Type* gIntTy() {return this->_int;}

   // PROPERTY : ShortTy
   Type* _short;
   inline Type* gShortTy() {return this->_short;}

   // PROPERTY : VoidTy
   Type* _void;
   inline Type* gVoidTy() {return this->_void;}
};

} }

#endif
