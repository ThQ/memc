#include "mem/st/Symbol.hpp"

namespace mem { namespace st {


Symbol::Symbol ()
{
   _child_count = 0;
   _depth = 0;
   _kind = UNKNOWN;
   _md = NULL;
   _parent = NULL;
   _size = 0;
}

Symbol::~Symbol ()
{
   std::map<std::string, Symbol*>::iterator i = _children.begin();
   for(; i != _children.end(); ++i)
   {
      delete i->second;
   }
   delete _md;
}

Symbol*
Symbol::gExprType ()
{
   printf("gExprType(FROM:%d)\n", _kind);
   return NULL;
}

bool
Symbol::addChild (Symbol* sym)
{
   if (sym->Name() == "")
   {
      std::ostringstream id;
      id << Name();
      id << "#";
      id << ChildCount() + 1;

      sym->setName(id.str());
   }

   if (!getChild(sym->Name()))
   {
      sym->_parent = this;
      _children[sym->Name()] = sym;
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
      if (sym->Name().size() != 0)
      {
         if (name.size() != 0)
         {
            name.insert(0, ".");
         }
         name.insert(0, sym->Name());
      }
      sym = sym->_parent;
   }

   return name;
}

void
Symbol::hintName (Symbol* parent, std::string hint)
{
   std::ostringstream id;
   id << hint << "#" << parent->ChildCount() + 1;
   setName(id.str());
}

bool
Symbol::isAnyTypeSymbol() const
{
   switch (_kind)
   {
      case st::CLASS:
      case st::PRIMITIVE:
      case st::POINTER:
         return true;
      default:
         return false;
   }
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

/*
void
Symbol::sName (char* name, size_t name_len)
{
   _name.assign(name, name_len);
}
*/


} }
