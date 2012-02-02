#include "mem/ast/node/Root.hpp"

namespace mem { namespace ast { namespace node {


Root::Root ()
{
   this->_type = MEM_NODE_ROOT;
}

void
Root::dump_self ()
{
   this->dump_depth();
   printf("<Root>\n");
}


} } }
