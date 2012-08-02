#include "mem/st/Alias.hpp"


namespace mem { namespace st {


Alias::Alias ()
{
   _kind = ALIAS;
}

Symbol*
Alias::getChild (std::string name)
{
   DEBUG_REQUIRE (_aliased != NULL);

   return _aliased->getChild(name);
}

} }
