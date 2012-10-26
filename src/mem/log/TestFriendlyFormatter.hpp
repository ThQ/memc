#ifndef _MEM__LOG__TEST_FRIENDLY_FORMATTER__HPP_
#define _MEM__LOG__TEST_FRIENDLY_FORMATTER__HPP_


#include <sstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "mem/fs/position/Position.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/log/Formatter.hpp"


namespace mem { namespace log {


class TestFriendlyFormatter : public Formatter
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   TestFriendlyFormatter ();


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
   _formatLevelId (std::ostream& str, MessageLevel level);
};


} }

#endif
