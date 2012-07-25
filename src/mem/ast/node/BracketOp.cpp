#include "mem/ast/node/BracketOp.hpp"


namespace mem { namespace ast { namespace node {


BracketOp::BracketOp ()
{
   _type = Kind::BRACKET_OP;
}

void
BracketOp::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Validate the number of children (2)
}

} } }
