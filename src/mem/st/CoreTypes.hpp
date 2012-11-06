#ifndef _MEM__MEM__ST__CORE_TYPES__HPP_
#define _MEM__MEM__ST__CORE_TYPES__HPP_

#include "mem/st/IntType.hpp"
#include "mem/st/Null.hpp"
#include "mem/st/Type.hpp"
#include "mem/st/VoidType.hpp"


namespace mem { namespace st {

class CoreTypes
{
   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   CoreTypes ();


   //==========================================================================
   // PUBLIC PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(BoolTy, class IntType*) { return _bool_ty; }

   GETTER(BugTy, class Type*) { return _bug_type; }

   GETTER(CharTy, class IntType*) { return _char_ty; }

   GETTER(ShortTy, class IntType*) { return _short_ty; }

   GETTER(IntTy, class IntType*) { return _int_ty; }

   GETTER(LongTy, class IntType*) { return _long_ty; }

   GETTER(Int8Ty, class IntType*) { return _int8_ty; }

   GETTER(Int16Ty, class IntType*) { return _int16_ty; }

   GETTER(Int32Ty, class IntType*) { return _int32_ty; }

   GETTER(Int64Ty, class IntType*) { return _int64_ty; }

   GETTER(UCharTy, class IntType*) { return _uchar_ty; }

   GETTER(UShortTy, class IntType*) { return _ushort_ty; }

   GETTER(UIntTy, class IntType*) { return _uint_ty; }

   GETTER(UInt8Ty, class IntType*) { return _uint8_ty; }

   GETTER(UInt16Ty, class IntType*) { return _uint16_ty; }

   GETTER(UInt32Ty, class IntType*) { return _uint32_ty; }

   GETTER(UInt64Ty, class IntType*) { return _uint64_ty; }

   GETTER(ULongTy, class IntType*) { return _ulong_ty; }

   GETTER(VoidTy, VoidType*) { return _void_ty; }

   GETTER(NullVal, Null*) {return _null;}


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

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
};

} }

#endif
