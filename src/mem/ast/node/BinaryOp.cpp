#include "mem/ast/node/BinaryOp.hpp"


namespace mem { namespace ast { namespace node {


BinaryOp::BinaryOp ()
{
   _type = Kind::UNKNOWN;
}

void
BinaryOp::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Validate the number of children (2) of their types
}

} } }
