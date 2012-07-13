#ifndef _MEM__AST__NODE__NODE_VALIDATOR__HPP_
#define _MEM__AST__NODE__NODE_VALIDATOR__HPP_


#include <string>
#include <vector>


namespace mem { namespace ast { namespace node {


class NodeValidator
{
   public: bool _is_valid;
   public: std::vector<std::string> _messages;

   public: NodeValidator ();
   public: void ensure (bool cond);
   public: void ensure (bool cond, std::string msg);
   public: void setup ();
};

} } }

#endif
