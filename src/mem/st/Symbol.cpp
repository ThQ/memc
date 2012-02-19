#include "mem/st/Symbol.hpp"

namespace mem { namespace st {


Symbol::Symbol ()
{
   this->_depth = 0;
   this->_kind = UNKNOWN;
   this->_next = NULL;
   this->_parent = NULL;
   this->_child_count = 0;
}

Symbol::~Symbol ()
{
   std::map<std::string, Symbol*>::iterator i = this->_children.begin();
   for(; i != this->_children.end(); ++i )
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
      id << this->gName();
      id << "#";
      id << this->_children.size() + 1;

      sym->sName(id.str());
   }

   if (!this->getChild(sym->_name))
   {
      sym->_parent = this;
      this->_children[sym->_name] = sym;
      sym->_depth = this->_depth + 1;
      return true;
   }
   return false;
}

Symbol*
Symbol::getChild (std::string name)
{
   if (name.size() != 0 && this->_children.find(name) != this->_children.end())
   {
      return this->_children[name];
   }
   return NULL;
}

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
   if (name.size() != 0)
   {
      return name;
   }
   return "?";
}

bool
Symbol::is (SymbolKind kind)
{
   return this->_kind == kind;
}

void
Symbol::sName (char* name, size_t name_len)
{
   this->_name.assign(name, name_len);
}

void
Symbol::sName (std::string name)
{
   this->_name = name;
}


} }
