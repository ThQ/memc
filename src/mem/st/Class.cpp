#include "mem/st/Class.hpp"


namespace mem { namespace st {


Class::Class ()
{
   _kind = CLASS;
}

Class::~Class ()
{
}


bool
Class::isDependingOn (Class* other_cls)
{
   assert (other_cls != NULL);
   assert (other_cls->isClassSymbol());

   st::Var* cls_field = NULL;

   if (this == other_cls)
   {
      return true;
   }
   else
   {
      // TODO This is an ugly one here...
      SymbolCollectionIterator i;
      for (i = _children.begin(); i != _children.end(); i++)
      {
         if ((*i).second->isVarSymbol())
         {
            cls_field = static_cast<st::Var*>(i->second);
            if (cls_field->gType()->isClassSymbol())
            {
               if (cls_field->gType() == other_cls)
               {
                  return true;
               }
               else if (static_cast<st::Class*>(
                  cls_field->gType())->isDependingOn(other_cls))
               {
                  return true;
               }
            }
         }
      }
   }

   return false;
}


} }
