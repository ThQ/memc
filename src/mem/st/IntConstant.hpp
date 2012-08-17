#ifndef _MEM__ST__INT_CONSTANT__HPP_
#define _MEM__ST__INT_CONSTANT__HPP_


#include "cxx.hpp"
#include "mem/st/Constant.hpp"


namespace mem { namespace st {


class IntConstant : public Constant
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   GETTER(IsSigned, bool) {return _is_signed;}

   // Default constructor.
   IntConstant ();

   i64
   getSignedValue() {return _signed_value;}

   void
   setChar (char i) {_byte_size = sizeof(char); _is_signed=true;_signed_value = i;}

   void
   setShort (int i) {_byte_size = sizeof(short); _is_signed=true;_signed_value = i;}

   void
   setInt (int i) {_byte_size = sizeof(int); _is_signed=true;_signed_value = i;}

   protected:
   bool _is_signed;
   i64 _unsigned_value;
   ui64 _signed_value;
   st::Type* _type;
};

IntConstant*
castToIntConstant (Symbol* s);

} }


#endif
