#ifndef _MEM__ST__IDUMPER__HPP_
#define _MEM__ST__IDUMPER__HPP_


#include <iostream>
#include <string>

#include "mem/st/Class.hpp"
#include "mem/st/Function.hpp"
#include "mem/st/FunctionSignature.hpp"
#include "mem/st/Symbol.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace st { namespace dumper {


class IDumper
{
   public: virtual std::string dump (Symbol* symb){return "";}
   public: virtual void dump_to (Symbol* symb, std::ostream& out){}
};


} } }

#endif
