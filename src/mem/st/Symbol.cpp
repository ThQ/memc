#include "mem/st/Symbol.hpp"

namespace mem { namespace st {


Symbol::Symbol ()
{
   this->_depth = 0;
   this->_kind = UNKNOWN;
   this->_next = NULL;
   this->_parent = NULL;
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
Symbol::add_child (Symbol* sym)
{
   if (!this->get_child(sym->_name))
   {
      sym->_parent = this;
      this->_children[sym->_name] = sym;
      sym->_depth = this->_depth + 1;
      return true;
   }
   return false;
}

Symbol*
Symbol::get_child (std::string name)
{
   if (name.size() != 0 && this->_children.find(name) != this->_children.end())
   {
      return this->_children[name];
   }
   return NULL;
}

std::string
Symbol::get_qualified_name ()
{
   std::string name = "";
   Symbol* sym = this;
   while (sym != NULL)
   {
      if (sym->_name.size() != 0)
      {
         if (name.size() != 0)
         {
            name.insert(0, ".");
         }
         name.insert(0, sym->_name);
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
Symbol::print ()
{
   this->print_depth();
   printf("<Symbol:%s>\n", this->get_qualified_name().c_str());
}

void
Symbol::print_depth ()
{
   for (unsigned i = 0 ; i < this->_depth ; ++i)
   {
      printf("   ");
   }
}

void
Symbol::set_name (char* name, size_t name_len)
{
   this->_name.assign(name, name_len);
}

void
Symbol::set_name (std::string name)
{
   this->_name = name;
}


} }
