#include "mem/st/Namespace.hpp"

namespace mem { namespace st {


Namespace::Namespace ()
{
   this->_kind = NAMESPACE;
}

Type*
Namespace::get_type (Type*& dest, std::string type_name)
{
   if (this->_children.find(type_name) != this->_children.end())
   {
      dest = static_cast<Type*>(this->_children[type_name]);
      return NULL;
   }
   dest = NULL;
   return NULL;

}

Namespace*
Namespace::get_namespace (Namespace*& dest, char* name, size_t name_len)
{
   std::string ns_name;
   ns_name.assign(name, name_len);
   if (this->has_symbol(ns_name))
   {
      dest = static_cast<Namespace*>(this->_children[ns_name]);
      return NULL;
   }
   //printf("NS[%s] not found\n", ns_name.c_str());
   dest = NULL;
   return NULL;
}

bool
Namespace::has_symbol (std::string name)
{
   return this->_children.find(name) != this->_children.end();
}

void
Namespace::print ()
{
   this->print_depth();
   printf("<Namespace:%s @x%x>(%d)\n",
      this->_name.c_str(),
      (unsigned int)this,
      this->_children.size());

   for (std::map<std::string, Symbol*>::iterator i = this->_children.begin() ; i != this->_children.end() ; ++ i)
   {
      ASSERT_NOT_NULL(i->second);
      i->second->print();
   }
}

Namespace*
Namespace::push (Namespace* ns)
{
   if (this->_children.find(ns->_name.c_str()) == this->_children.end())
   {
      ns->_depth = this->_depth + 1;
      this->_children[ns->_name] = ns;
      return ns;
   }
   return static_cast<Namespace*>(this->_children[ns->_name]);
}

Type*
Namespace::push (Type* type)
{
   if (this->_children.find(type->_name.c_str()) == this->_children.end())
   {
      type->_depth = this->_depth + 1;
      this->_children[type->_name] = type;
      return type;
   }
   return static_cast<Type*>(this->_children[type->_name]);
}


} }
