#ifndef _MEM__AST__NODE__FIELD__HPP
#define _MEM__AST__NODE__FIELD__HPP


#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Type.hpp"


namespace mem { namespace ast { namespace node {

   class Field : public Text
   {
      //public: const char* _field_name;
      //public: const char* _field_type;

      public: Field ();
      public: std::string get_type_name ();
   };

} } }

#endif
