#ifndef _MEM__MEM__ST__CORE_TYPES__HPP_
#define _MEM__MEM__ST__CORE_TYPES__HPP_

#include "mem/st/IntType.hpp"
#include "mem/st/Null.hpp"
#include "mem/st/Type.hpp"
#include "mem/st/VoidType.hpp"


namespace mem { namespace st {

class CoreTypes
{
   public:
   Type* _bug_type;
   IntType* _bool_ty;
   IntType* _char_ty;
   IntType* _long_ty;
   IntType* _int_ty;
   IntType* _int64_ty;
   IntType* _int32_ty;
   IntType* _int16_ty;
   IntType* _int8_ty;
   IntType* _short_ty;
   IntType* _uchar_ty;
   IntType* _ushort_ty;
   IntType* _uint_ty;
   IntType* _uint64_ty;
   IntType* _uint32_ty;
   IntType* _uint16_ty;
   IntType* _uint8_ty;
   IntType* _ulong_ty;
   VoidType* _void_ty;
   Null* _null;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   CoreTypes ();


   //--------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(BoolType, class IntType*) { return _bool_ty; }

   GETTER(CharType, class IntType*) { return _char_ty; }

   GETTER(ShortType, class IntType*) { return _short_ty; }

   GETTER(IntType, class IntType*) { return _int_ty; }

   GETTER(LongType, class IntType*) { return _long_ty; }

   GETTER(Int8Type, class IntType*) { return _int8_ty; }

   GETTER(Int16Type, class IntType*) { return _int16_ty; }

   GETTER(Int32Type, class IntType*) { return _int32_ty; }

   GETTER(Int64Type, class IntType*) { return _int64_ty; }

   GETTER(UCharType, class IntType*) { return _uchar_ty; }

   GETTER(UShortType, class IntType*) { return _ushort_ty; }

   GETTER(UIntType, class IntType*) { return _uint_ty; }

   GETTER(UInt8Type, class IntType*) { return _uint8_ty; }

   GETTER(UInt16Type, class IntType*) { return _uint16_ty; }

   GETTER(UInt32Type, class IntType*) { return _uint32_ty; }

   GETTER(UInt64Type, class IntType*) { return _uint64_ty; }

   GETTER(ULongType, class IntType*) { return _ulong_ty; }

   GETTER(VoidType, VoidType*) { return _void_ty; }
};

} }

#endif
