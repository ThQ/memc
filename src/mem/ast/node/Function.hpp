#ifndef _MEM__AST__NODE__FUNCTION__HPP_
#define _MEM__AST__NODE__FUNCTION__HPP_


#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class Function : public Text
{
   public: Function();

   public: node::Block* g_body_node ();
   public: Node* g_parameters_node ();
   public: Node* g_return_type_node ();
   public: bool is_virtual ();
};

} } }

#endif
