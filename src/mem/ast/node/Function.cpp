#include "mem/ast/node/Function.hpp"


namespace mem { namespace ast { namespace node {


Function::Function ()
{
   this->_type = MEM_NODE_FUNCTION_DECLARATION;
}

Block*
Function::g_body_node ()
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
Function::g_parameters_node ()
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
Function::g_return_type_node ()
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
Function::is_virtual ()
{
   return this->g_body_node() == NULL;
}


} } }
