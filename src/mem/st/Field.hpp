#ifndef _MEM__ST__FIELD__HPP_
#define _MEM__ST__FIELD__HPP_


#include "mem/st/Var.hpp"


namespace mem { namespace st {


class Field : public Var
{
   public: int _field_index;

   public:

   Field();
};

} }


#endif