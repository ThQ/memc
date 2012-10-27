#ifndef _MEM__AST__NODE__FILE__HPP_
#define _MEM__AST__NODE__FILE__HPP_


#include <string>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/EnumType.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/NodeList.hpp"
#include "mem/ast/node/Use.hpp"


namespace mem { namespace ast { namespace node {


class File : public NodeList
{
   public:
   static const int kTYPE = MetaKind::FILE;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor
   File ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // FunctionLinkedListHead
   GETTER(FunctionLinkedListHead, node::Func*) {return _function_ll_head;}
   SETTER(FunctionLinkedListHead, node::Func*) {_function_ll_head = val;}

   // FunctionLinkedListTail
   GETTER(FunctionLinkedListTail, node::Func*) {return _function_ll_tail;}
   SETTER(FunctionLinkedListTail, node::Func*) {_function_ll_tail = val;}

   // Id
   GETTER(Id, std::string) {return _id;}
   SETTER(Id, std::string) {_id = val;}

   // IncludePath
   SETTER(IncludePath, std::string) {_include_path = val;}

   virtual
   GETTER(MemorySize, int) {return sizeof(File);}

   // Path
   GETTER(Path, std::string) {return _path;}
   SETTER(Path, std::string) {_path = val;}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual void
   isValid (NodeValidator* v);

   void
   registerFunction (node::Func* func_n);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   std::string _id;
   std::string _include_path;
   std::string _path;
   Func* _function_ll_head;
   Func* _function_ll_tail;
};


} } }

#endif
