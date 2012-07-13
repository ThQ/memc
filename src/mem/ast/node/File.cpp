#include "mem/ast/node/File.hpp"


namespace mem { namespace ast { namespace node {


File::File ()
{
   _type = MEM_NODE_FILE;
}

void
File::isValid (NodeValidator* v)
{
   Node::isValid(v);

   Node* child = NULL;
   for (size_t i = 0 ; i < gChildCount(); ++i)
   {
      child = getChild(i);

      v->ensure(child->isUseNode() || child->isClassNode() || child->isFuncNode(),
         "Children of a File node must be either Use, Class or Func");
   }
}


} } }
