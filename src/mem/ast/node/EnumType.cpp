#include "mem/ast/node/EnumType.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

EnumType::EnumType ()
{
   _type = EnumType::kTYPE;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
EnumType::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Validate something here
}


} } }
