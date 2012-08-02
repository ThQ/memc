#ifndef _MEM__AST__VISITOR__TOP_TYPES_CHECKER__HPP_
#define _MEM__AST__VISITOR__TOP_TYPES_CHECKER__HPP_


#include <vector>
#include "mem/ast/node/Array.hpp"
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Dot.hpp"
#include "mem/ast/node/Field.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/Ptr.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Type.hpp"
#include "mem/ast/visitor/BlockTypesChecker.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/st/Field.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/Util.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace ast { namespace visitor {


/**
 * Checks correctness of types in high level declarations : functions
 * and fields.
 */
class TopTypesChecker : public BlockTypesChecker
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   TopTypesChecker ();


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   /**
    * Visitor entry point.
    */
   virtual bool
   visit (node::Node* node);

#if 0
   void
   visitArray (st::Symbol* scope, node::Array* n);

   /**
    * Visit a DOT expression (MEM_NODE_DOT).
    */
   void
   visitDot (st::Symbol* scope, node::Node* dot);

#endif
   /**
    * Visits a class field declaration (MEM_NODE_FIELD).
    *
    * Checks whether the type symbol is really one and binds it to the AST.
    *
    * @param scope A class symbol, the field's parent.
    * @param field The field node to check.
    */
   virtual void
   visitField (st::Symbol* scope, node::Field* field);

   /**
    * Visits a function declaration (MEM_NODE_FUNCTION_DECLARATION)
    */
   virtual void
   visitFuncDecl (st::Symbol* scope, node::Func* func_decl);

   /**
    * Visits parameters in function declaration.
    */
   virtual void
   visitFuncParams (st::Symbol* scope, node::Node* params_node, st::Func* func);

   /**
    * Visits return type in function declaration.
    */
   virtual void
   visitFuncReturnType (node::Func* func_node, st::Func* func_sym);

#if 0
   virtual void
   visitQualifiedName (st::Symbol* scope, node::Node* name_node);

   void
   visitTypeName (st::Symbol* scope, node::Node* node);
#endif
};


} } }

#endif
