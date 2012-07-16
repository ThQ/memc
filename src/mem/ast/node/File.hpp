#ifndef _MEM__AST__NODE__FILE__HPP_
#define _MEM__AST__NODE__FILE__HPP_


#include <string>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class File : public Node
{
   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   std::string _id;
   std::string _include_path;
   std::string _path;


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   File ();


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid(NodeValidator* v);
};


} } }

#endif
