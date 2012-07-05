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

bool
Field::isValid ()
{
   if (!Node::isValid()) return false;
   if (gChildCount() != 2) return false;
   if (!hasBoundSymbol()) return false;
   if (!hasExprType()) return false;
   if (!getChild(0)->isIdNode()) return false;
   if (!getChild(0)->hasBoundSymbol()) return false;
   if (!getChild(1)->hasBoundSymbol()) return false;
   if (!getChild(1)->hasExprType()) return false;

   return true;
}


} } }
