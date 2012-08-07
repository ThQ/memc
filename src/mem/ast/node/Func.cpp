#include "mem/ast/node/Func.hpp"


namespace mem { namespace ast { namespace node {


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

bool
Func::isVirtual ()
{
   return BodyNode() == NULL;
}


} } }
