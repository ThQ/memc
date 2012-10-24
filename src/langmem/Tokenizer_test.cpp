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
