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
      if (this->get_child(i)->_type == MEM_NODE_BLOCK)
      {
         return (Block*)this->get_child(i);
      }
   }
   return NULL;
}

Node*
Function::g_parameters_node ()
{
   for (int i = 0 ; i < this->_child_count ; ++i)
   {
      if (this->get_child(i)->_type == MEM_NODE_FUNCTION_PARAMETERS)
      {
         return this->get_child(i);
      }
   }
   return NULL;
}

Node*
Function::g_return_type_node ()
{
   for (int i = 0 ; i < this->_child_count ; ++i)
   {
      if (this->get_child(i)->_type != MEM_NODE_FUNCTION_PARAMETERS && this->get_child(i)->_type != MEM_NODE_BLOCK)
      {
         return this->get_child(i);
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
