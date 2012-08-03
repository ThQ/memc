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
   switch (sym->Kind())
   {
      case ARRAY:
         visitArrayType(static_cast<st::ArrayType*>(sym));
         break;

      case CLASS:
         visitClass(static_cast<st::Class*>(sym));
         break;

      case FIELD:
         visitField(static_cast<st::Field*>(sym));
         break;

      case FUNCTION:
         visitFunction(static_cast<st::Func*>(sym));
         break;

      case INT_TYPE:
         visitIntType(static_cast<st::IntType*>(sym));
         break;

      case NAMESPACE:
         visitNamespace(static_cast<st::Namespace*>(sym));
         break;

      case POINTER:
         visitPointerType(static_cast<st::PointerType*>(sym));
         break;

      case PRIMITIVE_TYPE:
         visitPrimitiveType(static_cast<st::PrimitiveType*>(sym));
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
   for (i=sym->Children().begin(); i != sym->Children().end(); ++i)
   {
      this->visit(i->second);
   }
}

bool
XmlDumper::visitArrayType (st::ArrayType* s)
{
   *_out << "<Array name=\"" + s->Name() + "\"";
   if (s->ItemType() != NULL)
   {
      *_out << " base-type=\"" + s->ItemType()->gQualifiedName() + "\"";
   }
   if (s->hasLength())
   {
      *_out << " size=\"" << s->ArrayLength() << "\"";
   }
   *_out << " byte-size=\"" << s->ByteSize() << "\"";
   *_out << " />\n";

   return true;
}

bool
XmlDumper::visitClass (st::Class* cls_sym)
{
   *_out << "<Class name=\"" + cls_sym->Name() + "\"";
   if (cls_sym->ParentType() != NULL)
   {
      *_out << " parent_type=\"" + cls_sym->ParentType()->gQualifiedName() + "\"";
   }
   *_out << " byte-size=\"" << cls_sym->ByteSize() << "\"";
   *_out << ">\n";
   this->visitChildren(cls_sym);
   *_out << "</Class>";

   return true;
}

bool
XmlDumper::visitField (st::Field* s)
{
   *_out << "<Field name=\"" + s->Name() + "\"";
   if (s->Type() != NULL)
   {
      *_out << " type=\"" + s->Type()->gQualifiedName() + "\"";
   }
   *_out << " />\n";

   return true;
}

bool
XmlDumper::visitFunction (st::Func* func_sym)
{
   *_out << "<Function name=\"" + func_sym->Name() + "\"";
   if (func_sym->ReturnType() != NULL)
   {
      *_out << " return-type=\"" + func_sym->ReturnType()->gQualifiedName() + "\"";
   }
   *_out << ">\n";
   visitChildren(func_sym);
   *_out << "</Function>";

   return true;
}

bool
XmlDumper::visitIntType (st::IntType* s)
{
   *_out << "<IntType name=\"" + s->Name() + "\"";
   *_out << " byte-size=\"" << s->ByteSize() << "\"";
   *_out << " />\n";

   return true;
}

bool
XmlDumper::visitNamespace (st::Namespace* ns_sym)
{
   *_out << "<Namespace name=\"" << ns_sym->Name() << "\">\n";
   visitChildren(ns_sym);
   *_out << "</Namespace>";

   return true;
}

bool
XmlDumper::visitPointerType (st::PointerType* s)
{
   *_out << "<PointerType name=\"" + s->Name() + "\"";
   if (s->PointedType() != NULL)
   {
      *_out << " base-type=\"" + s->PointedType()->gQualifiedName() + "\"";
   }
   *_out << " byte-size=\"" << s->ByteSize() << "\"";
   *_out << " />\n";

   return true;
}

bool
XmlDumper::visitPrimitiveType (st::PrimitiveType* s)
{
   *_out << "<PrimitiveType name=\"" + s->Name() + "\"";
   *_out << " byte-size=\"" << s->ByteSize() << "\"";
   *_out << " />\n";

   return true;
}

bool
XmlDumper::visitVar (st::Var* var_sym)
{
   *_out << "<Variable name=\"" + var_sym->Name() + "\"";
   if (var_sym->Type() != NULL)
   {
      *_out << " type=\"" + var_sym->Type()->gQualifiedName() + "\"";
   }
   *_out << " />\n";

   return true;
}

bool
XmlDumper::visitUnknown (st::Symbol* sym)
{
   *_out << "<Unknown name=\"" + sym->Name() + "\">\n";
   visitChildren(sym);
   *_out << "</Unknown>";

   return true;
}


} } }
