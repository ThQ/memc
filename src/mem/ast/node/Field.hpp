#ifndef _MEM__AST__NODE__FIELD__HPP
#define _MEM__AST__NODE__FIELD__HPP


#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Type.hpp"


namespace mem { namespace ast { namespace node {


class Field : public Text
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Field ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // NameNode
   GETTER(NameNode, node::Node*) {return getChild(0);}

   // ValueNode
   GETTER(ValueNode, node::Node*) {return getChild(1);}


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
