#ifndef _MEM__ST__FIELD__HPP_
#define _MEM__ST__FIELD__HPP_


#include "mem/st/Var.hpp"


namespace mem { namespace st {


class Field : public Var
{
   public: int _field_index;

   public:

   Field();

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Ptr");return false;}
};

} }


#endif
