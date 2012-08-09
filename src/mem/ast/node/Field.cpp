#include "mem/ast/node/Field.hpp"


namespace mem { namespace ast { namespace node {

Field::Field ()
{
   _type = Kind::FIELD;
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
   v->ensure(ChildCount() == 2, "Field must have exactly 2 children");
   v->ensure(hasBoundSymbol(), "Field must have a bound symbol");
   v->ensure(hasExprType(), "Field must have an expression type");

   // Check NAME node
   v->ensure(NameNode() != NULL, "Field : Must have a name node");
   if (NameNode() != NULL)
   {
      v->ensure(NameNode()->isIdNode(), "Field : Name node must be an ID");
      v->ensure(NameNode()->hasBoundSymbol(), "Field : Name node must have a bound symbol");
   }

   v->ensure(TypeNode()->hasBoundSymbol(), "Field : Type node must have a bound symbol");

   // Check VALUE node
   if (ValueNode() != NULL)
   {
      v->ensure(ValueNode()->hasExprType(), "Field : Value node must have an expression type");
   }
}


} } }
