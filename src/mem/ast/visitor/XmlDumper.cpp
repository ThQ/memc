#include "mem/ast/dumper/XmlDumper.hpp"

namespace mem { namespace ast { namespace visitor {


bool
XmlDumper::setup ()
{
   *_out << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
   return true;
}

bool
XmlDumper::tearDown ()
{
   return true;
}

void
XmlDumper::visit (node::Node* node)
{
   *_out << "<";

   *_out << node::Node::get_type_name(node->gType());
   if (node->isText())
   {
      *_out << " text=\"";
      *_out << ((node::Text*)node)->_value;
      *_out << "\"";
   }

   if (node->gBoundSymbol() != NULL)
   {
      *_out << " bound=\"";
      *_out << node->gBoundSymbol()->gQualifiedName();
      *_out << "\"";
   }

   if (node->gExprType() != NULL)
   {
      *_out << " type=\"";
      *_out << node->gExprType()->gQualifiedName();
      *_out << "\"";
   }

   if (node->gPosition() != NULL)
   {
      *_out << " line=\"";
      *_out << node->gPosition()->gLine();
      *_out << "\"";
   }

   switch (node->gType())
   {
      case MEM_NODE_NUMBER:
         *_out << " val=\"";
         *_out << static_cast<node::Number*>(node)->getStringFromVal();
         *_out << "\"";
         break;

      case MEM_NODE_FILE:
         *_out << " id=\"";
         *_out << static_cast<node::File*>(node)->_id;
         *_out << "\"";
         break;

      default:
         break;
   }

   if (node->hasChildren())
   {
      *_out << ">\n";
      for (size_t i = 0 ; i < node->gChildCount() ; ++i)
      {
         visit(node->getChild(i));
      }
      *_out << "</";
      *_out << node::Node::get_type_name(node->_type);
      *_out << ">\n";
   }
   else
   {
      *_out << " />\n";
   }
}


} } }
