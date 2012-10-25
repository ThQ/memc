#ifndef _MEM__LOG__CONSOLE_FORMATTER__HPP_
#define _MEM__LOG__CONSOLE_FORMATTER__HPP_


#include <sstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "mem/fs/position/Position.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/log/Formatter.hpp"


namespace mem { namespace log {


class ConsoleFormatter : public Formatter
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   ConsoleFormatter ();

   // Destructor
   virtual
   ~ConsoleFormatter ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   SETTER(ColorsEnabled, bool) { _colors_enabled = val;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual std::string
   format (Message* msg);


   //--------------------------------------------------------------------------
   // PROTECTED FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   void
   _formatDescription (std::ostream& str, Message* msg);

   void
   _formatLevelId (std::ostream& str, MessageLevel level);

   void
   _formatMessage (std::ostream& str, Message* msg);

   void
   _formatPosition (std::ostream& str, fs::position::Position* pos);

   void
   _formatSourceLines (std::ostream& str, fs::position::Range* pos);

   std::string
   _getLinuxColor (std::string color);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   bool _colors_enabled;
   int _num_context_lines;
};


} }

#endif
