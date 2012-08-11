#include "mem/ast/visitor/XmlDumper.hpp"

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

bool
XmlDumper::visit (node::Node* node)
{
   *_out << "<";

   if (node != NULL)
   {
      *_out << node->KindName();
      if (node->isText())
      {
         *_out << " text=\"";
         *_out << ((node::Text*)node)->_value;
         *_out << "\"";
      }

      if (node->BoundSymbol() != NULL)
      {
         *_out << " bound=\"";
         *_out << node->BoundSymbol()->gQualifiedName();
         *_out << "\"";
      }

      if (node->ExprType() != NULL)
      {
         *_out << " type=\"";
         *_out << node->ExprType()->gQualifiedName();
         *_out << "\"";
      }

      if (node->Position() != NULL)
      {
         *_out << " position-start=\"";
         *_out << node->Position()->LineStart();
         *_out << ":";
         *_out << node->Position()->ColumnStart();
         *_out << "\" position-end=\"";
         *_out << node->Position()->LineEnd();
         *_out << ":";
         *_out << node->Position()->ColumnEnd();
         *_out << "\"";
      }

      switch (node->Kind())
      {
         case node::Kind::FILE:
            *_out << " id=\"";
            *_out << static_cast<node::File*>(node)->Id();
            *_out << "\"";
            break;

         default:
            break;
      }

      if (node->hasChildren())
      {
         *_out << ">\n";
         for (size_t i = 0 ; i < node->ChildCount() ; ++i)
         {
            visit(node->getChild(i));
         }
         *_out << "</";
         *_out << node->KindName();
         *_out << ">\n";
      }
      else
      {
         *_out << " />\n";
      }
   }
   else
   {
      *_out << "NULL />\n";
   }

   return false;
}


} } }
