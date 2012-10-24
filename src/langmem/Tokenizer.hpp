#ifndef _MEM__LANG__TOKENIZER__HPP_
#define _MEM__LANG__TOKENIZER__HPP_


#include <fstream>
#include <sstream>
#include <queue>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include "langmem/Token.hpp"
#include "langmem/TokenKind.hpp"
#include "mem/fs/File.hpp"
#include "mem/log/errors.hpp"
#include "mem/log/Logger.hpp"
#include "mem/ss.hpp"


namespace langmem {


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
   int _cur_line;
   int _cur_column;
   mem::fs::File* _fs_file;
   std::string _indent_unit;
   //int _indent_level;
   bool _eat_space;
   std::istream* _in;
   mem::fs::position::Range _location;
   mem::log::Logger* _logger;
   int _state;
   int _cur_tok;
   std::queue<Token> _token_queue;


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   SETTER(EatSpace, bool) {_eat_space = val;}

   SETTER(Logger, mem::log::Logger*) { _logger = val;}

   SETTER(FsFile, mem::fs::File*) {_fs_file = val;}


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   Tokenizer ();

   // Destructor
   ~Tokenizer ();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   Token
   getNextToken ();

   bool
   isFinished ();

   void
   reset ();

   inline void
   setInputFile (std::string fpath)
   {
      delete _in;
      _in = new std::ifstream(fpath.c_str(), std::ifstream::in);
   }

   inline void
   setInputString (std::string str)
   {
      delete _in;
      _in = new std::istringstream (str, std::istringstream::in);
   }

   inline void
   setInputStringStream (std::istringstream* istr)
   {
      delete _in;
      _in = istr;
   }


   //--------------------------------------------------------------------------
   // PROTECTED FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   inline void
   _backtrack ();

   void
   _dumpBuffer ();

   inline void
   _endToken ()
   {
      _location.setLineEnd(_cur_line);
      _location.setColumnEnd(_cur_column);
   }
   char
   _escapeChar(char c) const ;

   //inline void
   //_getIndentTokenKind (std::string indent);

   inline int
   _getTokenKindFromId (std::string id);

   inline void
   _readNextToken ();

   static inline bool
   _isAlpha (char c) {return (c >= 97 && c <= 122) || (c >= 65 && c <= 90);}

   static inline bool
   _isAlphaNumeric (char c) {return _isAlpha(c) || _isNumeric(c);}

   inline bool
   _isIdFirstChar (char c) {return _isAlpha(c) || c == '_';}

   inline bool
   _isFileConsumed () {return _in->eof() && (_bufferCursor == _bufferSize);}

   static inline bool
   _isNumeric (char c) {return (c >= 48 && c <= 57);}

   static inline bool
   _isSpace (char c) {return (c == 9 || c== 32);}

   static inline bool
   _isValidIdChar (char c) {return _isAlphaNumeric(c) || c == '_';}

   //std::string
   //_makeIndentationVisible (std::string indent);

   inline bool
   _processTokenStart (char c);

   void
   _shiftBufferLeft (int n);

   void
   _readSome (int n);

   inline char
   _getChar () {return *(_getNChars(1));}

   char*
   _getNChars (int n);

   void
   _pushEndTokens ();

   inline void
   _pushToken (int kind)
   {
      _endToken();

      Token t(kind, _tokenBuffer);
      t.setLocation(_location);
      _token_queue.push(t);
      _state = T_YACC_UNDEFINED;
      _startToken();
   }

   inline void
   _pushToken (int kind, std::string val)
   {
      _endToken();

      Token t(kind, val);
      t.setLocation(_location);
      _token_queue.push(t);
      _state = T_YACC_UNDEFINED;
      _startToken();
   }

   inline void
   _resetLocation ()
   {
      _location.setLineStart(1);
      _location.setLineEnd(1);
      _location.setColumnEnd(1);
      _location.setColumnStart(1);
   }

   inline void
   _startToken ()
   {
      _location.setLineStart(_cur_line);
      _location.setColumnStart(_cur_column);
      _location.setLineEnd(_cur_line);
      _location.setColumnEnd(_cur_column);
   }
};


}

#endif
