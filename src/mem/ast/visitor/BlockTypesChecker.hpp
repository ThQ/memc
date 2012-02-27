#ifndef _MEM__AST__VISITOR__BLOCK_TYPES_CHECKER__HPP_
#define _MEM__AST__VISITOR__BLOCK_TYPES_CHECKER__HPP_


#include <map>
#include <vector>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/Type.hpp"
#include "mem/ast/node/VarDecl.hpp"
#include "mem/ast/visitor/TypeChecker.hpp"
#include "mem/ast/util.hpp"
#include "mem/fs/position/Composite.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/FunctionSignature.hpp"
#include "mem/st/Var.hpp"
#include "mem/st/Util.hpp"


namespace mem { namespace ast { namespace visitor {


class BlockTypesChecker : public TypeChecker
{
   public: BlockTypesChecker();

   public: bool isCompatibleFuncSign(st::FunctionSignature* sign_sym, node::Node* params_node);
   public: void pickFuncSign(st::Func* func_sym, node::Node* call_node, node::Node* params_node);
   public: virtual bool visit (node::Node* node);
   public: void visitBlock (st::Symbol* scope, node::Node* block);
   public: void visitCall (st::Symbol* scope, node::Node* call_node);
   public: void visitDot (st::Symbol* scope, node::Node* dot_node);
   public: void visitExpr (st::Symbol* scope, node::Node* node);
   public: void visitExprList (st::Symbol* scope, node::Node* node);
   public: void visitFinalId (st::Symbol* scope, node::Text* node);
   public: void visitIf (st::Symbol* scope, node::Node* node);
   public: void visitVarDecl (st::Symbol* scope, node::VarDecl* var_decl_node);
   //public: void visit_variable_declaration_with_value (node::Node* node);
   public: void visitWhile (st::Symbol* scope, node::Node* node);
};


} } }

#endif
