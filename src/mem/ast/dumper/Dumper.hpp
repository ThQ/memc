#ifndef _MEM__AST__DUMPER__DUMPER__HPP_
#define _MEM__AST__DUMPER__DUMPER__HPP_


#include <iostream>
#include <string>

#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace dumper {


class Dumper
{
   public: virtual std::string dump (node::Node* node);
   public: virtual void dump_to (node::Node* root, std::ostream& out);
};


} } }


#endif
