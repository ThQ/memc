#include "mem/ast/node/Field.hpp"


namespace mem { namespace ast { namespace node {

Field::Field ()
{
   _type = MEM_NODE_FIELD;
}

std::string
Field::get_type_name ()
{
   node::Type* type = static_cast<node::Type*>(ValueNode());
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

   // Check NAME node
   v->ensure(NameNode() != NULL);
   if (NameNode() != NULL)
   {
      v->ensure(NameNode()->isIdNode());
      v->ensure(NameNode()->hasBoundSymbol());
   }

   // Check VALUE node
   v->ensure(ValueNode() != NULL);
   if (ValueNode() != NULL)
   {
      v->ensure(ValueNode()->hasBoundSymbol());
      v->ensure(ValueNode()->hasExprType());
   }
}


} } }
