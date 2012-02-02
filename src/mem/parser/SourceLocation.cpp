#include "mem/parser/SourceLocation.hpp"

namespace mem { namespace parser {


SourceLocation::SourceLocation (int line, int column)
{
   this->_line = line;
   this->_column = column;
}


} }
