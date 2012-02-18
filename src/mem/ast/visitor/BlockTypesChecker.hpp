#ifndef _MEM__AST__VISITOR__BLOCK_TYPES_CHECKER__HPP_
#define _MEM__AST__VISITOR__BLOCK_TYPES_CHECKER__HPP_


#include <map>
#include <vector>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Function.hpp"
#include "mem/ast/node/Type.hpp"
#include "mem/ast/node/VarDecl.hpp"
#include "mem/ast/visitor/Visitor.hpp"
#include "mem/ast/util.hpp"
#include "mem/fs/position/Composite.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/st/Function.hpp"
#include "mem/st/FunctionSignature.hpp"
#include "mem/st/Var.hpp"
#include "mem/st/Util.hpp"


namespace mem { namespace ast { namespace visitor {


class BlockTypesChecker : public Visitor
{
   public: BlockTypesChecker();

   public: bool is_compatible_function_signature (st::FunctionSignature* sign_sym, node::Node* params_node);
   public: void pick_function_signature (st::Function* func_sym, node::Node* call_node, node::Node* params_node);
   public: virtual bool visit (node::Node* node);
   public: void visit_block (st::Symbol* scope, node::Node* block);
   public: void visit_call (st::Symbol* scope, node::Node* call_node);
   public: void visit_call_parameters (st::Symbol* scope, node::Node* params_node, st::Function* func_sym);
   public: void visit_dot (st::Symbol* scope, node::Node* dot_node);
   public: void visit_exp (st::Symbol* scope, node::Node* node);
   public: void visit_expr_list (st::Symbol* scope, node::Node* node);
   public: void visit_final_id (st::Symbol* scope, node::Text* node);
   public: void visit_if (st::Symbol* scope, node::Node* node);
   public: void visit_var_decl (st::Symbol* scope, node::VarDecl* var_decl_node);
   public: void visit_variable_declaration_with_value (node::Node* node);
   public: void visit_while (st::Symbol* scope, node::Node* node);
};


} } }

#endif
