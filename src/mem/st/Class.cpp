#include "mem/st/Class.hpp"


namespace mem { namespace st {


Class::Class ()
{
   _cur_field_index = 0;
   _kind = CLASS;
}

Class::~Class ()
{
}

bool
Class::addChild (Symbol* s)
{
   printf("Class.addChild(%s) / FI=%d\n", s->gNameCstr(), _cur_field_index);
   if (s->_kind == FIELD)
   {
      static_cast<Field*>(s)->_field_index = _cur_field_index;
      _cur_field_index++;
   }
   return Type::addChild(s);
}

std::vector<st::Field*>
Class::getOrderedFields ()
{
   std::vector<st::Field*> v;
   if (hasFields())
   {
      v.resize(_cur_field_index, NULL);

      Field* field = NULL;
      SymbolCollectionIterator i;
      for (i = _children.begin(); i != _children.end(); i++)
      {
         if (i->second->_kind == FIELD)
         {
            field = static_cast<Field*>(i->second);
            printf("SetField @%d\n", field->_field_index);
            v[field->_field_index] = field;
         }
      }

      printf("%d fields in %s\n", _cur_field_index, gNameCstr());
      for (size_t i = 0; i < v.size(); ++i)
      {
         printf("Check field @%d\n", i);
         assert(v[i] != NULL);
      }
   }
   return v;
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
