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
         res += "<Function";
         res += " name=\"" + sym->_name + "\"";
         res += " return_type=\"" + ((st::Function*)sym)->_return_type->get_qualified_name() + "\"";
         res += ">\n";
         res += this->dump_children(sym, level+1);
         res += depth + "</Function>";
         break;
      case FUNCTION_SIGNATURE:
         res += "<FunctionSignature";
         res += " name=\"" + sym->_name + "\"";
         res += " return_type=\"" + ((st::Function*)sym->_parent)->_return_type->get_qualified_name() + "\"";
         res += ">\n";
         res += this->dump_children(sym, level+1);
         res += depth + "</FunctionSignature>";
         break;

      case CLASS:
         res += "<Class";
         res += " name=\"" + sym->_name + "\"";
         if (((st::Class*)sym)->_parent_type != NULL)
         {
            res += " parent_type=\"" + ((st::Class*)sym)->_parent_type->get_qualified_name() + "\"";
         }
         res += ">\n";
         res += this->dump_children(sym, level+1);
         res += depth + "</Class>";
         break;
      case VAR:
         res += "<Variable";
         res += " name=\"" + sym->_name + "\"";
         res += " type=\"" + ((st::Var*)sym)->_type->get_qualified_name() + "\"";
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
