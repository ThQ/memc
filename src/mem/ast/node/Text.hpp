#ifndef _MEM__AST__NODE__TEXT_NODE__HPP_
#define _MEM__AST__NODE__TEXT_NODE__HPP_


#include <string.h>
#include "mem/ast/node/Node.hpp"


namespace mem { namespace ast { namespace node {

   class Text: public Node
   {
      public: std::string _value;

      public: Text ();
      public: Text (unsigned int type);
      public: void set_value (const char* value);
      public: void set_value (const char* value, size_t len);
      public: void set_value (std::string value);
   };

} } }

#endif
