#ifndef _MEM__AST__NODE__TEXT_NODE__HPP_
#define _MEM__AST__NODE__TEXT_NODE__HPP_


#include <string.h>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {


class Text: public Node
{
   public: std::string _value;

   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------

   // PROPERTY : Value
   public: std::string gValue() const { return this->_value;}
   public: const char* gValueCstr() {return this->_value.c_str();}
   public: void sValue (const char* value);
   public: void sValue (const char* value, size_t len);
   public: void sValue (std::string value);

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Text ();

   virtual
   GETTER(MemorySize, int) {return sizeof(Node);}

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Node*
   copy () const;
};


} } }


#endif
