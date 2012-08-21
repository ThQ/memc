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
 *
 * Primary text :
 *  > The primary text provides the user with a one sentence summary of the
 *  > information or suggested action. This summary should concisely contain
 *  > the essential details of the problem or suggestion. Every [message] has
 *  > primary text [...]. The primary text is punctuated in 'newspaper
 *  > headline' style, that is, it has no terminating period, but it may have a
 *  > terminating question mark.
 *
 * Secondary text :
 *  > Secondary text provides a more in-depth description of the problem and
 *  > suggested action, including possible side effects. Secondary text can
 *  > also provide information that may be helpful in allowing the user to make
 *  > an informed decision. In most situations the user should only need the
 *  > primary text to make a quick decision, but they may read the secondary
 *  > text if they are unsure of the proper course of action, or require extra
 *  > details. Secondary text is optional [...].
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


class Info : public Message
{
   public: Info () { _level = log::INFO; }
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
