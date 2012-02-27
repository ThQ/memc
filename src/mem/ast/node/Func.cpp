#include "mem/ast/node/Func.hpp"


namespace mem { namespace ast { namespace node {


Func::Func()
{
   this->_type = MEM_NODE_FUNCTION_DECLARATION;
}

Block*
Func::gBodyNode ()
{
   for (int i = 0 ; i < this->_child_count ; ++i)
   {
      if (this->getChild(i)->isType(MEM_NODE_BLOCK))
      {
         return static_cast<Block*>(this->getChild(i));
      }
   }
   return NULL;
}

Node*
Func::gParamsNode ()
{
   for (int i = 0 ; i < this->_child_count ; ++i)
   {
      if (this->getChild(i)->isType(MEM_NODE_FUNCTION_PARAMETERS))
      {
         return this->getChild(i);
      }
   }
   return NULL;
}

Node*
Func::gReturnTypeNode ()
{
   for (int i = 0 ; i < this->_child_count ; ++i)
   {
      if (this->getChild(i)->_type != MEM_NODE_FUNCTION_PARAMETERS && this->getChild(i)->_type != MEM_NODE_BLOCK)
      {
         return this->getChild(i);
      }
   }
   return NULL;
}

bool
Func::isVirtual ()
{
   return this->gBodyNode() == NULL;
}


} } }
