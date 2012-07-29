#include "mem/ast/node/For.hpp"


namespace mem { namespace ast { namespace node {


For::For ()
{
   _type = Kind::FOR;
}

void
For::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Must do some checks here
}

} } }
