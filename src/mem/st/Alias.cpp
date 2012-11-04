#include "mem/st/Alias.hpp"


namespace mem { namespace st {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Alias::Alias ()
{
   _kind = Alias::kTYPE;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Symbol*
Alias::getChild (std::string name)
{
   DEBUG_REQUIRE (_aliased != NULL);

   return _aliased->getChild(name);
}


} }
