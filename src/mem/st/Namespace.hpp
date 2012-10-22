#ifndef _MEM__ST__NAMESPACE__HPP_
#define _MEM__ST__NAMESPACE__HPP_


#include "mem/st/Type.hpp"


namespace mem { namespace st {


class Namespace : public Symbol
{
   public:
   static const int kTYPE = MetaKind::NAMESPACE;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   Namespace ();
};


} }

#endif
