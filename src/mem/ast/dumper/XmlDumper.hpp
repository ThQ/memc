#ifndef _MEM__AST__DUMPER__XML_DUMPER__HPP_
#define _MEM__AST__DUMPER__XML_DUMPER__HPP_


#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Number.hpp"
#include "mem/ast/dumper/Dumper.hpp"


namespace mem { namespace ast { namespace dumper {


class XmlDumper : public Dumper
{
   public: virtual std::string dump (node::Node* node);
   public: virtual void dump_node (std::ostringstream& dump, node::Node* node, unsigned int level);
   public: std::string get_indent (unsigned int level);

};

} } }

#endif
