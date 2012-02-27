#include "mem/st/SymbolTable.hpp"


namespace mem { namespace st {


SymbolTable::SymbolTable ()
{
   this->_root = new Namespace();
}

SymbolTable::~SymbolTable ()
{
   delete this->_root;
}

Class*
SymbolTable::create_class (std::string full_class_name)
{
   Class* klass = new Class();
   if (this->create_type (klass, full_class_name))
   {
      return klass;
   }
   else
   {
      delete klass;
      return NULL;
   }
}

bool
SymbolTable::create_type (Type* type, std::string full_type_name)
{
   std::string ns_name;
   std::string type_name;
   mem::Util::partition_full_type_name(full_type_name, ns_name, type_name);
   type->sName(type_name);

   Namespace* ns = 0;
   if (ns_name.size() == 0)
   {
      ns = this->_root;
   }
   else
   {
      ns = this->create_namespace(ns_name);
   }
   assert (ns != 0);
   //printf("NS<%s>@%x +TYPE<%s>@%x\n", ns->_name.c_str(), ns, type->_name.c_str(), type);
   ns->push(type);
   return true;
}

Namespace*
SymbolTable::create_namespace (std::string name)
{
   //printf(" + NS [%s]\n", name.c_str());
   Namespace* ns = NULL;
   char buffer[200];
   size_t buffer_len = 0;
   size_t buffer_cursor = 0;
   Namespace* cur_namespace = this->_root;
   Namespace* child_namespace = NULL;
   for (size_t i = 0 ; i < name.size(); ++i)
   {
      if (name[i] == '.')
      {
         //printf("Try + NS [%s](%d)\n", buffer, buffer_len);
         cur_namespace->get_namespace(child_namespace, (char*)buffer, buffer_len);
         if (child_namespace == NULL)
         {
            Namespace* ns_to_create = new Namespace();
            ns_to_create->sName(buffer, buffer_len);
            ns_to_create = cur_namespace->push(ns_to_create);
            /**if (ns_to_create != 0)
            {
               printf("NS<%s>@%x +NS<%s>@%x\n",
                  cur_namespace->_name.c_str(),
                  (unsigned int)cur_namespace,
                  ns_to_create->_name.c_str(),
                  (unsigned int)ns_to_create);
            }*/
            child_namespace = ns_to_create;
         }
         cur_namespace = child_namespace;
         child_namespace = NULL;
         buffer_cursor = 0;
         buffer_len = 0;
      }
      else
      {
         buffer[buffer_cursor] = name[i];
         buffer_len ++;
         buffer_cursor ++;
      }
   }

   if (buffer_len != 0)
   {
      ns = new Namespace();
      ns->sName((char*)buffer, buffer_len);
      ns = cur_namespace->push(ns);
   }

   return ns;
}

/*
void
SymbolTable::dump ()
{
   this->_root->print();
}
*/

Namespace*
SymbolTable::get_namespace (std::string ns_name)
{
   char buffer[200];
   size_t buffer_len = 0;
   size_t buffer_cursor = 0;
   Namespace* cur_namespace = this->_root;
   Namespace* child_namespace = NULL;

   for (size_t i = 0 ; i < ns_name.size(); ++i)
   {
      if (ns_name[i] == '.')
      {
         cur_namespace->get_namespace(child_namespace, (char*)buffer, buffer_len);
         if (child_namespace == NULL)
         {
            return 0;
         }
         cur_namespace = child_namespace;
         child_namespace = NULL;
         buffer_cursor = 0;
         buffer_len = 0;
      }
      else
      {
         buffer[buffer_cursor] = ns_name[i];
         buffer_len ++;
         buffer_cursor ++;
      }
   }

   if (buffer_len != 0)
   {
      cur_namespace->get_namespace(child_namespace, buffer, buffer_len);
      return child_namespace;
   }

   return 0;
}

bool
SymbolTable::has_class (std::string full_class_name)
{
   std::string ns_name;
   std::string class_name;
   Util::partition_full_type_name(full_class_name, ns_name, class_name);
   Namespace* ns = NULL;
   if (ns_name.size() == 0)
   {
      ns = this->_root;
   }
   else
   {
      ns = this->get_namespace(ns_name);
   }
   Type* klass = NULL;
   if (ns != 0)
   {
      ns->get_type(klass, class_name);
   }
   return klass != NULL;
}

bool
SymbolTable::has_namespace (std::string ns_name)
{
   return this->get_namespace(ns_name) != 0;
}

Symbol*
SymbolTable::get_symbol (std::string name)
{
   Symbol* cur_symbol = this->_root;
   Path path = Path(name);
   std::string cur_symbol_name = "";

   while ((cur_symbol_name = path.next_name()) != "")
   {
      cur_symbol = cur_symbol->getChild(cur_symbol_name);
      if (cur_symbol == NULL)
      {
         return NULL;
      }
   }
   return cur_symbol;
}

Func*
SymbolTable::register_function (std::string func_full_name)
{
   std::string ns_name;
   std::string func_name;
   mem::Util::partition_full_type_name(func_full_name, ns_name, func_name);
   Namespace* ns = this->get_namespace (ns_name);

   if (ns == NULL)
   {
      return NULL;
   }

   Func* func = new Func();
   func->sName(func_name);

   ns->addChild(func);

   return func;
}

bool
SymbolTable::register_symbol (std::string path, Symbol* sym)
{
   assert(sym != NULL);
   Symbol* parent_sym = this->get_symbol(path);
   if (parent_sym != NULL && parent_sym->addChild(sym))
   {
      return true;
   }
   return false;
}

void
SymbolTable::setup ()
{
   this->setupBool();
   this->setupInts();
   this->setupVoid();
}

void
SymbolTable::setupBool ()
{
   this->_glob_bool_cls = new st::Class();
   this->_glob_bool_cls->sName("bool");
   this->_root->addChild(this->_glob_bool_cls);

   this->_root->addChild(new st::Var("true", this->_glob_bool_cls));
   this->_root->addChild(new st::Var("false", this->_glob_bool_cls));
}

void
SymbolTable::setupInts ()
{
   st::Class* int_cls = new st::Class();
   int_cls->sName("int");
   this->_root->addChild(int_cls);

   st::Class* uint_cls = new st::Class();
   uint_cls->sName("uint");
   this->_root->addChild(uint_cls);

   st::Class* char_cls = new st::Class();
   char_cls->sName("char");
   this->_root->addChild(char_cls);
}

void
SymbolTable::setupVoid ()
{
   this->_glob_void_cls = new st::Class();
   this->_glob_void_cls->sName("void");
   this->_root->addChild(this->_glob_void_cls);

   this->_root->addChild(new st::Var("null", this->_glob_void_cls));
}
} }
