#ifndef _MEM__TOOL__COMMAND_CHAIN__HPP_
#define _MEM__TOOL__COMMAND_CHAIN__HPP_


#include "mem/tool/Toolbox.hpp"
#include "mem/ss.hpp"


namespace mem { namespace tool {


class CommandChain
{
   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   int _last_status;
   mem::Toolbox _tb;


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(Status, int) {return _last_status;}


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------

   public:
   CommandChain (mem::Toolbox& tb);


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
