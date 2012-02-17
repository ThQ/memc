#ifndef _MEM__AST__VISITOR__FIND_CLASSES__HPP_
#define _MEM__AST__VISITOR__FIND_CLASSES__HPP_


#include <vector>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Type.hpp"
#include "mem/ast/visitor/Visitor.hpp"
#include "mem/st/Util.hpp"


namespace mem { namespace ast { namespace visitor {


class FindClasses : public Visitor
{
   public: FindClasses ();
   public: virtual bool visit (node::Node* node);
};


} } }

#endif
