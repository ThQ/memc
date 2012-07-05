#ifndef _MEM__AST__NODE__FILE__HPP_
#define _MEM__AST__NODE__FILE__HPP_


#include <string>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class File : public Node
{
   public: std::string _id;
   public: std::string _include_path;
   public: std::string _path;

   //--------------------------------------------------------------------------
   // Constructors / Destrutors
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   File ();

   //--------------------------------------------------------------------------
   // PUBLIC METHODS
   //--------------------------------------------------------------------------
   public:

   virtual bool isValid();
};


} } }

#endif
