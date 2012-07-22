#ifndef _MEM__LANG__TOKENIZER__HPP_
#define _MEM__LANG__TOKENIZER__HPP_


#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include "mem/lang/Token.hpp"
#include "mem/lang/TokenKind.hpp"
#include "mem/log/Logger.hpp"
#include "mem/ss.hpp"


namespace mem { namespace lang {


class Tokenizer
{
   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   static const int kBUFFER_SIZE=10;
   std::string _tokenBuffer;
   char _buffer[kBUFFER_SIZE];
   int _bufferCursor;
   int _bufferSize;
   std::string _indent_unit;
   int _indent_level;
   bool _eat_space;
   std::istream* _in;
   log::Logger* _logger;
   int _state;
   int _cur_tok;


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   SETTER(Logger, log::Logger*) { _logger = val;}
   SETTER(EatSpace, bool) {_eat_space = val;}


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Tokenizer ();


   //--------------------------------------------------------------------------
   // PROTECTED FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   inline void
   _backtrack ();

   void
   _dumpBuffer ();

   inline int
   _getIndentTokenKind (std::string indent);

   inline int
   _getTokenKindFromId (std::string id);

   inline Token
   _getNextToken ();

   static inline bool
   _isAlpha (char c) {return (c >= 97 && c <= 122) || (c >= 65 && c <= 90);}

   static inline bool
   _isAlphaNumeric (char c) {return _isAlpha(c) || _isNumeric(c);}

   inline bool
   _isFileConsumed () {return _in->eof() && (_bufferCursor == _bufferSize);}

   static inline bool
   _isNumeric (char c) {return (c >= 48 && c <= 57);}

   static inline bool
   _isSpace (char c) {return (c == 9 || c== 32);}

   std::string
   _makeIndentationVisible (std::string indent);

   inline bool
   _processTokenStart (char c);

   void
   _shiftBufferLeft (int n);

   void
   _readSome (int n);

   inline char
   _get1Char () {return *(_getNChars(1));}

   char*
   _getNChars (int n);


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   Token
   getNextToken ();

   void
   reset ();

   inline void
   setInputFile (std::string fpath) { _in = new std::ifstream(fpath.c_str(), std::ifstream::in); };
};


} }

#endif
