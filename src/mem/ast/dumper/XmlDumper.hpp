#ifndef _MEM__AST__DUMPER__XML_DUMPER__HPP_
#define _MEM__AST__DUMPER__XML_DUMPER__HPP_


#include "mem/ast/dumper/Dumper.hpp"


namespace mem { namespace ast { namespace dumper {


class XmlDumper : public Dumper
{
   public: virtual std::string dump (node::Node* node);
   public: virtual std::string dump_node (node::Node* node, unsigned int level);
   public: std::string get_indent (unsigned int level);

};

} } }

#endif
