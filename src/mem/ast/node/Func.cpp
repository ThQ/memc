#include "mem/ast/node/Func.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Func::Func()
{
   _body_node = NULL;
   _decorator_node = NULL;
   _name_node = NULL;
   _next_function = NULL;
   _params_node = NULL;
   _type = Func::kTYPE;
   _return_type_node = NULL;
}

Func::~Func ()
{
   delete _body_node;
   delete _decorator_node;
   delete _name_node;
   delete _params_node;
   delete _return_type_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

node::VarDecl*
Func::createParameter (std::string name, st::Type* ty)
{
   node::FinalId* name_n = new node::FinalId();
   name_n->setValue(name);

   node::FinalId* type_n = new node::FinalId();
   type_n->setValue(ty->Name());

   node::VarDecl* param = new node::VarDecl();
   param->setNameNode(name_n);
   param->setTypeNode(type_n);

   return param;
}

Node*
Func::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _decorator_node;
      case 1: return _name_node;
      case 2: return _params_node;
      case 3: return _return_type_node;
      case 4: return _body_node;
   }
   return NULL;
}

bool
Func::isVirtual ()
{
   return BodyNode() == NULL;
}

void
Func::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setDecoratorNode(node::cast<Decorator>(n));break;
      case 1: setNameNode(node::cast<Id>(n));break;
      case 2: setParamsNode(n);break;
      case 3: setReturnTypeNode(n);break;
      case 4: setBodyNode(node::cast<Block>(n));break;
   }
}


} } }
