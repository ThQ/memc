#ifndef _MEM__LOG__XML_FORMATTER__HPP_
#define _MEM__LOG__XML_FORMATTER__HPP_


#include <string>
#include <string.h>
#include "mem/log/Formatter.hpp"
#include "mem/log/Message.hpp"


namespace mem { namespace log {


class XmlFormatter : public Formatter
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   XmlFormatter();


   //--------------------------------------------------------------------------
   // PROTECTED FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   std::string
   _formatLevel (MessageLevel lvl);


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual std::string
   format (Message* msg);

   std::string
   formatStart ();

   std::string
   formatEnd ();
};


} }

#endif
