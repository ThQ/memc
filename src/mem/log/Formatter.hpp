#ifndef _MEM__LOG__FORMATTER__HPP_
#define _MEM__LOG__FORMATTER__HPP_


#include <string>
#include <string.h>
#include "mem/log/Message.hpp"


namespace mem { namespace log {


class Formatter
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Destructor.
    */
   virtual ~Formatter();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual std::string
   format (Message* msg);

   virtual const char*
   format_string (const char* message);
};


} }

#endif
