#include "mem/st/Symbol.hpp"

namespace mem { namespace st {


Symbol::Symbol ()
{
   _depth = 0;
   _kind = UNKNOWN;
   _parent = NULL;
   _child_count = 0;
   _size = 0;
}

Symbol::~Symbol ()
{
   std::map<std::string, Symbol*>::iterator i = _children.begin();
   for(; i != _children.end(); ++i)
   {
      delete i->second;
   }
}

bool
Symbol::addChild (Symbol* sym)
{
   if (sym->gName() == "")
   {
      std::ostringstream id;
      id << gName();
      id << "#";
      id << gChildCount() + 1;

      sym->sName(id.str());
   }

   if (!getChild(sym->_name))
   {
      sym->_parent = this;
      _children[sym->_name] = sym;
      sym->_depth = _depth + 1;
      return true;
   }
   return false;
}

Symbol*
Symbol::getChild (std::string name)
{
   if (name.size() != 0 && _children.find(name) != _children.end())
   {
      return _children[name];
   }
   return NULL;
}

/*
Symbol*
Symbol::gEvalType ()
{
   return this;
}
*/

std::string
Symbol::gQualifiedName ()
{
   std::string name = "";
   Symbol* sym = this;
   while (sym != NULL)
   {
      if (sym->gName().size() != 0)
      {
         if (name.size() != 0)
         {
            name.insert(0, ".");
         }
         name.insert(0, sym->gName());
      }
      sym = sym->_parent;
   }

   return name;
}

bool
Symbol::isTypeSymbol () const
{
   switch (this->_kind)
   {
      case CLASS:
      case POINTER:
      case PRIMITIVE:
         return true;
      default:
         return false;
   }
}

void
Symbol::sName (char* name, size_t name_len)
{
   _name.assign(name, name_len);
}

void
Symbol::sName (std::string name)
{
   _name = name;
}


} }
