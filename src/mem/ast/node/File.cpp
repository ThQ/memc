#include "mem/ast/node/File.hpp"


namespace mem { namespace ast { namespace node {


File::File ()
{
   _type = Kind::FILE;
}

void
File::isValid (NodeValidator* v)
{
   Node::isValid(v);

   Node* child = NULL;
   for (size_t i = 0 ; i < ChildCount(); ++i)
   {
      child = getChild(i);

      v->ensure(child->isUseNode() || child->isClassNode() || child->isFuncNode(),
         "Children of a File node must be either Use, Class or Func");
   }
}


} } }
