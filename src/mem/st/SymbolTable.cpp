#include "mem/st/SymbolTable.hpp"


namespace mem { namespace st {


SymbolTable::SymbolTable ()
{
   _home = new Namespace();
   _home->setName("$home");
   _home->setIsInvisible(true);

   _system = new Namespace();
   _system->setName("$system");
   _system->setIsInvisible(true);

   _root = new Namespace();
   _root->addChild(_home);
   _root->addChild(_system);
   _func_ll_head = NULL;
}

SymbolTable::~SymbolTable ()
{
   delete _root;
}

st::Symbol*
SymbolTable::lookupMember (st::Type* symCurrentType, std::string sSymbolName)
{
   DEBUG_REQUIRE (symCurrentType != NULL);
   DEBUG_REQUIRE (sSymbolName.size() != 0);

   st::Symbol* symLookedFor = NULL;

   while (symCurrentType != NULL)
   {
      symLookedFor = symCurrentType->getChild(sSymbolName);
      if (symLookedFor != NULL)
      {
         break;
      }

      symCurrentType = symCurrentType->ParentType();
   }

   return symLookedFor;
}

st::Symbol*
SymbolTable::lookupSymbol (st::Symbol* scope, std::string symbol_id)
{
   if (st::isa<st::PointerType>(scope))
   {
      scope = st::cast<st::PointerType>(scope)->getNonPointerParent();
   }
   st::Symbol* symbol = lookupSymbolUntil(scope, symbol_id, _root);
   if (symbol == NULL)
   {
      symbol = lookupSymbolUntil(_system, symbol_id, _root);
   }

   return symbol;
}

st::Symbol*
SymbolTable::lookupSymbolUntil (st::Symbol* scope, std::string symbol_id, st::Symbol* symTopScope)
{
   st::Symbol* symCurrentScope = scope;
   st::Symbol* sym = NULL;

   while (symCurrentScope != NULL && symCurrentScope != symTopScope)
   {
      sym = symCurrentScope->getChild(symbol_id);
      if (sym != NULL)
      {
         break;
      }

      symCurrentScope = symCurrentScope->Parent();
   }

   return sym;
}

void
SymbolTable::registerFunction (Func* func)
{
   if (_func_ll_head == NULL)
   {
      _func_ll_head = func;
      _func_ll_tail = func;
   }
   else
   {
      _func_ll_tail->setNextFunction(func);
      _func_ll_tail = func;
   }
}

} }
