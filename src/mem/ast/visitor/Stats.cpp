#include "mem/ast/visitor/Stats.hpp"


namespace mem { namespace ast { namespace visitor {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Stats::Stats ()
{
   _name = "ast.Stats";
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
Stats::tearDown ()
{
   std::ostringstream stats;
   std::map<int, KindStats>::iterator it;
   int total_node_count = 0;
   int total_memory_size = 0;

   int colsw[4] = {25, 10, 13 ,14};
   int totalw = 1 + 3 * 3 + 1;
   for (int i = 0; i < 4; ++i) totalw += colsw[i];

   stats << " " << std::setw(totalw) << std::setfill('=') << "" << "\n";
   stats << std::setfill(' ');

   stats << "| " << std::setw(colsw[0]) << "Node";
   stats << " | " << std::setw(colsw[1]) << "Node count";
   stats << " | " << std::setw(colsw[2]) << "Node size (B)";
   stats << " | " << std::setw(colsw[3]) << "Total size (B)";
   stats << " |\n";

   stats << " " << std::setw(totalw) << std::setfill('=') << "" << "\n";
   stats << std::setfill(' ');

   for (it = _kind_usages.begin(); it != _kind_usages.end(); ++it)
   {
      stats << "| " << std::setw(colsw[0]) << node::Node::get_type_name(it->first);
      stats << " | " << std::setw(colsw[1]) << it->second.usages;
      stats << " | " << std::setw(colsw[2]) << it->second.unit_memory_size;
      stats << " | " << std::setw(colsw[3]) << it->second.total_memory_size;
      stats << " |\n";

      total_node_count += it->second.usages;
      total_memory_size += it->second.total_memory_size;
   }

   stats << " " << std::setw(totalw) << std::setfill('-') << "" << "\n";
   stats << std::setfill(' ');

   stats << "| " << std::setw(colsw[0]) << "Total";
   stats << " | " << std::setw(colsw[1]) << total_node_count;
   stats << " | " << std::setw(colsw[2]) << "";
   stats << " | " << std::setw(colsw[3]) << total_memory_size;
   stats << " |\n";

   stats << " " << std::setw(totalw) << std::setfill('-') << "" << "\n";
   stats << std::setfill(' ');

   log::Message* msg = new log::Info();
   msg->setPrimaryText("AST stats");
   msg->setSecondaryText(stats.str());
   log(msg);

   return true;
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
         KindStats s;
         s.usages = 1;
         s.unit_memory_size = node->MemorySize();
         s.total_memory_size = node->MemorySize();
         _kind_usages[node->Kind()] = s;
      }
   }

   return true;
}


} } }
