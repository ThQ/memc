#ifndef _MEM__AST__NODE__NUMBER__HPP_
#define _MEM__AST__NODE__NUMBER__HPP_


#include <string>
#include <sstream>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class Number : public Node
{
   public: char _format;
   public: long _lval;
   public: int _ival;
   public: short _sval;
   public: char _cval;

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
   getChar(){return _cval;}

   int
   getInt ();

   short
   getShort ();

   inline long
   getLong () {assert(_format=='l');return _lval;}

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
   setChar (char c){_format='c';_cval = c;}
};


} } }


#endif
