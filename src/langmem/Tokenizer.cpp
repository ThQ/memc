#include "langmem/Tokenizer.hpp"


namespace langmem {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Tokenizer::Tokenizer ()
{
   _bufferCursor = 0;
   _bufferSize = 0;
   _cur_column = 0;
   _cur_line = 1;
   _fs_file = NULL;
   //_indent_level = 0;
   _eat_space = true;
   _in = NULL;
   _logger = NULL;
}

Tokenizer::~Tokenizer ()
{
   delete _in;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

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

   t.Location().setFile(_fs_file);
   return t;
}


//-----------------------------------------------------------------------------
// PROTECTED FUNCTIONS
//-----------------------------------------------------------------------------

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
      case 'a': return '\a';
      case 'b': return '\b';
      case 'f': return '\f';
      case 'n': return '\n';
      case 'r': return '\r';
      case 't': return '\t';
      case 'v': return '\v';
      case '\'': return 39;
      case '\\': return 92;
      default: c = c_in;
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
      case '{': _pushToken(T_OPEN_BRACE, "{"); break;
      case '}': _pushToken(T_CLOSE_BRACE, "}"); break;
      case '(': _pushToken(T_OP, "("); break;
      case ')': _pushToken(T_CP, ")"); break;
      case '[': _pushToken(T_LBRACKET, "["); break;
      case ']': _pushToken(T_RBRACKET, "]"); break;
      case ',': _pushToken(T_COMMA, ","); break;
      case ';': _pushToken(T_SEMICOLON, ";"); break;
      case '.': _pushToken(T_DOT, "."); break;
      case '@': _pushToken(T_AROBASE, "@"); break;
      case '&': _pushToken(T_AMPERSAND, "&"); break;
      case '%': _pushToken(T_MODULO, "%"); break;
      case ':': _pushToken(T_COLON, ":"); break;

      case '+':
      {
         c2 = _getChar();
         switch (c2)
         {
            case '=':
               _pushToken(T_PLUS_EQ, "*");
               break;
            default:
               _backtrack();
               _pushToken(T_PLUS, "+");
         }
         break;
      }
      case '*':
      {
         c2 = _getChar();
         switch (c2)
         {
            case '=':
               _pushToken(T_STAR_EQ, "*="); break;
               break;
            default:
               _backtrack();
               _pushToken(T_STAR, "*"); break;
         }
         break;
      }
      case '!':
      {
         c2 = _getChar();
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
         c2 = _getChar();
         switch (c2)
         {
            case '/':
               _state = T_SINGLE_LINE_COMMENT;
               break;
            case '=':
               _pushToken(T_SLASH_EQ, "/=");
               break;
            default:
               _backtrack();
               _pushToken(T_DIV, "/");
         }
         break;
      }
      case '-':
      {
         c2 = _getChar();
         switch (c2)
         {
            case '>':
               _pushToken(T_RARR, "->");
               break;
            case '=':
               _pushToken(T_MINUS_EQ, "-=");
               break;
            default:
               _backtrack();
               _pushToken(T_MINUS, "-");
         }
         break;
      }
      case '>':
      {
         c2 = _getChar();
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
         c2 = _getChar();
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
         c2 = _getChar();
         switch (c2)
         {
            case '=':
               _pushToken(T_EQ_EQ, "==");
               break;
            default:
               _backtrack();
               _pushToken(T_EQ, "=");
         }
         break;
      }
      case '\n': // NEWLINE
      {
         _cur_line ++;
         _cur_column = 1;
         _state = T_YACC_UNDEFINED;
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
            _pushToken(T_YACC_ERROR);
            _pushToken(T_YACC_END);
            emit_token = true;
            DEBUG_PRINTF("(%d:%d) Lexer error : bad token start <%c> (%d)\n", _cur_line, _cur_column, c, c);
         }
      }
   }

   return emit_token;
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

      case 'v':
         if (id == "var") kind = T_VAR;
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
   char c = 0;
   _cur_tok = T_YACC_END;

   while (!_isFileConsumed())
   {
      c = _getChar();
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
         /*
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
         */
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
               _tokenBuffer += _escapeChar(_getChar());
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
            if (c == '\n' || c == '\r' || c == ' ')
            {
            }
            else if (c == '{')
            {
               _state = T_OPEN_BRACE;
               _backtrack();
            }
            else if (c == '}')
            {
               _pushToken(T_SEMICOLON, ";");
               _state = T_CLOSE_BRACE;
               _backtrack();
            }
            else
            {
               _pushToken(T_SEMICOLON, ";");
               _state = T_YACC_UNDEFINED;
               _backtrack();
               return ;
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
            DEBUG_PRINTF("Lexer error on <%c> (%d)\n", c, c);
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

/*
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
*/

bool
Tokenizer::isFinished ()
{
   return _isFileConsumed();
}

void
Tokenizer::_pushEndTokens ()
{
   _state = T_YACC_END;
   /*
   for (int i = 0; i < _indent_level; ++i)
   {
      _pushToken(T_DEDENT, "");
   }
   _pushToken(T_NEWLINE, "");
   */
   _pushToken(T_YACC_END, "");
}


}
