#include "mem/ast/visitor/Ctor.hpp"


namespace mem { namespace ast { namespace visitor {


Ctor::Ctor ()
{
   _name = "ast.Ctor";
}

void
Ctor::initializeField (st::Field* field, node::Block* ctor)
{
   st::Type* field_ty = field->Type();

   node::FinalId* self_n = new node::FinalId();
   self_n->sValue("self");

   node::Text* field_name_n = new node::Text();
   field_name_n->setKind(node::Kind::ID);
   field_name_n->sValue(field->Name());

   node::Dot* dot_name_n = new node::Dot();
   dot_name_n->pushChildren(self_n, field_name_n);

   // ---------
   //  Integer
   // ---------
   if (field_ty->isIntType())
   {
      st::IntConstant* ic = st::util::getNativeCharConstant(_symbols->System(), 0);
      ic->setType(_symbols->_core_types._char);

      node::Number* value_n = new node::Number();
      value_n->setBoundSymbol(ic);
      value_n->setExprType(_symbols->_core_types._char);

      node::VarAssign* var_n = new node::VarAssign();
      var_n->pushChildren(dot_name_n, value_n);

      ctor->pushChild(var_n);
   }
   // ---------
   //  Pointer
   // ---------
   else if (field_ty->isPointerType())
   {
      node::Node* field_val = NULL;

      if (field->VirtualFunction() != NULL)
      {
         node::FinalId* vfn = new node::FinalId();
         vfn->sValue(field->VirtualFunction()->Name());
         field_val = vfn;
      }
      else
      {
         node::FinalId* nul = new node::FinalId();
         nul->sValue("NULL");
         field_val = nul;
      }

      node::VarAssign* var_n = new node::VarAssign();
      var_n->pushChildren(dot_name_n, field_val);

      ctor->pushChild(var_n);
   }
}

bool
Ctor::visit (node::Node* node)
{
   assert (node != NULL);

   if (node->isClassNode())
   {
      visitClass(static_cast<node::Class*>(node));
      return false;
   }
   return true;
}

void
Ctor::visitClass (class node::Class* n)
{
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->BoundSymbol());
   DEBUG_REQUIRE (n->BoundSymbol()->isClassType());

   st::Class* cls_ty = static_cast<st::Class*>(n->BoundSymbol());

   // ------------
   //  Parameters
   // ------------
   st::PointerType* self_ty = st::util::getPointerType(cls_ty);
   node::Node* param = node::Func::createParameter("self", self_ty);

   node::Node* params_n = new node::Node();
   params_n->setKind(node::Kind::FUNCTION_PARAMETERS);
   params_n->pushChild(param);

   // -------------
   //  Return type
   // -------------
   node::FinalId* return_n = new node::FinalId();
   return_n->sValue("void");

   // ------------
   //  Body block
   // ------------
   node::Block* body_n = new node::Block();

   st::Class* cls = static_cast<st::Class*>(n->BoundSymbol());
   st::FieldVector fields = cls->getAllFields();
   st::Field* field = NULL;
   for (size_t i = 0; i < fields.size(); ++i)
   {
      if (fields[i]->isFieldSymbol())
      {
         field = fields[i];
         initializeField (field, body_n);
      }
   }

   // ----------
   //  Function
   // ----------
   node::Func* func_n = new node::Func();
   func_n->sValue("__ctor__");
   func_n->pushChildren(params_n, return_n, body_n);

   n->insertChild(func_n);

   visitFuncDecl(n->BoundSymbol(), func_n);
}


} } }
