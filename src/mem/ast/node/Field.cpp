#include "mem/ast/node/Field.hpp"


namespace mem { namespace ast { namespace node {

Field::Field ()
{
   _type = MEM_NODE_FIELD;
}

std::string
Field::get_type_name ()
{
   node::Type* type = static_cast<node::Type*>(getChild(1));
   return type->_value;
}

void
Field::isValid (NodeValidator* v)
{
   // Check SELF
   Node::isValid(v);
   v->ensure(gChildCount() == 2, "Field must have exactly 2 children");
   v->ensure(hasBoundSymbol(), "Field must have a bound symbol");
   v->ensure(hasExprType(), "Field must have an expression type");
   v->ensure(getChild(0)->isIdNode());
   v->ensure(getChild(0)->hasBoundSymbol());
   v->ensure(getChild(1)->hasBoundSymbol());
   v->ensure(getChild(1)->hasExprType());
}


} } }
