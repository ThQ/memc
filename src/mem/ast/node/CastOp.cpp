#include "mem/ast/node/CastOp.hpp"


namespace mem { namespace ast { namespace node {


CastOp::CastOp ()
{
   _type = Kind::OP_CAST;
}

void
CastOp::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Validate the number of children (2)
}

} } }
