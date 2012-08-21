#ifndef _MEMC__TOOL__COMMAND_CHAIN__HPP_
#define _MEMC__TOOL__COMMAND_CHAIN__HPP_


#include "memc/tool/Toolbox.hpp"
#include "mem/ss.hpp"


namespace memc { namespace tool {


class CommandChain
{
   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   int _last_status;
   memc::Toolbox _tb;


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(Status, int) {return _last_status;}


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------

   public:
   CommandChain (memc::Toolbox& tb);


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   CommandChain*
   then (Toolbox::ToolName alias, std::string args);

   CommandChain*
   run (Toolbox::ToolName alias, std::string args);
};


} }

#endif
