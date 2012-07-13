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
   public: Number ();

   public: inline char getChar(){return _cval;}

   public: int getInt ();
   public: short getShort ();
   public: inline long getLong () {assert(_format=='l');return _lval;}

   public: std::string getStringFromVal();
   public: unsigned int getUInt();
   public: void isValid(NodeValidator* vld);
   public: void setInt (int i);
   public: void setShort (short s);
   public: inline void setChar (char c){_format='c';_cval = c;}
};


} } }


#endif
