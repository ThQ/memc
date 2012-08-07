#include "mem/st/Symbol.hpp"

namespace mem { namespace st {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Symbol::Symbol ()
{
   _child_count = 0;
   _depth = 0;
   _kind = UNKNOWN;
   _md = NULL;
   _parent = NULL;
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
      if (sym->Name().size() != 0)
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
Symbol::isAnyType () const
{
   switch (_kind)
   {
      case st::CLASS:
      case st::INT_TYPE:
      case st::PRIMITIVE_TYPE:
      case st::POINTER:
      case st::TUPLE_TYPE:
      case st::ARRAY:
         return true;
      default:
         return false;
   }
   DEBUG_UNREACHABLE();
}

bool
Symbol::isAnyPrimitiveType () const
{
   switch (_kind)
   {
      case st::INT_TYPE:
      case st::PRIMITIVE_TYPE:
         return true;
      default:
         return false;
   }
   DEBUG_UNREACHABLE();
}

bool
Symbol::isReferenceSymbol() const
{
   switch (_kind)
   {
      case VAR:
      case ARG:
      case ARRAY:
      case POINTER:
         return true;
      default:
         return false;
   }
   DEBUG_UNREACHABLE();
}


} }
