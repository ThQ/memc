#include "mem/lang/Tokenizer.hpp"


namespace mem { namespace lang {

Tokenizer::Tokenizer ()
{
   _bufferCursor = 0;
   _bufferSize = 0;
   _indent_level = 0;
   _eat_space = true;
   _logger = NULL;
}

void
Tokenizer::_backtrack ()
{
   _bufferCursor --;
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

void
Tokenizer::_readSome (int n)
{
   //printf("<readSome(%d)>\n", n);
   _dumpBuffer();

   _in->read(&_buffer[_bufferCursor], n);
   _bufferSize += _in->gcount();

   _dumpBuffer();
   //printf("</readSome>\n");
}

void
Tokenizer::_shiftBufferLeft (int n)
{
   //printf("<shiftBufferLeft(%d)>\n", n);
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
   //printf("</shiftBufferLeft>\n");
}

char*
Tokenizer::_getNChars (int n)
{
   _dumpBuffer();
   //printf("<getNChars(%d)>\n", n);
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
   else
   {
   }

   char* ptr = &(_buffer[_bufferCursor]);
   _bufferCursor += n;
   //printf("</getNChars>\n");
   return ptr;
}

bool
Tokenizer::_processTokenStart (char c)
{
   bool emit_token = false;
   char c2 = 0;

   //printf("_processTokenStart\n");
   switch (c)
   {
      case '(':
      {
        _cur_tok = T_OP;
        _state = T_YACC_UNDEFINED;
        _tokenBuffer = c;
        emit_token = true;
        break;
      }
      case ')':
      {
         _cur_tok = T_CP;
         _state = T_YACC_UNDEFINED;
         _tokenBuffer = c;
         emit_token = true;
         break;
      }
      case '[':
      {
         _cur_tok = T_LBRACKET;
         _state = T_YACC_UNDEFINED;
         _tokenBuffer = c;
         emit_token = true;
         break;
      }
      case ']':
      {
         _cur_tok = T_RBRACKET;
         _state = T_YACC_UNDEFINED;
         _tokenBuffer = c;
         emit_token = true;
         break;
      }
      case ':':
      {
         _cur_tok = T_SEMICOLON;
         _state = T_YACC_UNDEFINED;
         _tokenBuffer = c;
         emit_token = true;
         break;
      }
      case ',':
      {
         _cur_tok = T_COMMA;
         _state = T_YACC_UNDEFINED;
         _tokenBuffer = c;
         emit_token = true;
         break;
      }
      case '*':
      {
         _cur_tok = T_MUL;
         _state = T_YACC_UNDEFINED;
         _tokenBuffer = c;
         emit_token = true;
         break;
      }
      case '+':
      {
         _cur_tok = T_PLUS;
         _state = T_YACC_UNDEFINED;
         _tokenBuffer = c;
         emit_token = true;
         break;
      }
      case '-':
      {
         c2 = _get1Char();
         if (c2 == '>')
         {
            _cur_tok = T_RARR;
            _state = T_YACC_UNDEFINED;
            _tokenBuffer = c;
            _tokenBuffer += c2;
            emit_token = true;
         }
         else
         {
            _cur_tok = T_MINUS;
            _state = T_YACC_UNDEFINED;
            _tokenBuffer = c;
            _backtrack();
            emit_token = true;
         }
         break;
      }
      case '=':
      {
         c2 = _get1Char();
         if (c2 == '=')
         {
            _cur_tok = T_EQ_EQ;
            _tokenBuffer = c;
            _tokenBuffer += c2;
            _state = T_YACC_UNDEFINED;
            emit_token = true;
         }
         else
         {
            _cur_tok = T_EQ;
            _tokenBuffer = c;
            _backtrack();
            _state = T_YACC_UNDEFINED;
            emit_token = true;
         }
         break;
      }
      case 10: // NL
      {
         // We emit the token now but next time we know we're looking for
         // indent/dedent
         _state = T_INDENT;
         _cur_tok = T_NEWLINE;
         _tokenBuffer = "\n";
         emit_token = true;
         //printf("NEWLINE <%c>\n", c);
         break;
      }
      default:
      {
         if (Tokenizer::_isAlpha(c))
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
         }
      }
   }

   return emit_token;
}

Token
Tokenizer::getNextToken ()
{
   //DEBUG_PRINTF("========= getNextToken ==========\n", "");
   Token t = _getNextToken();

   // There cannot be 2 consecutive T_SPACE, no need to loop here
   if (_eat_space && t.Kind() == T_SPACE)
   {
      t = _getNextToken();
   }

   DEBUG_PRINTF("=> TOKEN[%d] = <%s>\n", t.Kind(), t.Value().c_str());
   return t;
}

int
Tokenizer::_getIndentTokenKind (std::string indent)
{
   // First time we see indentation
   if (_indent_unit.size() == 0 && indent.size() != 0)
   {
      //printf("First time indent\n");
      _indent_unit = indent;
      _indent_level = 1;
      return T_INDENT;
   }

   // True if indentation is a multiple of the unit
   // For example :
   // * _indent_unit = <   > (3 spaces)
   // * indent = <      > (6 spaces)
   // Then this is OK (true)
   int is_mul_of_unit = (indent.size() % _indent_unit.size()) == 0;

   if (is_mul_of_unit)
   {
      int indent_level = indent.size() / _indent_unit.size();
      // Ident
      if (indent_level > _indent_level)
      {
         _indent_level = indent_level;
         return T_INDENT;
      }
      else if (indent_level < _indent_level)
      {
         _indent_level = indent_level;
         return T_DEDENT;
      }
      else
      {
         // We are simply indenting in the same block (not an indentation, nor
         // a dedentation, we then just skip the token since a T_NEWLINE has
         // been just emited the token before.
         return T_YACC_UNDEFINED;
      }
   }
   else
   {
      log::Message* err = new log::FatalError();
      err->sMessage("Bad indentation");
      err->formatDescription("Default indentation is %s, but got %s",
         _makeIndentationVisible(_indent_unit).c_str(),
         _makeIndentationVisible(indent).c_str());
      _logger->log(err);

      return T_YACC_ERROR;
   }
}

int
Tokenizer::_getTokenKindFromId (std::string id)
{
   int kind = T_ID;
   switch (id[0])
   {
      case 'e':
         if (id == "else") kind = T_ELSE;
         break;

      case 'i':
         if (id == "if") kind = T_IF;
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
   }
   return kind;
}

void
Tokenizer::reset ()
{
   _state = T_YACC_UNDEFINED;
}

Token
Tokenizer::_getNextToken ()
{
   Token t;

   //printf("EOF? %d | cursor=size? %d\n", _in->eof(), _bufferCursor==_bufferSize);
   if (_isFileConsumed())
   {
      //printf("Consumed, dont get next char\n");
      t.setKind(T_YACC_END);
      return t;
   }

   _tokenBuffer = "";
   char c;
   _cur_tok = T_YACC_END;

   while (!_isFileConsumed())
   {
      c = _get1Char();
      //DEBUG_PRINTF("CHAR <%c>(%d)\n", c, c);
      if (c == 0)
      {
         _state = T_YACC_END;
         _cur_tok = T_YACC_END;
         goto ret;
      }

      switch (_state)
      {
         case T_YACC_UNDEFINED:
         {
            if (_processTokenStart(c))
            {
               goto ret;
            }
            break;
         }
         case T_ID:
         {
            //printf("ID\n");
            if (Tokenizer::_isAlphaNumeric(c))
            {
               _tokenBuffer += c;
            }
            else
            {
               _cur_tok = _getTokenKindFromId(_tokenBuffer);
               _backtrack();
               _state = T_YACC_UNDEFINED;
               goto ret;
            }
            break;
         }
         case T_INDENT:
         {
            //printf("T_INDENT\n");
            if (Tokenizer::_isSpace(c))
            {
               _tokenBuffer += c;
            }
            else
            {
               _cur_tok = _getIndentTokenKind(_tokenBuffer);
               _backtrack();
               _state = T_YACC_UNDEFINED;
               if (_cur_tok != T_YACC_UNDEFINED)
               {
                  goto ret;
               }
               else
               {
                  _tokenBuffer = "";
               }
            }
            break;
         }
         case T_LITERAL_NUMBER:
         {
            //printf("NUMBER\n");
            if (Tokenizer::_isAlphaNumeric(c))
            {
               _tokenBuffer += c;
            }
            else
            {
               _backtrack();
               _state = T_YACC_UNDEFINED;
               goto ret;
            }
            break;
         }
         case T_SPACE:
         {
            //printf("SPACE\n");
            if (Tokenizer::_isSpace(c))
            {
               _tokenBuffer += c;
            }
            else
            {
               _backtrack();
               _state = T_YACC_UNDEFINED;
               goto ret;
            }
            break;
         }
         case T_YACC_ERROR:
         {
            goto ret;
         }
         default:
         {
            _cur_tok = T_YACC_ERROR;
            _tokenBuffer += c;
            goto ret;
         }
      }
   }

   ret:
      t.setKind(_cur_tok);
      t.setValue(_tokenBuffer);
      return t;
}

std::string
Tokenizer::_makeIndentationVisible (std::string indent)
{
   std::string r;
   for (size_t i=0; i < indent.size(); ++i)
   {
      if (indent[i] == ' ')
      {
         r += "<space>";
      }
      else if (indent[i] == '\t')
      {
         r += "<tab>";
      }
      else
      {
         assert(false);
         r += "<?>";
      }
   }
   return r;
}

} }
