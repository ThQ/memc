#include "mem/ast/dumper/Dumper.hpp"


namespace mem { namespace ast { namespace dumper {


std::string
Dumper::dump (node::Node* root)
{
   std::string res = "";
   return res;
}

void
Dumper::dump_to (node::Node* root, std::ostream& out)
{
   out << this->dump(root);
}

} } }
