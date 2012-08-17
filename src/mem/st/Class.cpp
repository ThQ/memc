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
   _kind = CLASS;
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
   if (s->Kind() == FIELD)
   {
      st::Field* field = static_cast<Field*>(s);
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
   if (dest_ty->isClassType())
   {
      return this == dest_ty || isSubclassOf(static_cast<Class*>(dest_ty));
   }
   return false;
}

int
Class::getAbsoluteFieldCount ()
{
   int count = 0;
   if (_parent != NULL && _parent->isClassType())
   {
      count += static_cast<st::Class*>(_parent)->getAbsoluteFieldCount();
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
      if (i->second->isFieldSymbol())
      {
         fv.push_back(static_cast<Field*>(i->second));
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
      if (cls->isClassType())
      {
         func = cls->getChild(name);
         if (func != NULL && func->Name() == name)
         {
            if (st::castToFunc(func)->Type()->isOverridenCandidate(func_ty))
            {
               funcs.push_back(static_cast<st::Func*>(func));
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
   if (_parent!= NULL && _parent->isClassType())
   {
      v = static_cast<st::Class*>(_parent)->getOrderedFields();
      parent_field_count = v.size();
   }
   if (hasFields())
   {
      v.resize(parent_field_count + _cur_field_index, NULL);

      Field* field = NULL;
      SymbolCollectionIterator i;
      for (i = _children.begin(); i != _children.end(); i++)
      {
         if (i->second->Kind() == FIELD)
         {
            field = static_cast<Field*>(i->second);
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
   assert (other_cls != NULL);
   assert (other_cls->isClassType());

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
            if (cls_field->Type()->isClassType())
            {
               if (cls_field->Type() == other_cls)
               {
                  return true;
               }
               else if (static_cast<st::Class*>(
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


//-----------------------------------------------------------------------------
// PROTECTED FUNCTIONS
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// STATIC FUNCTIONS
//-----------------------------------------------------------------------------

Class*
castToClassType (Symbol* s)
{
   assert (s != NULL);
   assert (s->isClassType());
   return static_cast<Class*>(s);
}

} }
