#ifndef _MEM__ST__INT_CONSTANT__HPP_
#define _MEM__ST__INT_CONSTANT__HPP_


#include <inttypes.h>
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

   int64_t
   getSignedValue() {return _signed_value;}

   void
   setChar (char i) {_byte_size = sizeof(char); _is_signed=true;_signed_value = i;}

   void
   setShort (int i) {_byte_size = sizeof(short); _is_signed=true;_signed_value = i;}

   void
   setInt (int i) {_byte_size = sizeof(int); _is_signed=true;_signed_value = i;}

   protected:
   bool _is_signed;
   int64_t _unsigned_value;
   uint64_t _signed_value;
   st::Type* _type;
};

} }


#endif
