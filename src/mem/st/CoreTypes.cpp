#include "mem/st/CoreTypes.hpp"

namespace mem { namespace st {


CoreTypes::CoreTypes ()
{
   _void_ty = new st::VoidType();

   // Integer types
   _bool_ty = new st::IntType("bool", sizeof(bool));

   _short_ty = new st::IntType("short", sizeof(short));
   _char_ty = new st::IntType("char", sizeof(char));
   _int_ty = new st::IntType("int", sizeof(int));
   _long_ty = new st::IntType("long", sizeof(long));

   _ushort_ty = new st::IntType("ushort", sizeof(unsigned short));
   _uchar_ty = new st::IntType("uchar", sizeof(unsigned short));
   _uint_ty = new st::IntType("uint", sizeof(unsigned short));
   _ulong_ty = new st::IntType("ulong", sizeof(unsigned short));

   _int8_ty = new st::IntType("int8", 1);
   _int16_ty = new st::IntType("int16", 2);
   _int32_ty = new st::IntType("int32", 4);
   _int64_ty = new st::IntType("int64", 8);

   _uint8_ty = new st::IntType("uint8", 1);
   _uint16_ty = new st::IntType("uint16", 2);
   _uint32_ty = new st::IntType("uint32", 4);
   _uint64_ty = new st::IntType("uint64", 8);

   _bug_type = new st::PrimitiveType();
   _bug_type->setName("$BadType");

   _null = new st::Null();
   _null->setType(_void_ty);
}

} }
