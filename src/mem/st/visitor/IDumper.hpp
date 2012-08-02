#ifndef _MEM__ST__IDUMPER__HPP_
#define _MEM__ST__IDUMPER__HPP_


#include <iostream>
#include <string>

#include "mem/st/ArrayType.hpp"
#include "mem/st/Class.hpp"
#include "mem/st/Field.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/Namespace.hpp"
#include "mem/st/PointerType.hpp"
#include "mem/st/PrimitiveType.hpp"
#include "mem/st/Symbol.hpp"
#include "mem/st/Var.hpp"
#include "mem/st/visitor/Visitor.hpp"

namespace mem { namespace st { namespace visitor {


class IDumper : public Visitor
{
   public: std::ostream* _out;
};


} } }

#endif
