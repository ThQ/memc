#ifndef _MEM__AST__NODE__FIELD__HPP
#define _MEM__AST__NODE__FIELD__HPP


#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Type.hpp"
#include "mem/ast/node/VarDecl.hpp"


namespace mem { namespace ast { namespace node {


class Field : public VarDecl
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Field ();

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}

   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   std::string
   get_type_name ();

   virtual void
   isValid(NodeValidator* v);
};


} } }

#endif
