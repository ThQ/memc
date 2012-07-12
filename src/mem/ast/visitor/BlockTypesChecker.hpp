#ifndef _MEM__AST__VISITOR__BLOCK_TYPES_CHECKER__HPP_
#define _MEM__AST__VISITOR__BLOCK_TYPES_CHECKER__HPP_


#include <map>
#include <stdlib.h>
#include <vector>
#include "mem/ast/node/Call.hpp"
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/New.hpp"
#include "mem/ast/node/Number.hpp"
#include "mem/ast/node/Type.hpp"
#include "mem/ast/node/VarAssign.hpp"
#include "mem/ast/node/VarDecl.hpp"
#include "mem/ast/node/While.hpp"
#include "mem/ast/visitor/TypeChecker.hpp"
#include "mem/ast/util.hpp"
#include "mem/fs/position/Composite.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/Var.hpp"
#include "mem/st/Util.hpp"
#include "mem/Util.hpp"


namespace mem { namespace ast { namespace visitor {


class BlockTypesChecker : public TypeChecker
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * @brief Default constructor.
    */
   BlockTypesChecker();

   //--------------------------------------------------------------------------
   // PUBLIC METHODS
   //--------------------------------------------------------------------------
   public:

   void
   checkCallParameters (st::Func* func_sym, node::Node* params);

   /**
    * @brief Checks whether a function node is compatible with a declared
    * function signature.
    */
   //public: bool isCompatibleFuncSign(st::FunctionSignature* sign_sym,
   //   node::Node* params_node);

   /**
    * @brief Finds a matching function signature and binds it to a call node.
    */
   void
   pickFuncSign(st::Func* func_sym, node::Node* call_node,
      node::Node* params_node);

   /**
    * @brief Visitor entry point.
    */
   virtual bool
   visit (node::Node* node);


   void
   visitAmpersand (st::Symbol* scope, node::Node* node);

   void
   visitArithmeticOp (st::Symbol* scope, node::Node* node);

   void
   visitBinaryExpr (st::Symbol* scope, node::Node* expr_node);

   void
   visitLogicalExpr (st::Symbol* scope, node::Node* expr_node);

   /**
    * @brief Visit a MEM_NODE_BLOCK node.
    */
   void
   visitBlock (st::Symbol* scope, node::Node* block);

   /**
    * Visits a MEM_NODE_CALL.
    */
   void
   visitCall (st::Symbol* scope, node::Call* call_node);

   void
   visitDot (st::Symbol* scope, node::Node* dot_node);

   void
   visitExpr (st::Symbol* scope, node::Node* node);

   void
   visitExprList (st::Symbol* scope, node::Node* node);

   void
   visitFinalId (st::Symbol* scope, node::Text* node);

   void
   visitIf (st::Symbol* scope, node::Node* node);

   void
   visitNew (st::Symbol* scope, node::New* node);

   void
   visitReturn (st::Symbol* scope, node::Node* ret);

   void
   visitVarLiteralNumber (st::Type*, node::Text* literal_nb);

   void
   visitVarAssign (st::Symbol* scope, node::VarAssign* var_assign_node);

   /**
    * Visits a MEM_NODE_VARIABLE_DECLARATION node.
    */
   void
   visitVarDecl (st::Symbol* scope, node::VarDecl* var_decl_node);

   /**
    * Visits a MEM_NODE_WHILE node.
    */
   void
   visitWhile (st::Symbol* scope, node::While* while_node);
};


} } }

#endif
