#ifndef _MEM__ST__VAR__HPP
#define _MEM__ST__VAR__HPP


#include "mem/st/Instance.hpp"
#include "mem/st/Symbol.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace st {


class Var : public Symbol
{
   public: Type* _type;

   public: Var ();
   public: Var (std::string name, Type* type);
   //public: virtual void print ();

   public: void set_type (Symbol* type);
};


} }

#endif
