#ifndef _MEM__ST__DUMPER__XML_DUMPER__HPP_
#define _MEM__ST__DUMPER__XML_DUMPER__HPP_


#include "mem/st/visitor/IDumper.hpp"


namespace mem { namespace st { namespace visitor {


/**
 * A class for dumping a symbol tree as XML.
 */
class XmlDumper : public IDumper
{

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   setup ();

   virtual bool
   visit (st::Symbol* sym);

   virtual void
   visitChildren (st::Symbol* sym);

   virtual bool
   visitClass (st::Class* cls_sym);

   virtual bool
   visitFunction (st::Func* func_sym);

   virtual bool
   visitNamespace (st::Namespace* var_sym);

   virtual bool
   visitVar (st::Var* var_sym);

   virtual bool
   visitUnknown (st::Symbol* sym);
};


} } }


#endif
