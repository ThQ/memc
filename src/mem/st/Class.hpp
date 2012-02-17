#ifndef _MEM__ST__CLASS__HPP
#define _MEM__ST__CLASS__HPP


#include "mem/st/Instance.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace st {


class Class : public Type
{
   public: Instance* _instance_type;

   public: Class ();
   public: virtual ~Class();
   public: Instance* g_instance_type();
   //public: virtual void print ();
};


} }

#endif
