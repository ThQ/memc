#include "mem/ast/visitor/Ctor.hpp"


namespace mem { namespace ast { namespace visitor {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Ctor::Ctor ()
{
   _name = "ast.Ctor";
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
Ctor::initializeField (st::Field* symField, node::Block* nodeCtorBlock)
{
   node::FinalId* nodeSelf = new node::FinalId();
   nodeSelf->setValue("self");

   node::Text* nodeFieldName = new node::Text();
   nodeFieldName->setKind(node::MetaKind::ID);
   nodeFieldName->setValue(symField->Name());

   node::Dot* nodeDotName = new node::Dot();
   nodeDotName->setLeftNode(nodeSelf);
   nodeDotName->setRightNode(nodeFieldName);

   if (symField->VirtualFunction() != NULL)
   {
      node::FinalId* nodeVirtualFuncName = new node::FinalId();
      nodeVirtualFuncName->setValue(symField->VirtualFunction()->Name());

      node::VarAssign* nodeField = new node::VarAssign();
      nodeField->setNameNode(nodeDotName);
      nodeField->setValueNode(nodeVirtualFuncName);

      nodeCtorBlock->addChild(nodeField);
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
   // Create a constructor function whose signature is:
   // >>> $ctor (self :ClassType) -> void

   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->BoundSymbol());
   DEBUG_REQUIRE (st::isa<st::Class>(n->BoundSymbol()));

   st::Class* symClass = st::cast<st::Class>(n->BoundSymbol());

   // -------
   //  Name
   // -------
   node::Id* nodeName = new node::Id();
   nodeName->setValue("$ctor");

   // ------------
   //  Parameters
   // ------------
   st::PointerType* symSelfType = st::util::getPointerType(symClass);
   node::Node* nodeSelfParam = node::Func::createParameter("self", symSelfType);

   node::NodeList* nodeParams = new node::NodeList();
   nodeParams->addChild(nodeSelfParam);

   // -------------
   //  Return type
   // -------------
   node::FinalId* nodeReturn = new node::FinalId();
   nodeReturn->setValue("void");

   // ------------
   //  Body block
   // ------------
   node::Block* nodeBody = new node::Block();

   st::FieldVector fields = symClass->getAllFields();
   st::Field* symField = NULL;
   for (size_t i = 0; i < fields.size(); ++i)
   {
      if (st::isa<st::Field>(fields[i]))
      {
         symField = fields[i];
         initializeField (symField, nodeBody);
      }
   }

   // ----------
   //  Function
   // ----------
   node::Func* nodeFunc = new node::Func();
   nodeFunc->setValue("$ctor");
   nodeFunc->setNameNode(nodeName);
   nodeFunc->setParamsNode(nodeParams);
   nodeFunc->setReturnTypeNode(nodeReturn);
   nodeFunc->setBodyNode(nodeBody);

   n->MembersNode()->addChild(nodeFunc);

   visitFuncDecl(n->BoundSymbol(), nodeFunc);
}


} } }
