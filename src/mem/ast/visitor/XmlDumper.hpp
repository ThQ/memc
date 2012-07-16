#ifndef _MEM__AST__DUMPER__XML_DUMPER__HPP_
#define _MEM__AST__DUMPER__XML_DUMPER__HPP_


#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Number.hpp"
#include "mem/ast/visitor/Dumper.hpp"


namespace mem { namespace ast { namespace visitor {


class XmlDumper : public Dumper
{
   public:

   virtual bool
   setup ();

   virtual bool
   tearDown ();

   virtual bool
   visit (node::Node* node);
};


} } }


#endif
