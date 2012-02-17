#include "mem/ast/dumper/XmlDumper.hpp"

namespace mem { namespace ast { namespace dumper {


std::string
XmlDumper::dump (node::Node* root)
{
   std::string res = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
   res += this->dump_node(root, 0);
   return res;
}

std::string
XmlDumper::dump_node (node::Node* node, unsigned int level)
{
   std::string dump = this->get_indent(level) + "<";
   dump += node::Node::get_type_name(node->_type);
   if (node->is_text())
   {
      dump += " text=\"";
      dump += ((node::Text*)node)->_value;
      dump += "\"";
   }

   if (node->_bound_type != NULL)
   {
      dump += " bound_type=\"";
      dump += node->_bound_type->get_qualified_name();
      dump += "\"";
   }

   if (node->_exp_type != NULL)
   {
      dump += " expr_type=\"";
      dump += node->_exp_type->get_qualified_name();
      dump += "\"";
   }

   if (node->has_children())
   {
      dump += ">\n";
      for (unsigned int i = 0 ; i < node->_child_count ; ++i)
      {
         dump += this->dump_node(node->get_child(i), level+1);
      }
      dump += this->get_indent(level);
      dump += "</";
      dump += node::Node::get_type_name(node->_type);
      dump += ">\n";
   }
   else
   {
      dump += " />\n";
   }
   return dump;
}


std::string
XmlDumper::get_indent (unsigned int level)
{
   std::string indent = "";
   for (unsigned int i = 0 ; i < level ; ++i)
   {
      indent += "   ";
   }
   return indent;
}

} } }
