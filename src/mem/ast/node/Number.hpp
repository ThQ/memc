#ifndef _MEM__AST__NODE__NUMBER__HPP_
#define _MEM__AST__NODE__NUMBER__HPP_


#include <string>
#include <sstream>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class Number : public Node
{
   public: char _format;
   public: long _val;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Number ();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   char
   getChar(){return (char)_val;}

   int
   getInt ();

   short
   getShort ();

   inline long
   getLong () {return _val;}

   std::string
   getStringFromVal();

   unsigned int
   getUInt();

   void
   isValid(NodeValidator* vld);

   void
   setInt (int i);

   void
   setShort (short s);

   inline void
   setChar (char c){_format='c';_val = c;}
};


} } }


#endif
