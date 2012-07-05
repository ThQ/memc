#include "mem/ast/node/Func.hpp"


namespace mem { namespace ast { namespace node {


Func::Func()
{
   _type = MEM_NODE_FUNCTION_DECLARATION;
}

Block*
Func::gBodyNode ()
{
   for (size_t i = 0 ; i < gChildCount() ; ++i)
   {
      if (getChild(i)->isBlockNode())
      {
         return static_cast<Block*>(getChild(i));
      }
   }
   return NULL;
}

Node*
Func::gParamsNode ()
{
   for (size_t i = 0 ; i < gChildCount() ; ++i)
   {
      if (getChild(i)->isFuncParamsNode())
      {
         return getChild(i);
      }
   }
   return NULL;
}

Node*
Func::gReturnTypeNode ()
{
   for (size_t i = 0 ; i < gChildCount() ; ++i)
   {
      if (!getChild(i)->isFuncParamsNode() && !getChild(i)->isBlockNode())
      {
         return getChild(i);
      }
   }
   return NULL;
}

bool
Func::isVirtual ()
{
   return gBodyNode() == NULL;
}


} } }
