#include "mem/st/TupleType.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

TupleType::TupleType ()
{
   _kind = TupleType::kTYPE;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
TupleType::addChild (Symbol* s)
{
   DEBUG_REQUIRE (s != NULL);
   if (st::isa<st::Type>(s))
   {
      if (_byte_size == -1) _byte_size = 0;
      _byte_size += st::cast<st::Type>(s)->ByteSize();
      _subtypes.push_back(st::cast<st::Type>(s));
   }
   return false;
}

bool
TupleType::addTypes (TypeVector tys)
{
   for (size_t i = 0; i < tys.size(); ++i)
   {
      addChild(tys[i]);
   }
   _recomputeName();
   return true;
}


bool
TupleType::hasTypes (TypeVector tys)
{
   if (_subtypes.size() == tys.size())
   {
      for (size_t i = 0; i < tys.size(); ++i)
      {
         if (_subtypes[i] != tys[i])
         {
            return false;
         }
      }
      return true;
   }
   return false;
}

void
TupleType::_recomputeName ()
{
   std::string name = "(";
   for (size_t i=0; i < _subtypes.size(); ++i)
   {
      if (i != 0) name += ",";
      name += _subtypes[i]->gQualifiedName();
   }
   name += ")";
   _name = name;
}

} }
