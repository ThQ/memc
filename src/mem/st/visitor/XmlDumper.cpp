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
      case st::MetaKind::ARG:
         visitArgument(st::cast<st::Arg>(sym));
         break;

      case st::MetaKind::ARRAY_TYPE:
         visitArrayType(st::cast<st::ArrayType>(sym));
         break;

      case st::MetaKind::CLASS_TYPE:
         visitClass(st::cast<st::Class>(sym));
         break;

      case st::MetaKind::ENUM_TYPE:
         visitEnumType(st::cast<st::EnumType>(sym));
         break;

      case st::MetaKind::INT_CONSTANT:
         visitIntConstant(st::cast<st::IntConstant>(sym));
         break;

      case st::MetaKind::FIELD:
         visitField(st::cast<st::Field>(sym));
         break;

      case st::MetaKind::FUNCTION:
         visitFunction(st::cast<st::Func>(sym));
         break;

      case st::MetaKind::INT_TYPE:
         visitIntType(st::cast<st::IntType>(sym));
         break;

      case st::MetaKind::NAMESPACE:
         visitNamespace(st::cast<st::Namespace>(sym));
         break;

      case st::MetaKind::POINTER_TYPE:
         visitPointerType(st::cast<st::PointerType>(sym));
         break;

      case st::MetaKind::PRIMITIVE_TYPE:
         visitPrimitiveType(st::cast<st::PrimitiveType>(sym));
         break;

      case st::MetaKind::TUPLE_TYPE:
         visitTupleType(st::cast<st::TupleType>(sym));
         break;

      case st::MetaKind::VAR:
         visitVar(st::cast<st::Var>(sym));
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
XmlDumper::visitArgument (st::Arg* s)
{
   *_out << "<Argument name=\"" + s->Name() + "\"";
   if (s->Type() != NULL)
   {
      *_out << " type=\"" + s->Type()->gQualifiedName() + "\"";
   }
   *_out << " />\n";

   return true;
}

bool
XmlDumper::visitArrayType (st::ArrayType* s)
{
   *_out << "<ArrayType name=\"" + s->Name() + "\"";
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
XmlDumper::visitEnumType (st::EnumType* e)
{
   *_out << "<EnumType name=\"" + e->Name() + "\"";
   *_out << " byte-size=\"" << e->ByteSize() << "\"";
   *_out << ">\n";
   this->visitChildren(e);
   *_out << "</EnumType>";

   return true;
}

bool
XmlDumper::visitClass (st::Class* cls_sym)
{
   *_out << "<ClassType name=\"" + cls_sym->Name() + "\"";
   if (cls_sym->ParentClass() != NULL)
   {
      *_out << " parent-class=\"" + cls_sym->ParentClass()->gQualifiedName() + "\"";
   }
   if (cls_sym->DefaultCtor() != NULL)
   {
      *_out << " default-ctor=\"" << cls_sym->DefaultCtor()->gQualifiedName() << "\"";
   }
   *_out << " absolute-field-count=\"" << cls_sym->getAbsoluteFieldCount() << "\"";
   *_out << " byte-size=\"" << cls_sym->ByteSize() << "\"";
   *_out << ">\n";
   this->visitChildren(cls_sym);
   *_out << "</ClassType>";

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
   if (func_sym->Type() != NULL)
   {
      *_out << " type=\"" + func_sym->Type()->gQualifiedName() + "\"";
   }
   if (func_sym->IsVirtual())
   {
      *_out << " virtual=\"true\"";
   }
   *_out << ">\n";
   visitChildren(func_sym);
   *_out << "</Function>";

   return true;
}
bool
XmlDumper::visitIntConstant (st::IntConstant* s)
{
   *_out << "<IntConstant name=\"" << s->Name() << "\"";
   *_out << " byte-size=\"" << s->ByteSize() << "\"";
   *_out << " signed=\"" << (s->IsSigned() ? "true" : "false") << "\"";
   *_out << " />\n";
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
XmlDumper::visitTupleType (st::TupleType* s)
{
   *_out << "<TupleType name=\"" + s->Name() + "\"";
   *_out << " byte-size=\"" << s->ByteSize() << "\"";
   if (s->hasChildren())
   {
      *_out << ">\n";
      visitChildren(s);
      *_out << "</TupleType>\n";
   }
   else
   {
      *_out << " />\n";
   }

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
   *_out << " constant=\"" << (var_sym->IsConstant() ? "true" : "false") << "\"";
   *_out << " global=\"" << (var_sym->IsGlobal() ? "true" : "false") << "\"";
   if (var_sym->ConstantValue() != NULL)
   {
      *_out << " constant-value=\"" << var_sym->ConstantValue()->gQualifiedName() << "\"";
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
