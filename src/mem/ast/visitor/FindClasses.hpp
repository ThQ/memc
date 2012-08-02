#ifndef _MEM__AST__VISITOR__FIND_CLASSES__HPP_
#define _MEM__AST__VISITOR__FIND_CLASSES__HPP_


#include <vector>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Type.hpp"
#include "mem/ast/util.hpp"
#include "mem/ast/visitor/Visitor.hpp"
#include "mem/st/util.hpp"


namespace mem { namespace ast { namespace visitor {


/**
 * Visits the AST in order to find MEM_NODE_CLASS nodes.
 */
class FindClasses : public Visitor
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   FindClasses ();


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual bool
   visit (node::Node* node);

   void
   visitClassDecl (node::Class* cls_node);
};


} } }

#endif
