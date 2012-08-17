#ifndef _MEM__ST__VISITOR__VISITOR__HPP_
#define _MEM__ST__VISITOR__VISITOR__HPP_


#include "mem/st/Symbol.hpp"


namespace mem { namespace st { namespace visitor {


class Visitor
{
   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------

   // PROPERTY : Name
   public: std::string _name;
   public: inline void sName(std::string name) {_name = name;}
   public: inline std::string gName() const {return _name;}
   public: inline const char* gNameCstr() const {return _name.c_str();}


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   virtual
   ~Visitor ();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   setup() {};

   virtual void
   tearDown() {};

   virtual inline bool
   visit (st::Symbol* symbol) {return false;}

   virtual void
   visitPreorder (st::Symbol* symbol);
};


} } }


#endif
