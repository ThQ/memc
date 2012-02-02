#ifndef _MEM__ST__NAMESPACE__HPP_
#define _MEM__ST__NAMESPACE__HPP_

#include "check.h"
#include "mem/st/Type.hpp"

namespace mem { namespace st {


class Namespace : public Symbol
{
   public: Namespace ();
   public: Type* get_type (Type*& dest, std::string type_name);
   public: Namespace* get_namespace (Namespace*& dest, char* name, size_t name_len);
   public: bool has_symbol (std::string name);
   public: virtual void print ();
   public: Type* push (Type* type);
   public: Namespace* push (Namespace* ns);
};


} }

#endif
