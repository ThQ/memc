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

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUTOR
   //--------------------------------------------------------------------------
   public: Number ();

   public: int getInt ();
   public: short getShort ();
   public: std::string getStringFromVal();
   public: unsigned int getUInt();
   public: bool isValid();
   public: void setInt (int i);
   public: void setShort (short s);
};


} } }


#endif
