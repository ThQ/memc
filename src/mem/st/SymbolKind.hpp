#ifndef _MEM__ST__SYMBOL_KIND__HPP_
#define _MEM__ST__SYMBOL_KIND__HPP_


namespace mem { namespace st {


typedef enum {
   UNKNOWN=0,
   CLASS=1,
   FIELD=2,
   NAMESPACE=3,
   OBJECT=4,
   PRIMITIVE_TYPE=5,
   FUNCTION=6,
   VAR=7,
   INSTANCE=8,
   FUNCTION_SIGNATURE=9,
   POINTER=10,
   ARG=11,
   ARRAY=12,
   ALIAS=13,
   INT_TYPE=14,
   MACRO=15,
   TUPLE_TYPE=16,
   FUNCTION_TYPE=17,
   ENUM_TYPE=18,
   INT_CONSTANT=19
} SymbolKind;


} }

#endif
