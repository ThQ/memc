#ifndef _MEM__ST__SYMBOL_KIND__HPP_
#define _MEM__ST__SYMBOL_KIND__HPP_

namespace mem { namespace st
{
   typedef enum {
      UNKNOWN=0,
      CLASS=1,
      FIELD=2,
      NAMESPACE=3,
      OBJECT=4,
      PRIMITIVE=5,
      FUNCTION=6,
      VAR=7,
      INSTANCE=8,
      FUNCTION_SIGNATURE=9
   } SymbolKind;
}
}

#endif
