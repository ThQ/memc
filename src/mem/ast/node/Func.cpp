#include "mem/ast/node/Func.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Func::Func()
{
   _next_function = NULL;
   _nodeBody = NULL;
   _nodeDecorator = NULL;
   _nodeName = NULL;
   _nodeParams = NULL;
   _nodeReturnType = NULL;
   _type = Func::kTYPE;
}

Func::~Func ()
{
   delete _nodeBody;
   delete _nodeDecorator;
   delete _nodeName;
   delete _nodeParams;
   delete _nodeReturnType;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

node::VarDecl*
Func::createParameter (std::string name, st::Type* ty)
{
   node::FinalId* nodeName = new node::FinalId();
   nodeName->setValue(name);

   node::FinalId* nodeType = new node::FinalId();
   nodeType->setValue(ty->Name());

   node::VarDecl* param = new node::VarDecl();
   param->setNameNode(nodeName);
   param->setTypeNode(nodeType);

   return param;
}

Node*
Func::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeDecorator;
      case 1: return _nodeName;
      case 2: return _nodeParams;
      case 3: return _nodeReturnType;
      case 4: return _nodeBody;
   }
   assert(false);
   return NULL;
}

void
Func::isValid (NodeValidator* v)
{
   Node::isValid(v);

   v->ensure(NameNode() != NULL, "Func: must have a name node");
   v->ensure(ParamsNode() != NULL, "Func: must have a parameter node");
   v->ensure(ReturnTypeNode() != NULL, "Func: must have a return type node");
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
   assert(false);
}


} } }
