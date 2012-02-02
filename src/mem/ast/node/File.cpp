#include "mem/ast/node/File.hpp"

namespace mem { namespace ast { namespace node {


File::File ()
{
   this->_type = MEM_NODE_FILE;
}

void
File::dump_self ()
{
   this->dump_depth();
   printf("<File(relative_path=%s, include_path=%s, id=%s)>\n",
          this->_path.c_str(),
          this->_include_path.c_str(),
          this->_id.c_str());
}


} } }
