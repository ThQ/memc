#include "mem/lang/Tokenizer.hpp"


namespace mem { namespace lang {

Tokenizer::Tokenizer ()
{
   _bufferCursor = 0;
   _bufferSize = 0;
   _cur_column = 0;
   _cur_line = 1;
   _fs_file = NULL;
   _indent_level = 0;
   _eat_space = true;
   _logger = NULL;
}

Tokenizer::~Tokenizer ()
{
   delete _in;
}

void
Tokenizer::_backtrack ()
{
   //DEBUG_PRINT("backtrack\n");
   _bufferCursor --;
   _cur_column --;
}

void
Tokenizer::_dumpBuffer ()
{
#if 0
   printf("# BUFFER: [");
   for (int i = 0; i < _bufferSize; ++i)
   {
      switch (_buffer[i])
      {
         case '\n': printf("#"); break;
         case '\t': printf("#"); break;
         default:
            printf("%c", _buffer[i]);
      }
   }
   printf("]");
   for (int i = _bufferSize; i < kBUFFER_SIZE; ++i)
   {
      printf(".");
   }
   printf(" (@%d %d/%d)\n#          ", _bufferCursor, _bufferSize, kBUFFER_SIZE);
   for (int i = 0; i < _bufferCursor; ++i)
   {
      printf("-");
   }
   printf("^\n");
#endif
}

char
Tokenizer::_escapeChar (char c_in) const
{
   char c = '\0';

   switch (c_in)
   {
      case 'a':
         return '\a';
      case 'b':
         return '\b';
      case 'f':
         return '\f';
      case 'n':
         return '\n';
      case 'r':
         return '\r';
      case 't':
         return '\t';
      case 'v':
         return '\v';
      case '\'':
         return 39;
      case '\\':
         return 92;

      default:
         c = c_in;
   }

   return c;
}

void
Tokenizer::_readSome (int n)
{
   _dumpBuffer();

   _in->read(&_buffer[_bufferCursor], n);
   _bufferSize += _in->gcount();

   _dumpBuffer();
}

void
Tokenizer::_shiftBufferLeft (int n)
{
   if (n > 0)
   {
      _dumpBuffer();

      for (int j = 0; j < n; ++j)
      {
         for (int i = 1; i < _bufferSize; ++i)
         {
            _buffer[i-1] = _buffer[i];
            _buffer[i] = _buffer[i + 1];
         }
      }
      _bufferCursor -= n;
      _bufferSize -= n;
      _dumpBuffer();
   }
}

char*
Tokenizer::_getNChars (int n)
{
   _dumpBuffer();

   // Not enough data in the buffer
   if ((_bufferCursor + n) > _bufferSize)
   {
      int slots_missing = (_bufferCursor + n) - kBUFFER_SIZE;
      if (slots_missing > 0)
      {
         _shiftBufferLeft(slots_missing);
      }
      _readSome(n);
   }

   char* ptr = &(_buffer[_bufferCursor]);
   _bufferCursor += n;
   _cur_column += n;

   return ptr;
}

bool
Tokenizer::_processTokenStart (char c)
{
   bool emit_token = false;
   char c2 = 0;

   switch (c)
   {
      case '(': _pushToken(T_OP, "("); break;
      case ')': _pushToken(T_CP, ")"); break;
      case '[': _pushToken(T_LBRACKET, "["); break;
      case ']': _pushToken(T_RBRACKET, "]"); break;
      case ',': _pushToken(T_COMMA, ","); break;
      case ';': _pushToken(T_COLON, ";"); break;
      case '.': _pushToken(T_DOT, "."); break;
      case '@': _pushToken(T_AROBASE, "@"); break;
      case '&': _pushToken(T_AMPERSAND, "&"); break;
      case '*': _pushToken(T_STAR, "*"); break;
      case '%': _pushToken(T_MODULO, "*"); break;
      case '+': _pushToken(T_PLUS, "*"); break;
      case ':': _pushToken(T_SEMICOLON, ":"); break;

      case '!':
      {
         c2 = _get1Char();
         if (c2 == '=')
         {
            _pushToken(T_BANG_EQ, "!=");
         }
         else
         {
            _backtrack();
            _pushToken(T_BANG, "!");
         }
         break;
      }
      case '/':
      {
         c2 = _get1Char();
         if (c2 == '/')
         {
            _state = T_SINGLE_LINE_COMMENT;
         }
         else
         {
            _backtrack();
            _pushToken(T_DIV, "/");
         }
         break;
      }
      case '-':
      {
         c2 = _get1Char();
         if (c2 == '>')
         {
            _pushToken(T_RARR, "->");
         }
         else
         {
            _backtrack();
            _pushToken(T_MINUS, "-");
         }
         break;
      }
      case '>':
      {
         c2 = _get1Char();
         if (c2 == '=')
         {
            _pushToken(T_GT_EQ, ">=");
         }
         else if (c2 == '>')
         {
            _pushToken(T_GT_GT, ">>");
         }
         else
         {
            _backtrack();
            _pushToken(T_GT, ">");
         }
         break;
      }
      case '<':
      {
         c2 = _get1Char();
         if (c2 == '=')
         {
            _pushToken(T_LT_EQ, "<=");
         }
         else if (c2 == '<')
         {
            _pushToken(T_LT_LT, "<<");
         }
         else
         {
            _backtrack();
            _pushToken(T_LT, "<");
         }
         break;
      }
      case '=':
      {
         c2 = _get1Char();
         if (c2 == '=')
         {
            _pushToken(T_EQ_EQ, "==");
         }
         else
         {
            _backtrack();
            _pushToken(T_EQ, "=");
         }
         break;
      }
      case 10: // NEWLINE
      {
         _pushToken(T_NEWLINE);
         _cur_line ++;
         _cur_column = 1;
         _state = T_NEWLINE;
         _cur_tok = T_NEWLINE;
         break;
      }
      case '"':
      {
         _state = T_STRING;
         _cur_tok = T_STRING;
         break;
      }
      default:
      {
         if (Tokenizer::_isIdFirstChar(c))
         {
            _state = T_ID;
            _cur_tok = T_ID;
            _backtrack();
         }
         else if (Tokenizer::_isSpace(c))
         {
            _state = T_SPACE;
            _cur_tok = T_SPACE;
            _backtrack();
         }
         else if (Tokenizer::_isNumeric(c))
         {
            _state = T_LITERAL_NUMBER;
            _cur_tok = T_LITERAL_NUMBER;
            _backtrack();
         }
         else
         {
            _cur_tok = T_YACC_ERROR;
            emit_token = true;
            DEBUG_PRINTF("Lexer error on <%c>\n", c);
         }
      }
   }

   return emit_token;
}

Token
Tokenizer::getNextToken ()
{
   Token t;

   while (_token_queue.size() == 0)
   {
      _readNextToken();
   }

   // There cannot be 2 consecutive T_SPACE, no need to loop here
   if (_eat_space && _token_queue.front().Kind() == T_SPACE)
   {
      _token_queue.pop();
      _readNextToken();
   }
   assert (_token_queue.size() != 0);

   t = _token_queue.front();
   _token_queue.pop();

#if 0
   DEBUG_PRINTF("Emit TOKEN {kind:%d, value:\"%s\"} @ %d:%d..%d:%d\n",
     t.Kind(), t.Value().c_str(),
     t.Location().LineStart(), t.Location().ColumnStart(),
     t.Location().LineEnd(), t.Location().ColumnEnd());
#endif

   t.Location().sFile(_fs_file);
   return t;
}

void
Tokenizer::_getIndentTokenKind (std::string indent)
{
   // First time we see indentation
   if (_indent_unit.size() == 0 && indent.size() != 0)
   {
      _indent_unit = indent;
      _indent_level = 1;
      _pushToken(T_INDENT, indent);
      return;
   }

   // True if indentation is a multiple of the unit
   // For example :
   // * _indent_unit = <tab>
   // * indent = <tab><tab>
   // Then this is OK (true)
   int is_mul_of_unit = (indent.size() %
      (_indent_unit.size() == 0 ? 1 : _indent_unit.size())) == 0;

   if (is_mul_of_unit)
   {
      int indent_level = indent.size() /
         (_indent_unit.size() == 0 ? 1 : _indent_unit.size());

      // Identation
      if (indent_level > _indent_level)
      {
         _indent_level = indent_level;
         _pushToken(T_INDENT, indent);
         return;
      }
      // Dedentation
      else if (indent_level < _indent_level)
      {
         // We may be dedenting more than once at a time :
         // If _indent_unit = <   > (3 spaces -> 1 level)
         // and last identation was <         > (9 spaces -> 3 levels)
         // and now its <   > (3 spaces -> 1 level)
         // -> we are decrementing by 2 levels (3 - 1)
         for (int i = 0; i < _indent_level - indent_level; ++i)
         {
            _pushToken(T_DEDENT, _indent_unit);
         }
         _indent_level = indent_level;
         return;
      }
      else
      {
         // We are simply indenting in the same block (not an indentation, nor
         // a dedentation, we then just skip the token since a T_NEWLINE has
         // been just emited the token before.
         //_pushToken(T_NEWLINE, "");
         _state = T_YACC_UNDEFINED;
         return;
      }
   }
   else
   {
      log::BadIndentation* err = new log::BadIndentation();
      err->sDefaultIndentation(_indent_unit);
      err->sIndentation(indent);
      err->format();
      _logger->log(err);

      _pushToken(T_YACC_ERROR, indent);
   }
}

int
Tokenizer::_getTokenKindFromId (std::string id)
{
   int kind = T_ID;
   switch (id[0])
   {
      case 'b':
         if (id.size() >= 2)
         {
            switch (id[1])
            {
               case 'o':
                  if (id == "bor") kind = T_BIT_OR;
                  break;
               case 'a':
                  if (id == "band") kind = T_BIT_AND;
                  break;
            }
         }
         break;

      case 'c':
         if (id == "class") kind = T_CLASS;
         break;

      case 'e':
         if (id.size() >= 2)
         {
            switch (id[1])
            {
               case 'l':
                  if (id == "else") kind = T_ELSE;
                  break;
               case 'n':
                  if (id == "enum") kind = T_ENUM;
                  break;
            }
         }
         break;

      case 'i':
         if (id == "if") kind = T_IF;
         break;

      case 'f':
         if (id == "for") kind = T_FOR;
         break;

      case 'n':
         if (id == "new") kind = T_NEW;
         break;

      case 'r':
         if (id == "return") kind = T_RETURN;
         break;

      case 'u':
         if (id == "use") kind = T_USE;
         break;

      case 'w':
         if (id == "while") kind = T_WHILE;
         break;

      case 'x':
         if (id == "xor") kind = T_XOR;
   }
   return kind;
}

void
Tokenizer::reset ()
{
   _bufferCursor = 0;
   _bufferSize = 0;
   _state = T_YACC_UNDEFINED;
   _resetLocation();
   _cur_line = 1;
   _cur_column = 0;
}

void
Tokenizer::_readNextToken ()
{
   _tokenBuffer = "";
   char c;
   _cur_tok = T_YACC_END;

   while (!_isFileConsumed())
   {
      c = _get1Char();
      //DEBUG_PRINTF("State[%d] CHAR <%c>(%d)\n", _state, c, c);
      if (c == 0)
      {
         _pushEndTokens();
         return;
      }

      switch (_state)
      {
         case T_YACC_UNDEFINED:
         {
            if (_processTokenStart(c))
            {
               return;
            }
            break;
         }
         case T_ID:
         {
            if (Tokenizer::_isValidIdChar(c))
            {
               _tokenBuffer += c;
            }
            else
            {
               _backtrack();
               _pushToken(_getTokenKindFromId(_tokenBuffer));
               return;
            }
            break;
         }
         case T_INDENT:
         {
            if (Tokenizer::_isSpace(c))
            {
               _tokenBuffer += c;
            }
            else
            {
               _getIndentTokenKind(_tokenBuffer);
               _backtrack();
               if(_state != T_NEWLINE)
               {
                  return;
               }
            }
            break;
         }
         case T_LITERAL_NUMBER:
         {
            if (Tokenizer::_isAlphaNumeric(c))
            {
               _tokenBuffer += c;
            }
            else
            {
               _backtrack();
               _pushToken(T_LITERAL_NUMBER);
               return;
            }
            break;
         }
         case T_SPACE:
         {
            if (Tokenizer::_isSpace(c))
            {
               _tokenBuffer += c;
            }
            else
            {
               _backtrack();
               _pushToken(T_SPACE);
               return;
            }
            break;
         }
         case T_STRING:
         {
            if (c == '\\')
            {
               _tokenBuffer += _escapeChar(_get1Char());
            }
            else if (c != '"')
            {
               _tokenBuffer += c;
            }
            else
            {
               _pushToken(T_STRING);
               return;
            }
            break;
         }
         case T_NEWLINE:
         {
            if (c != '\n')
            {
               _state = T_INDENT;
               _backtrack();
            }
            else
            {
               _cur_line ++;
            }
            break;
         }
         case T_SINGLE_LINE_COMMENT:
         {
            if (c == '\n')
            {
               _state = T_YACC_UNDEFINED;
            }
            break;
         }
         case T_YACC_ERROR:
         {
            return;
         }
         default:
         {
            DEBUG_PRINTF("Lexer error on <%c>\n", c);
            _pushToken(T_YACC_ERROR);
            return ;
         }
      }
   }

   if (_isFileConsumed())
   {
      _pushEndTokens();
   }
}

std::string
Tokenizer::_makeIndentationVisible (std::string indent)
{
   std::stringstream r;
   r << indent.size();
   r << " ";

   if (indent[0] == ' ')
   {
      r << "<space>";
   }
   else if (indent[0] == '\t')
   {
      r << "<tab>";
   }
   else
   {
      r << "<?>";
      assert(false);
   }
   return r.str();
}

bool
Tokenizer::isFinished ()
{
   return _isFileConsumed();
}

void
Tokenizer::_pushEndTokens ()
{
   _state = T_YACC_END;
   for (int i = 0; i < _indent_level; ++i)
   {
      _pushToken(T_DEDENT, "");
   }
   _pushToken(T_NEWLINE, "");
   _pushToken(T_YACC_END, "");
}

} }
