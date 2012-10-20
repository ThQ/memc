#ifndef _MEM__AST__DUMPER__XML_DUMPER__HPP_
#define _MEM__AST__DUMPER__XML_DUMPER__HPP_


#include "mem/ast/node/ArrayType.hpp"
#include "mem/ast/node/BinaryOp.hpp"
#include "mem/ast/node/Call.hpp"
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Dot.hpp"
#include "mem/ast/node/Field.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/For.hpp"
#include "mem/ast/node/If.hpp"
#include "mem/ast/node/NodeList.hpp"
#include "mem/ast/node/New.hpp"
#include "mem/ast/node/Number.hpp"
#include "mem/ast/node/PointerType.hpp"
#include "mem/ast/node/Return.hpp"
#include "mem/ast/node/Root.hpp"
#include "mem/ast/node/VarAssign.hpp"
#include "mem/ast/node/VarDecl.hpp"
#include "mem/ast/node/While.hpp"
#include "mem/ast/visitor/Dumper.hpp"


namespace mem { namespace ast { namespace visitor {


// Dumps the AST as XML.
class XmlDumper : public Dumper
{
   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   void
   dumpBoundSymbol (node::Node* n);

   void
   dumpExprType (node::Node* n);

   void
   dumpPosition (node::Node* n);

   virtual bool
   setup ();

   virtual bool
   tearDown ();

   virtual bool
   visit (node::Node* node);

   void
   visitArithmeticOp (node::Node* n);

   void
   visitArrayType (node::ArrayType* n);

   void
   visitBlock (node::Block* n);

   void
   visitCall (node::Call* n);

   void
   visitClass (node::Class* n);

   void
   visitChildrenOf (node::Node* n);

   void
   visitCompOp (node::BinaryOp* n);

   void
   visitDot (node::Dot* n);

   void
   visitField (node::Field* n);

   void
   visitFile (node::File* n);

   void
   visitFinalId (node::FinalId* n);

   void
   visitFunction (node::Func* n);

   void
   visitFor (node::For* n);

   void
   visitId (node::Text* n);

   void
   visitIf (node::If* n);

   void
   visitNew (node::New* n);

   void
   visitNodeList (node::NodeList* n);

   void
   visitNumber (node::Number* n);

   void
   visitPlaceHolder (node::Node* n);

   void
   visitPointerType (node::PointerType* n);

   void
   visitReturn (node::Return* n);

   void
   visitRoot (node::Root* n);

   void
   visitVarAssign (node::VarAssign* n);

   void
   visitVarDecl (node::VarDecl* n);

   void
   visitWhile (node::While* n);
};


} } }


#endif
