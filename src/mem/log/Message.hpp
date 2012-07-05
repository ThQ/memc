#ifndef _MEM__LOG__MESSAGE__HPP_
#define _MEM__LOG__MESSAGE__HPP_


#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include "mem/fs/position/Position.hpp"
#include "mem/log/MessageLevel.hpp"


namespace mem { namespace log {


class Message
{
   public: std::string _file_path;
   public: std::string _source_line;

   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------

   // PROPERTY : Description
   public: std::string _description;
   public: void sDescription(const char* desc);
   public: inline void sDescription (std::string desc) { _description.assign(desc); }

   // PROPERTY : Level
   public: MessageLevel _level;
   public: inline MessageLevel gLevel() {return this->_level;}
   public: void sLevel (MessageLevel level);

   // PROPERTY : Message
   public: std::string _message;
   public: void sMessage (const char* message);

   // PROPERTY : Position
   public: fs::position::Position* _position;
   public: fs::position::Position* gPosition() {return _position;}
   public: void sPosition (fs::position::Position* position);


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Message ();

   /**
    * Initializes a Message at a given level.
    */
   Message (MessageLevel level);

   /**
    * Destructor.
    */
   virtual
   ~Message();

   /**
    * Formats the description text.
    */
   void
   formatDescription(const char* format, ...);

   /**
    * Formats the message text.
    *
    * Messages should be as short as possible.
    */
   void
   formatMessage (const char* format, ...);
};


class Warning : public Message
{
   public: Warning () { _level = log::WARNING; }
};


class Error : public Message
{
   public: Error() { _level = log::ERROR; }
};


class FatalError : public Message
{
   public: FatalError() { _level = log::FATAL_ERROR; }
};


} }


#endif
