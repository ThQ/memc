#ifndef _MEM__MEM__ST__CORE_TYPES__HPP_
#define _MEM__MEM__ST__CORE_TYPES__HPP_

#include "mem/st/IntType.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace st {

class CoreTypes
{
   public:
   Type* _bug_type;
   IntType* _bool;
   IntType* _char;
   IntType* _long;
   IntType* _int;
   IntType* _int64;
   IntType* _int32;
   IntType* _int16;
   IntType* _int8;
   IntType* _short;
   IntType* _uchar;
   IntType* _ushort;
   IntType* _uint;
   IntType* _uint64;
   IntType* _uint32;
   IntType* _uint16;
   IntType* _uint8;
   IntType* _ulong;
   Type* _void;

   // -------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   // -------------------------------------------------------------------------
   public:

   // PROPERTY : BoolTy
   inline Type* gBoolTy() {return this->_bool;}

   // PROPERTY : CharTy
   inline Type* gCharTy() {return this->_char;}

   // PROPERTY : IntTy
   inline Type* gIntTy() {return this->_int;}

   // PROPERTY : ShortTy
   inline Type* gShortTy() {return this->_short;}

   // PROPERTY : VoidTy
   inline Type* gVoidTy() {return this->_void;}
};

} }

#endif
