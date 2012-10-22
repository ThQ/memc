#include "mem/ast/visitor/Ctor.hpp"


namespace mem { namespace ast { namespace visitor {


Ctor::Ctor ()
{
   _name = "ast.Ctor";
}

void
Ctor::initializeField (st::Field* field, node::Block* ctor)
{
   node::FinalId* self_n = new node::FinalId();
   self_n->setValue("self");

   node::Text* field_name_n = new node::Text();
   field_name_n->setKind(node::MetaKind::ID);
   field_name_n->setValue(field->Name());

   node::Dot* dot_name_n = new node::Dot();
   dot_name_n->setLeftNode(self_n);
   dot_name_n->setRightNode(field_name_n);

   if (field->VirtualFunction() != NULL)
   {
      node::Node* field_val = NULL;
      node::FinalId* vfn = new node::FinalId();
      vfn->setValue(field->VirtualFunction()->Name());
      field_val = vfn;
      assert (field_val != NULL);

      node::VarAssign* var_n = new node::VarAssign();
      var_n->setNameNode(dot_name_n);
      var_n->setValueNode(field_val);

      ctor->addChild(var_n);
   }
}

bool
Ctor::visit (node::Node* node)
{
   assert (node != NULL);

   if (node::isa<node::Class>(node))
   {
      visitClass(node::cast<node::Class>(node));
      return false;
   }
   return true;
}

void
Ctor::visitClass (class node::Class* n)
{
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->BoundSymbol());
   DEBUG_REQUIRE (st::isa<st::Class>(n->BoundSymbol()));

   st::Class* cls_ty = st::cast<st::Class>(n->BoundSymbol());

   // -------
   //  Name
   // -------
   node::Id* name_n = new node::Id();
   name_n->setValue("$ctor");

   // ------------
   //  Parameters
   // ------------
   st::PointerType* self_ty = st::util::getPointerType(cls_ty);
   node::Node* param = node::Func::createParameter("self", self_ty);

   node::NodeList* params_n = new node::NodeList();
   params_n->addChild(param);

   // -------------
   //  Return type
   // -------------
   node::FinalId* return_n = new node::FinalId();
   return_n->setValue("void");

   // ------------
   //  Body block
   // ------------
   node::Block* body_n = new node::Block();

   st::Class* cls = st::cast<st::Class>(n->BoundSymbol());
   st::FieldVector fields = cls->getAllFields();
   st::Field* field = NULL;
   for (size_t i = 0; i < fields.size(); ++i)
   {
      if (st::isa<st::Field>(fields[i]))
      {
         field = fields[i];
         initializeField (field, body_n);
      }
   }

   // ----------
   //  Function
   // ----------
   node::Func* func_n = new node::Func();
   func_n->setValue("$ctor");
   func_n->setNameNode(name_n);
   func_n->setParamsNode(params_n);
   func_n->setReturnTypeNode(return_n);
   func_n->setBodyNode(body_n);

   n->MembersNode()->addChild(func_n);

   visitFuncDecl(n->BoundSymbol(), func_n);
}


} } }
