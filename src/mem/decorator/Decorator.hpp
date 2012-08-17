#ifndef _MEM__DECORATOR__DECORATOR__HPP_
#define _MEM__DECORATOR__DECORATOR__HPP_


#include <map>
#include <string>
#include "mem/ast/node/Node.hpp"
#include "mem/ss.hpp"

namespace mem { namespace decorator {

class Decorator
{
   public:

   GETTER(Name, std::string) {return _name;}
   SETTER(Name, std::string) {_name = val;}

   public:

   virtual
   ~Decorator () {}

   virtual bool
   decorate (ast::node::Node* node) {return false;}

   protected:

   std::string _name;
};

typedef std::map<std::string, Decorator*> DecoratorMap;

} }

#endif
