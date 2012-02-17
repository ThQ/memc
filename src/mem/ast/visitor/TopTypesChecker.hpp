#ifndef _MEM__AST__VISITOR__TOP_TYPES_CHECKER__HPP_
#define _MEM__AST__VISITOR__TOP_TYPES_CHECKER__HPP_


#include <vector>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Field.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Function.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Type.hpp"
#include "mem/ast/visitor/Visitor.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/st/Util.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace ast { namespace visitor {

class TopTypesChecker : public Visitor
{
   public: TopTypesChecker ();

   public: virtual bool visit (node::Node* node);
   public: virtual void visit_field (st::Symbol* scope, node::Field* field);
   public: virtual void visit_function_declaration (st::Symbol* scope, node::Function* func_decl);
   public: virtual void visit_func_param (st::Symbol* scope, node::Node* param_node);
   public: virtual void visit_qualified_name (st::Symbol* scope, node::Text* name_node);
};


} } }

#endif
