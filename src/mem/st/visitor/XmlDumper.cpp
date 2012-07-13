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
      case CLASS:
         visitClass(static_cast<st::Class*>(sym));
         break;

      case FIELD:
         visitField(static_cast<st::Field*>(sym));
         break;

      case FUNCTION:
         visitFunction(static_cast<st::Func*>(sym));
         break;

      case NAMESPACE:
         visitNamespace(static_cast<st::Namespace*>(sym));
         break;

      case POINTER:
         visitPointer(static_cast<st::Ptr*>(sym));
         break;

      case PRIMITIVE:
         visitPrimitive(static_cast<st::Primitive*>(sym));
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
XmlDumper::visitField (st::Field* s)
{
   *_out << "<Field name=\"" + s->gName() + "\"";
   if (s->_type != NULL)
   {
      *_out << " type=\"" + s->_type->gQualifiedName() + "\"";
   }
   *_out << " />\n";

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
      *_out << " return-type=\"" + func_sym->gReturnType()->gQualifiedName() + "\"";
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
XmlDumper::visitPointer (st::Ptr* s)
{
   *_out << "<PointerType name=\"" + s->gName() + "\"";
   if (s->gBaseType() != NULL)
   {
      *_out << " base-type=\"" + s->gBaseType()->gQualifiedName() + "\"";
   }
   *_out << " />\n";

   return true;
}

bool
XmlDumper::visitPrimitive (st::Primitive* s)
{
   *_out << "<Primitive name=\"" + s->gName() + "\"";
   if (s->_parent_type != NULL)
   {
      *_out << " parent_type=\"" + s->_parent_type->gQualifiedName() + "\"";
   }
   *_out << " />\n";

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
   *_out << " />\n";

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
