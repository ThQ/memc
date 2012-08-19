#include "mem/ast/node/Func.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Func::Func()
{
   _type = Kind::FUNCTION;
   _next_function = NULL;
}

Block*
Func::BodyNode ()
{
   for (size_t i = 0 ; i < ChildCount() ; ++i)
   {
      if (getChild(i)->isBlockNode())
      {
         return static_cast<Block*>(getChild(i));
      }
   }
   return NULL;
}

Decorator*
Func::DecoratorNode () const
{
   for (size_t i = 0; i < ChildCount(); ++i)
   {
      if (getChild(i)->isDecoratorNode())
      {
         return static_cast<Decorator*>(getChild(i));
      }
   }
   return NULL;
}

Node*
Func::ParamsNode ()
{
   for (size_t i = 0 ; i < ChildCount() ; ++i)
   {
      if (getChild(i)->isFuncParamsNode())
      {
         return getChild(i);
      }
   }
   return NULL;
}

Node*
Func::ReturnTypeNode ()
{
   for (size_t i = 0 ; i < ChildCount() ; ++i)
   {
      if (!getChild(i)->isFuncParamsNode() && !getChild(i)->isBlockNode() && !getChild(i)->isDecoratorNode())
      {
         return getChild(i);
      }
   }
   return NULL;
}

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

node::Node*
Func::createParameter (std::string name, st::Type* ty)
{
   node::Text* name_n = new node::Text();
   name_n->setKind(Kind::ID);
   name_n->sValue(name);

   node::FinalId* type_n = new node::FinalId();
   type_n->sValue(ty->Name());

   node::Node* param = new node::Node();
   param->setKind(Kind::FUNCTION_PARAMETER);
   param->pushChildren(name_n, type_n);

   return param;
}

bool
Func::isVirtual ()
{
   return BodyNode() == NULL;
}

Func*
castToFunc (Node* n)
{
   assert (n->isFuncNode());
   return static_cast<Func*>(n);
}
} } }
