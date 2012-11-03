#ifndef _MEM__FS__POSITION__COMPOSITE__HPP_
#define _MEM__FS__POSITION__COMPOSITE__HPP_


#include <vector>

#include "mem/fs/position/Position.hpp"


namespace mem { namespace fs { namespace position {


class Composite : public Position
{
   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Destructor.
   virtual
   ~Composite ();


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   void
   addChild (Position* child);

   virtual PositionType
   getTypeAt (int column) const;


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   std::vector<Position*> _children;
};


} } }

#endif
