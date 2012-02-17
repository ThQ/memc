#ifndef _MEM__ST__DUMPER__TEXT_DUMPER__HPP_
#define _MEM__ST__DUMPER__TEXT_DUMPER__HPP_


#include "mem/st/dumper/IDumper.hpp"


namespace mem { namespace st { namespace dumper {


/**
 * A class for dumping a symbol as plain text.
 */
class TextDumper : public IDumper
{
   public: std::string dump (st::Symbol* symb);
   public: std::string dump_children (st::Symbol* sym, int level);
   public: std::string dump_depth (int level);
   public: std::string dump_symbol (st::Symbol* sym, int level);
   public: void dump_to (st::Symbol* symb, std::ostream& to);
};


} } }

#endif
