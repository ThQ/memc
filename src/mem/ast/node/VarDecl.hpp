#ifndef _MEM__AST__NODE__VARDECL__HPP_
#define _MEM__AST__NODE__VARDECL__HPP_


#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"


namespace mem { namespace ast { namespace node {


class VarDecl : public Node
{
   public: VarDecl ();

   public: inline std::string get_name()
   {
      return this->get_name_node()->_value;
   }

   public: inline Text* get_name_node()
   {
      return static_cast<Text*>(this->get_child(0));
   }

   public: inline Node* get_type_node()
   {
      return this->get_child(1);
   }

   public: inline Node* get_value_node()
   {
      return this->get_child(2);
   }
};


} } }

#endif
