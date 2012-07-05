#include "mem/st/visitor/XmlDumper.hpp"


namespace mem { namespace st { namespace visitor {


void
XmlDumper::setup ()
{
   *_out << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
}

bool
XmlDumper::visit (st::Symbol* sym)
{
   switch (sym->_kind)
   {
      case NAMESPACE:
         visitNamespace(static_cast<st::Namespace*>(sym));
         break;

      case FUNCTION:
         visitFunction(static_cast<st::Func*>(sym));
         break;

      case CLASS:
         visitClass(static_cast<st::Class*>(sym));
         break;

      case VAR:
         visitVar(static_cast<st::Var*>(sym));
         break;

      default:
         visitUnknown(sym);
   }

   return false;
}

void
XmlDumper::visitChildren (st::Symbol* sym)
{
   st::Symbol::SymbolCollectionIterator i;
   for (i=sym->_children.begin(); i != sym->_children.end(); ++i)
   {
      this->visit(i->second);
   }
}

bool
XmlDumper::visitClass (st::Class* cls_sym)
{
   *_out << "<Class name=\"" + cls_sym->gName() + "\"";
   if (cls_sym->_parent_type != NULL)
   {
      *_out << " parent_type=\"" + cls_sym->_parent_type->gQualifiedName() + "\"";
   }
   *_out << ">\n";
   this->visitChildren(cls_sym);
   *_out << "</Class>";

   return true;
}

bool
XmlDumper::visitFunction (st::Func* func_sym)
{
   *_out << "<Function name=\"" + func_sym->gName() + "\"";
   if (func_sym->gOverloadedFunc() != NULL)
   {
      *_out << " overload=\"" + func_sym->gOverloadedFunc()->gQualifiedName() + "\"";
   }
   if (func_sym->gReturnType() != NULL)
   {
      *_out << " return_type=\"" + func_sym->gReturnType()->gQualifiedName() + "\"";
   }
   *_out << ">\n";
   visitChildren(func_sym);
   *_out << "</Function>";

   return true;
}

bool
XmlDumper::visitNamespace (st::Namespace* ns_sym)
{
   *_out << "<Namespace name=\"" + ns_sym->_name + "\">\n";
   visitChildren(ns_sym);
   *_out << "</Namespace>";

   return true;
}

bool
XmlDumper::visitVar (st::Var* var_sym)
{
   *_out << "<Variable name=\"" + var_sym->gName() + "\"";
   if (var_sym->_type != NULL)
   {
      *_out << " type=\"" + var_sym->_type->gQualifiedName() + "\"";
   }
   *_out << ">\n";
   this->visitChildren(var_sym);
   *_out << "</Variable>";

   return true;
}

bool
XmlDumper::visitUnknown (st::Symbol* sym)
{
   *_out << "<Unknown name=\"" + sym->gName() + "\">\n";
   visitChildren(sym);
   *_out << "</Unknown>";

   return true;
}


} } }
