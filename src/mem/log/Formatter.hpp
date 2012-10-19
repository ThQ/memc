#ifndef _MEM__LOG__FORMATTER__HPP_
#define _MEM__LOG__FORMATTER__HPP_


#include <string>
#include <string.h>
#include "mem/log/Message.hpp"


namespace mem { namespace log {


class Formatter
{
   public:
   std::string _id;

   GETTER(Id, std::string) {return _id;}
   SETTER(Id, std::string) {_id = val;}

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   Formatter ();

   // Destructor.
   virtual
   ~Formatter ();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual std::string
   format (Message* msg);

   virtual std::string
   formatStart () {return "";}

   virtual std::string
   formatEnd () {return "";}
};


} }

#endif
