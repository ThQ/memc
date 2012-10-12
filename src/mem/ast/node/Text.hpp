#ifndef _MEM__AST__NODE__TEXT_NODE__HPP_
#define _MEM__AST__NODE__TEXT_NODE__HPP_


#include <string.h>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class Text: public Node
{
   public:
   static const int kTYPE = Kind::TEXT;

   Text ();
/*
   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // Value
   GETTER(Value, std::string) {return _value;}
   SETTER(Value, std::string) {_value = val;}

   // ValueCstr
   GETTER(ValueCstr, const char*) {return _value.c_str();}


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.

   virtual
   GETTER (MemorySize, int) {return sizeof(Text);}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   copy () const;


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   std::string _value;
   */
};


} } }


#endif
