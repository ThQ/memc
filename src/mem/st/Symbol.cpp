#include "mem/st/Symbol.hpp"

namespace mem { namespace st {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Symbol::Symbol ()
{
   _child_count = 0;
   _depth = 0;
   _is_invisible = false;
   _kind = Symbol::kTYPE;
   _parent = NULL;
}

Symbol::~Symbol ()
{
   std::map<std::string, Symbol*>::iterator i = _children.begin();
   for(; i != _children.end(); ++i)
   {
      delete i->second;
   }
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Symbol*
Symbol::gExprType ()
{
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

std::vector<Symbol*>
Symbol::getParents ()
{
   std::vector<Symbol*> parents;

   Symbol* parent = _parent;

   while (parent != NULL)
   {
      parents.insert(parents.begin(), parent);
      parent = parent->_parent;
   }
   return parents;
}

std::string
Symbol::gQualifiedName ()
{
   std::string name = "";
   Symbol* sym = this;
   while (sym != NULL)
   {
      if (sym->Name().size() != 0
#ifdef NDEBUG
          && !sym->IsInvisible()
#endif
          )
      {
         if (name.size() != 0)
         {
            name.insert(0, ".");
         }
         name.insert(0, sym->Name());
      }
      sym = sym->Parent();
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
Symbol::isReferenceSymbol() const
{
   switch (_kind)
   {
      case st::MetaKind::VAR:
      case st::MetaKind::ARG:
      case st::MetaKind::ARRAY_TYPE:
      case st::MetaKind::POINTER_TYPE:
         return true;
      default:
         return false;
   }
   DEBUG_UNREACHABLE();
}

void
Symbol::rename (std::string new_name)
{
   if (Parent() != NULL)
   {
      Parent()->renameChild(Name(), new_name);
   }
   else
   {
      setName(new_name);
   }
}

void
Symbol::renameChild (std::string old_name, std::string new_name)
{
   st::Symbol* sym = NULL;
   if (_children.find(old_name) != _children.end())
   {
      sym = _children[old_name];
      st::Symbol* parent = sym->Parent();
      sym->setParent(NULL);
      sym->setName(new_name);
      sym->setParent(parent);
      _children.erase(old_name);
      _children[new_name] = sym;
   }
}

} }
