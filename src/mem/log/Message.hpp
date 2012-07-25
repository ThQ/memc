#ifndef _MEM__LOG__MESSAGE__HPP_
#define _MEM__LOG__MESSAGE__HPP_


#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include "mem/fs/position/Position.hpp"
#include "mem/log/MessageLevel.hpp"


namespace mem { namespace log {

/**
 * A message to log.
 *
 * Message texts should follow the GNOME Human Interface Guidelines
 * http://developer.gnome.org/hig-book/3.0/windows-alert.html.en#alert-text
 */
class Message
{
   protected:

   std::string _description;
   std::string _file_path;
   MessageLevel _level;
   std::string _message;
   fs::position::Position* _position;
   std::string _source_line;

   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // PROPERTY : Description
   //:public: void sDescription(const char* desc);
   GETTER(SecondaryText, std::string) {return _description;}
   SETTER(SecondaryText, std::string) { _description.assign(val); }

   // PROPERTY : Level
   GETTER(Level, MessageLevel) {return _level;}
   SETTER(Level, MessageLevel) {_level = val;}

   // PROPERTY : Message
   GETTER(PrimaryText, std::string) {return _message;}
   SETTER(PrimaryText, std::string) {_message = val;}

   // PROPERTY : Position
   GETTER(Position, fs::position::Position*) {return _position;}
   SETTER(Position, fs::position::Position*) {_position = val;}


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
