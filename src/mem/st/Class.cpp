#include "mem/st/Class.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Class::Class ()
{
   _byte_size = 0;
   _cur_field_index = 0;
   _default_ctor = NULL;
   _kind = Class::kTYPE;
}

Class::~Class ()
{
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
Class::addChild (Symbol* s)
{
   if (s->Kind() == st::MetaKind::FIELD)
   {
      st::Field* field = st::cast<st::Field>(s);
      assert(field->Type() != NULL);
      field->setFieldIndex(_cur_field_index);
      _cur_field_index++;

      // Compute new byte size
      if (_byte_size == -1) _byte_size = 0;
      _byte_size += field->Type()->ByteSize();
   }
   return Type::addChild(s);
}

bool
Class::canCastTo (Type* dest_ty) const
{
   if (st::isa<st::Class>(dest_ty))
   {
      return this == dest_ty || isSubclassOf(st::cast<st::Class>(dest_ty));
   }
   return false;
}

int
Class::getAbsoluteFieldCount ()
{
   int count = 0;
   if (_parent != NULL && st::isa<st::Class>(_parent))
   {
      count += st::cast<st::Class>(_parent)->getAbsoluteFieldCount();
   }
   count += _cur_field_index;
   return count;
}

FieldVector
Class::getAllFields ()
{
   FieldVector fv;
   if (ParentClass() != NULL)
   {
      fv = ParentClass()->getAllFields();
   }

   SymbolMapIterator i;
   for (i = _children.begin(); i != _children.end(); ++i)
   {
      if (st::isa<st::Field>(i->second))
      {
         fv.push_back(st::cast<st::Field>(i->second));
      }
   }
   return fv;
}

int
Class::getFieldAbsoluteIndex (int relative_idx)
{
   return getAbsoluteFieldCount() - _cur_field_index + relative_idx;
}

FunctionVector
Class::getFunctionsLike (std::string name, FunctionType* func_ty)
{
   st::Symbol* cls = this;
   st::Symbol* func = NULL;
   FunctionVector funcs;

   while (cls != NULL)
   {
      if (st::isa<st::Class>(cls))
      {
         func = cls->getChild(name);
         if (func != NULL && func->Name() == name)
         {
            if (st::cast<st::Func>(func)->Type()->isOverridenCandidate(func_ty))
            {
               funcs.push_back(st::cast<st::Func>(func));
            }
         }
      }
      else
      {
         break;
      }
      cls = cls->Parent();
   }
   return funcs;
}

std::vector<st::Field*>
Class::getOrderedFields ()
{
   std::vector<st::Field*> v;
   size_t parent_field_count = 0;
   if (_parent!= NULL && st::isa<st::Class>(_parent))
   {
      v = st::cast<st::Class>(_parent)->getOrderedFields();
      parent_field_count = v.size();
   }
   if (hasFields())
   {
      v.resize(parent_field_count + _cur_field_index, NULL);

      Field* field = NULL;
      SymbolCollectionIterator i;
      for (i = _children.begin(); i != _children.end(); i++)
      {
         if (st::isa<st::Field>(i->second))
         {
            field = st::cast<st::Field>(i->second);
            v[parent_field_count + field->_field_index] = field;
         }
      }
      IF_DEBUG
      {
         for (size_t i = 0; i < v.size(); ++i)
         {
            assert(v[i] != NULL);
         }
      }
   }
   return v;
}

bool
Class::isDependingOn (Class* other_cls)
{
   DEBUG_REQUIRE (other_cls != NULL);
   DEBUG_REQUIRE (st::isa<st::Class>(other_cls));

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
         if (st::isa<st::Var>((*i).second))
         {
            cls_field = st::cast<st::Var>(i->second);
            if (st::isa<st::Class>(cls_field->Type()))
            {
               if (cls_field->Type() == other_cls)
               {
                  return true;
               }
               else if (st::cast<st::Class>(
                  cls_field->Type())->isDependingOn(other_cls))
               {
                  return true;
               }
            }
         }
      }
   }

   return false;
}

bool
Class::isSubclassOf (Class* cls) const
{
   st::Symbol* parent = cls;

   while (parent != NULL)
   {
      if (parent == cls) return true;
      parent = parent->Parent();
   }
   return false;
}


} }
