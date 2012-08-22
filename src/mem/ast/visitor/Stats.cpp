#include "mem/ast/visitor/Stats.hpp"


namespace mem { namespace ast { namespace visitor {


Stats::Stats ()
{
   _name = "ast.Stats";
}

bool
Stats::tearDown ()
{
   std::ostringstream stats;
   std::map<int, int>::iterator it;
   int total_node_count = 0;
   stats << "---------------\n";
   for (it = _kind_usages.begin(); it != _kind_usages.end(); ++it)
   {
      stats << node::Node::get_type_name(it->first) << ": ";
      stats << it->second << "\n";
      total_node_count += it->second;
   }

   stats << "---------------\n";
   stats << "Total: " << total_node_count << "\n";

   log::Message* msg = new log::Info();
   msg->setPrimaryText("AST stats");
   msg->setSecondaryText(stats.str());
   log(msg);
}

bool
Stats::visit (node::Node* node)
{
   assert (node != NULL);

   if (node != NULL)
   {
      _incrementNodeKindUsage(node->Kind());
   }

   return true;
}

void
Stats::_incrementNodeKindUsage (int kind)
{
   if (_kind_usages.find(kind) != _kind_usages.end())
   {
      _kind_usages[kind] ++;
   }
   else
   {
      _kind_usages[kind] = 1;
   }
}
} } }
