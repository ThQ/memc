#include "gtest/gtest.h"
#include "langmem/Tokenizer.hpp"

void
assertTokenStream (std::string src, langmem::_TokenKind* tokens)
{
   langmem::Tokenizer tkz;
   tkz.reset();
   tkz.setInputString(src);

   while ((*tokens) != langmem::T_YACC_END)
   {
      ASSERT_EQ(*tokens, tkz.getNextToken().Kind());
      ++ tokens;
   }
}

TEST(TokenizerTest, MainFunctionSimplest)
{
   std::string src = "main (){}";

   langmem::_TokenKind tokens[] = {
      langmem::T_ID,
      langmem::T_OP,
      langmem::T_CP,
      langmem::T_OPEN_BRACE,
      langmem::T_CLOSE_BRACE,
      langmem::T_YACC_END};

   assertTokenStream(src, tokens);
}

TEST(TokenizerTest, MainFunctionWithParameterAndReturnType)
{
   std::string src = "main (argc :int) -> int{}";

   langmem::_TokenKind tokens[] = {
      langmem::T_ID,
      // Parameters
      langmem::T_OP,
      langmem::T_ID,
      langmem::T_COLON,
      langmem::T_ID,
      langmem::T_CP,
      // Return type
      langmem::T_RARR,
      langmem::T_ID,
      // Block
      langmem::T_OPEN_BRACE,
      langmem::T_CLOSE_BRACE,
      langmem::T_YACC_END};

   assertTokenStream(src, tokens);
}

TEST(TokenizerTest, CallWithParameters)
{
   std::string src = "fn (i :int, j :int) -> int {return i;}";
   src += " main(){ var i :int = fn(1, 2); }";

   langmem::_TokenKind tokens[] = {
      // fn (
      langmem::T_ID,
      langmem::T_OP,
      //i :int,
      langmem::T_ID,
      langmem::T_COLON,
      langmem::T_ID,
      langmem::T_COMMA,
      //j :int
      langmem::T_ID,
      langmem::T_COLON,
      langmem::T_ID,
      // ) -> int
      langmem::T_CP,
      langmem::T_RARR,
      langmem::T_ID,
      // { return i; }
      langmem::T_OPEN_BRACE,
      langmem::T_RETURN,
      langmem::T_ID,
      langmem::T_SEMICOLON,
      langmem::T_CLOSE_BRACE,
      // main ()
      langmem::T_ID,
      langmem::T_OP,
      langmem::T_CP,
      // { var i :int =
      langmem::T_OPEN_BRACE,
      langmem::T_VAR,
      langmem::T_ID,
      langmem::T_COLON,
      langmem::T_ID,
      langmem::T_EQ,
      // fn(1, 2); }
      langmem::T_ID,
      langmem::T_OP,
      langmem::T_LITERAL_NUMBER,
      langmem::T_COMMA,
      langmem::T_LITERAL_NUMBER,
      langmem::T_CP,
      langmem::T_SEMICOLON,
      langmem::T_CLOSE_BRACE,
      langmem::T_YACC_END};

   assertTokenStream(src, tokens);
}

TEST(TokenizerTest, ObjectCall)
{
   std::string src = "main () {p.some_func(1);}";

   langmem::_TokenKind tokens[] = {
      // main () {
      langmem::T_ID,
      langmem::T_OP,
      langmem::T_CP,
      langmem::T_OPEN_BRACE,
      // p.some_func
      langmem::T_ID,
      langmem::T_DOT,
      langmem::T_ID,
      // (1)
      langmem::T_OP,
      langmem::T_LITERAL_NUMBER,
      langmem::T_CP,
      // ;}
      langmem::T_SEMICOLON,
      langmem::T_CLOSE_BRACE,
      langmem::T_YACC_END};

   assertTokenStream(src, tokens);
}
