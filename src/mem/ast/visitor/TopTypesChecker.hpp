#ifndef _MEM__AST__VISITOR__TOP_TYPES_CHECKER__HPP_
#define _MEM__AST__VISITOR__TOP_TYPES_CHECKER__HPP_


#include <vector>
#include "mem/ast/node/ArrayType.hpp"
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Dot.hpp"
#include "mem/ast/node/EnumType.hpp"
#include "mem/ast/node/Field.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/PointerType.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Type.hpp"
#include "mem/ast/visitor/BlockTypesChecker.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/st/EnumType.hpp"
#include "mem/st/Field.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/FunctionType.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace ast { namespace visitor {


// Checks correctness of types in high level declarations : functions
// and fields.
class TopTypesChecker : public BlockTypesChecker
{
   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   TopTypesChecker ();


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   // Visitor entry point.
   virtual bool
   visit (node::Node* node);

   void
   visitClass (st::Symbol* scope, node::Class* clss);

   void
   visitEnumType (st::Symbol* scope, node::EnumType* node);

   void
   visitEnumMembers (st::EnumType* symEnum, node::NodeList* nodeMembers);

   // Visit a class field declaration (MEM_NODE_FIELD).
   //
   // Checks whether the type symbol is really one and binds it to the AST.
   //
   // param(scope): A class symbol, the field's parent.
   // param(field): The field node to check.
   void
   visitField (st::Symbol* scope, node::Field* field);

   // Visit a function declaration (MEM_NODE_FUNCTION_DECLARATION)
   void
   visitFuncDecl (st::Symbol* scope, node::Func* func_decl);

   // Visit parameters in function declaration.
   void
   visitFuncParams (st::Symbol* scope, node::Node* params_node, st::Func* func);

   // Visit return type in function declaration.
   void
   visitFuncReturnType (node::Func* func_node, st::Func* func_sym);
};


} } }

#endif
