#include "mem/st/dumper/TextDumper.hpp"


namespace mem { namespace st { namespace dumper {


std::string
TextDumper::dump (st::Symbol* sym)
{
   std::string res = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
   res += "<?xml-stylesheet type=\"text/xsl\" href=\"mem_symbol_table.xsl\" ?>\n";
   res += this->dump_symbol(sym, 0);
   return res;
}

std::string
TextDumper::dump_children (st::Symbol* sym, int level)
{
   std::string res = "";
   std::map<std::string, Symbol*>::iterator i;
   for (i=sym->_children.begin(); i != sym->_children.end(); ++i)
   {
      res += this->dump_symbol(i->second, level+1);
   }
   return res;
}

std::string
TextDumper::dump_depth (int level)
{
   std::string res;
   for (int i = 0 ; i < level ; ++i)
   {
      res += "     ";
   }
   return res;
}


std::string
TextDumper::dump_symbol (st::Symbol* sym, int level)
{
   std::string depth = this->dump_depth(level);
   std::string res = depth;

   switch (sym->_kind)
   {
      case NAMESPACE:
         res += "<Namespace";
         res += " name=\"" + sym->_name + "\"";
         res += ">\n";
         res += this->dump_children(sym, level+1);
         res += depth + "</Namespace>";
         break;
      case FUNCTION:
      {
         st::Func* func = static_cast<st::Func*>(sym);

         res += "<Function";
         res += " name=\"" + func->gName() + "\"";
         if (func->gReturnType() != NULL)
         {
            res += " return_type=\"" + func->gReturnType()->gQualifiedName() + "\"";
         }
         res += ">\n";
         res += this->dump_children(func, level+1);
         res += depth + "</Function>";
      }
         break;

      case FUNCTION_SIGNATURE:
      {
         st::FunctionSignature* func_sign = static_cast<st::FunctionSignature*>(sym);

         res += "<FunctionSignature";
         res += " name=\"" + func_sign->_name + "\"";
         if (func_sign->gOverriddenFunc() != NULL)
         {
            res += " override=\"" + func_sign->gOverriddenFunc()->gQualifiedName() + "\"";
         }
         if (static_cast<st::Func*>(func_sign->_parent)->gReturnType() != NULL)
         {
            res += " return_type=\"" + static_cast<st::Func*>(func_sign->_parent)->gReturnType()->gQualifiedName() + "\"";
         }
         res += ">\n";
         res += this->dump_children(func_sign, level+1);
         res += depth + "</FunctionSignature>";
      }
      break;

      case CLASS:
         res += "<Class";
         res += " name=\"" + sym->_name + "\"";
         if (((st::Class*)sym)->_parent_type != NULL)
         {
            res += " parent_type=\"" + ((st::Class*)sym)->_parent_type->gQualifiedName() + "\"";
         }
         res += ">\n";
         res += this->dump_children(sym, level+1);
         res += depth + "</Class>";
         break;
      case VAR:
         res += "<Variable";
         res += " name=\"" + sym->_name + "\"";
         if (((st::Var*)sym)->_type != NULL)
         {
            res += " type=\"" + ((st::Var*)sym)->_type->gQualifiedName() + "\"";
         }
         res += ">\n";
         res += this->dump_children(sym, level+1);
         res += depth + "</Variable>";
         break;
      default:
         res += "<Unknown";
         res += " name=\"" + sym->_name + "\"";
         res += ">\n";
         res += this->dump_children(sym, level+1);
         res += depth + "</Unknown>";
   }
   res += "\n";

   return res;
}

void
TextDumper::dump_to (st::Symbol* sym, std::ostream& to)
{
   to << this->dump(sym);
}


} } }
