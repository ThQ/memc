#include "mem/ast/visitor/XmlDumper.hpp"

namespace mem { namespace ast { namespace visitor {

void
XmlDumper::dumpBoundSymbol (node::Node* n)
{
   if (n != NULL && n->BoundSymbol() != NULL)
   {
      *_out << " bound=\"";
      *_out << n->BoundSymbol()->gQualifiedName();
      *_out << "\"";
   }
}

void
XmlDumper::dumpExprType (node::Node* n)
{
   if (n != NULL && n->ExprType() != NULL)
   {
      *_out << " type=\"";
      *_out << n->ExprType()->gQualifiedName();
      *_out << "\"";
   }
}

void
XmlDumper::dumpPosition (node::Node* n)
{
   if (n!= NULL && n->Position() != NULL)
   {
      *_out << " position-start=\"";
      *_out << n->Position()->LineStart();
      *_out << ":";
      *_out << n->Position()->ColumnStart();
      *_out << "\" position-end=\"";
      *_out << n->Position()->LineEnd();
      *_out << ":";
      *_out << n->Position()->ColumnEnd();
      *_out << "\"";
   }
}

bool
XmlDumper::setup ()
{
   *_out << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
   return true;
}

bool
XmlDumper::tearDown ()
{
   return true;
}

bool
XmlDumper::visit (node::Node* node)
{
   if (node != NULL)
   {
      switch (node->Kind())
      {
         case node::Kind::ARRAY:
            visitArrayType(node::cast<node::ArrayType>(node)); break;

         case node::Kind::BLOCK:
            visitBlock(node::cast<node::Block>(node)); break;

         case node::Kind::CLASS:
            visitClass(node::cast<node::Class>(node)); break;

         case node::Kind::DOT:
            visitDot(node::cast<node::Dot>(node)); break;

         case node::Kind::FILE:
            visitFile (node::cast<node::File>(node)); break;

         case node::Kind::FINAL_ID:
            visitFinalId(node::cast<node::FinalId>(node)); break;

         case node::Kind::FUNCTION:
            visitFunction(node::cast<node::Func>(node)); break;

         case node::Kind::ID:
             visitId(node::cast<node::Text>(node)); break;

         case node::Kind::FIELD:
             visitField(node::cast<node::Field>(node)); break;

         case node::Kind::IF:
             visitIf(node::cast<node::If>(node)); break;

         case node::Kind::OP_NE:
         case node::Kind::OP_EQ_EQ:
         case node::Kind::OP_LT:
         case node::Kind::OP_LTE:
         case node::Kind::OP_GT:
         case node::Kind::OP_GTE:
            visitCompOp(node::cast<node::BinaryOp>(node)); break;

         case node::Kind::OP_DIV:
         case node::Kind::OP_MODULO:
         case node::Kind::OP_MUL:
         case node::Kind::OP_PLUS:
         case node::Kind::OP_MINUS:
         case node::Kind::OP_LSHIFT:
         case node::Kind::OP_RSHIFT:
         case node::Kind::OP_BIT_OR:
         case node::Kind::OP_BIT_AND:
         case node::Kind::OP_XOR:
            visitArithmeticOp(node); break;

         case node::Kind::PLACE_HOLDER:
            visitPlaceHolder(node); break;

         case node::Kind::NEW:
            visitNew(node::cast<node::New>(node)); break;

         case node::Kind::NODE_LIST:
            visitNodeList(node::cast<node::NodeList>(node)); break;

         case node::Kind::NUMBER:
            visitNumber(node::cast<node::Number>(node)); break;

         case node::Kind::RETURN:
            visitReturn(node::cast<node::Return>(node)); break;

         case node::Kind::ROOT:
            visitRoot(static_cast<node::Root*>(node)); break;

         case node::Kind::VARIABLE_ASSIGNMENT:
            visitVarAssign(node::cast<node::VarAssign>(node)); break;

         case node::Kind::VARIABLE_DECLARATION:
            visitVarDecl(node::cast<node::VarDecl>(node)); break;

         case node::Kind::WHILE:
            visitWhile(node::cast<node::While>(node)); break;

         default:
            IF_DEBUG
            {
               DEBUG_PRINTF("Unsupported node kind {ID: %d, NAME:%s}\n",
                  node->Kind(), node->KindNameCstr());
            }
      }
   }
   return false;
}

void
XmlDumper::visitArithmeticOp (node::Node* n)
{
   *_out << "<op-";
   switch (n->Kind())
   {
      case node::Kind::OP_BIT_AND: *_out << "band"; break;
      case node::Kind::OP_BIT_OR:  *_out << "bor"; break;
      case node::Kind::OP_XOR:     *_out << "xor"; break;
      case node::Kind::OP_LSHIFT:  *_out << "<<"; break;
      case node::Kind::OP_RSHIFT:  *_out << ">>"; break;
      case node::Kind::OP_PLUS:    *_out << "+"; break;
      case node::Kind::OP_MINUS:   *_out << "-"; break;
      case node::Kind::OP_MODULO:  *_out << "%"; break;
      case node::Kind::OP_MUL:     *_out << "*"; break;
      case node::Kind::OP_DIV:     *_out << "/"; break;
      default:
         assert(false);
   }
   dumpExprType(n);
   dumpPosition(n);
   *_out << " />\n";
}

void
XmlDumper::visitArrayType (node::ArrayType* n)
{
   *_out << "<array-type";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << ">\n";

   visitChildrenOf(n);

   *_out << "</array-type>\n";
}

void
XmlDumper::visitBlock (node::Block* n)
{
   *_out << "<block";
   *_out << " children=\"" << n->ChildCount() << "\"";
   dumpPosition(n);
   *_out << ">\n";

   visitChildrenOf(n);

   *_out << "</block>\n";
}

void
XmlDumper::visitChildrenOf (node::Node* n)
{
   DEBUG_REQUIRE (n != NULL);

   for (size_t i = 0; i < n->ChildCount(); ++i)
   {
      visit(n->getChild(i));
   }
}

void
XmlDumper::visitClass (node::Class* n)
{
   *_out << "<class";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << ">\n";

   visitChildrenOf(n);

   *_out << "</class>\n";
}

void
XmlDumper::visitCompOp (node::BinaryOp* n)
{
   std::string op_name = "?";

   *_out << "<op-" << op_name;
   dumpExprType(n);
   dumpPosition(n);
   *_out << ">\n";

   visit(n->LeftNode());
   visit(n->RightNode());

   *_out << "</op-" << op_name << ">\n";
}

void
XmlDumper::visitDot (node::Dot* n)
{
   std::string op_name = "?";

   *_out << "<op-dot";
   dumpExprType(n);
   dumpPosition(n);
   *_out << ">\n";

   visit(n->LeftNode());
   visit(n->RightNode());

   *_out << "</op-dot>\n";
}

void
XmlDumper::visitField (node::Field* n)
{
   *_out << "<field";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << ">\n";

   visitChildrenOf(n);

   *_out << "</field>\n";
}

void
XmlDumper::visitFile (node::File* n)
{
   *_out << "<file";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << ">\n";

   visitChildrenOf(n);

   *_out << "</file>\n";
}

void
XmlDumper::visitFinalId (node::FinalId* n)
{
   *_out << "<final-id";
   *_out << " name=\"" << n->Value() << "\"";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << " />\n";
}

void
XmlDumper::visitFunction (node::Func* n)
{
   *_out << "<function";
   *_out << " name=\"" << n->Value() << "\"";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << ">\n";

   visitChildrenOf(n);

   *_out << "</function>\n";
}

void
XmlDumper::visitIf (node::If* n)
{
   *_out << "<if";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << ">\n";

   visit (n->ConditionNode());
   visit (n->IfBlockNode());
   visit (n->ElseBlockNode());

   *_out << "</if>\n";
}

void
XmlDumper::visitId (node::Text* n)
{
   *_out << "<id";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << " />\n";
}

void
XmlDumper::visitNew (node::New* n)
{
   *_out << "<new";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << ">\n";

   visit(n->TypeNode());

   *_out << "</new>\n";
}

void
XmlDumper::visitNodeList (node::NodeList* n)
{
   *_out << "<node-list";
   *_out << " children=\"" << n->ChildCount() << "\"";
   dumpPosition(n);
   *_out << ">\n";

   visitChildrenOf(n);

   *_out << "</node-list>\n";
}

void
XmlDumper::visitNumber (node::Number* n)
{
   *_out << "<number";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << " />\n";
}

void
XmlDumper::visitPlaceHolder (node::Node* n)
{
   *_out << "<place-holder";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << " />\n";
}

void
XmlDumper::visitReturn (node::Return* n)
{
   *_out << "<return";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << ">\n";

   visit(n->ValueNode());

   *_out << "</return>\n";
}

void
XmlDumper::visitRoot (node::Root* n)
{
   *_out << "<root";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << ">\n";

   visitChildrenOf(n);

   *_out << "</root>\n";
}

void
XmlDumper::visitVarAssign (node::VarAssign* n)
{
   *_out << "<variable-assignment";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << ">\n";

   visitChildrenOf(n);

   *_out << "</variable-assignment>\n";
}

void
XmlDumper::visitVarDecl (node::VarDecl* n)
{
   *_out << "<variable-declaration";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << ">\n";

   visitChildrenOf(n);

   *_out << "</variable-declaration>\n";
}

void
XmlDumper::visitWhile (node::While* n)
{
   *_out << "<while";
   dumpExprType(n);
   dumpBoundSymbol(n);
   dumpPosition(n);
   *_out << ">\n";

   visitChildrenOf(n);

   *_out << "</while>\n";
}

} } }
