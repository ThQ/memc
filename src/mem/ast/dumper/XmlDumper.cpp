#include "mem/ast/dumper/XmlDumper.hpp"

namespace mem { namespace ast { namespace dumper {


std::string
XmlDumper::dump (node::Node* root)
{
   std::ostringstream res;
   res << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
   this->dump_node(res, root, 0);
   return res.str();
}

void
XmlDumper::dump_node (std::ostringstream& dump, node::Node* node, unsigned int level)
{
   dump << this->get_indent(level);
   dump << "<";

   dump << node::Node::get_type_name(node->gType());
   if (node->isText())
   {
      dump << " text=\"";
      dump << ((node::Text*)node)->_value;
      dump << "\"";
   }

   if (node->gBoundSymbol() != NULL)
   {
      dump << " bound=\"";
      dump << node->gBoundSymbol()->gQualifiedName();
      dump << "\"";
   }

   if (node->gExprType() != NULL)
   {
      dump << " type=\"";
      dump << node->gExprType()->gQualifiedName();
      dump << "\"";
   }

   if (node->gPosition() != NULL)
   {
      dump << " line=\"";
      dump << node->gPosition()->gLine();
      dump << "\"";
   }

   switch (node->gType())
   {
      case MEM_NODE_NUMBER:
         dump << " val=\"";
         dump << static_cast<node::Number*>(node)->getStringFromVal();
         dump << "\"";
         break;

      case MEM_NODE_FILE:
         dump << " id=\"";
         dump << static_cast<node::File*>(node)->_id;
         dump << "\"";
         break;

      default:
         break;
   }

   if (node->hasChildren())
   {
      dump << ">\n";
      for (size_t i = 0 ; i < node->_child_count ; ++i)
      {
         this->dump_node(dump, node->getChild(i), level+1);
      }
      dump << this->get_indent(level);
      dump << "</";
      dump << node::Node::get_type_name(node->_type);
      dump << ">\n";
   }
   else
   {
      dump << " />\n";
   }
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
