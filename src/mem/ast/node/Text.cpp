#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Text::Text ()
{
   _type = Text::kTYPE;
   _value.assign("");
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
Text::copy () const
{
   Text* n = new Text();
   n->setValue(n->Value());
   return n;
}

} } }
