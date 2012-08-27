#include "mem/ast/node/File.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

File::File ()
{
   _type = File::kTYPE;
   _function_ll_head = NULL;
   _function_ll_tail = NULL;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
File::isValid (NodeValidator* v)
{
   Node::isValid(v);

   Node* child = NULL;
   for (size_t i = 0 ; i < ChildCount(); ++i)
   {
      child = getChild(i);

      v->ensure(node::isa<Use>(child)
         || node::isa<Class>(child)
         || node::isa<EnumType>(child)
         || node::isa<Func>(child),
         "Children of a File node must be either Use, Class or Func");
   }
}

void
File::registerFunction (node::Func* func)
{
   if (_function_ll_head == NULL)
   {
      _function_ll_head = func;
      _function_ll_tail = func;
   }
   else
   {
      _function_ll_tail->setNextFunction(func);
      _function_ll_tail = func;
   }
}

} } }
