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
   std::map<int, KindStats>::iterator it;
   int total_node_count = 0;
   int total_memory_size = 0;
   stats << "---------------\n";
   for (it = _kind_usages.begin(); it != _kind_usages.end(); ++it)
   {
      stats << node::Node::get_type_name(it->first) << ": ";
      stats << it->second.usages;
      stats << " * " << it->second.unit_memory_size << "B";
      stats << " = " << it->second.total_memory_size << "B\n";
      total_node_count += it->second.usages;
      total_memory_size += it->second.total_memory_size;
   }

   stats << "---------------\n";
   stats << "Total: " << total_node_count;
   stats << " | " << total_memory_size << "B\n";

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
      if (_kind_usages.find(node->Kind()) != _kind_usages.end())
      {
         _kind_usages[node->Kind()].usages = _kind_usages[node->Kind()].usages + 1;
         _kind_usages[node->Kind()].total_memory_size = _kind_usages[node->Kind()].total_memory_size + node->MemorySize();
      }
      else
      {
         _kind_usages[node->Kind()] = {1,node->MemorySize(), node->MemorySize()};
      }
   }

   return true;
}


} } }
