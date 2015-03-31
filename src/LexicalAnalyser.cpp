/*****************************************************************************

      LexicalAnalyser.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "LexicalAnalyser.h"

#include "Error.h"

#include <fstream>
#include <iostream>

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
==============================================================================
*/

Tokens  LexicalAnalyser::process (std::string txt)
{
   preprocess (txt);

   Tokens tokens_base;
   tokens_base.push_back (Token::comment_ml_begin);
   tokens_base.push_back (Token::comment_ml_end);
   tokens_base.push_back (Token::comment_sl);
   tokens_base.push_back (Token::lf);

   tokens_base.push_back (Token::library);
   tokens_base.push_back (Token::book);
   tokens_base.push_back (Token::chapter);
   tokens_base.push_back (Token::section);
   tokens_base.push_back (Token::subsection);
   tokens_base.push_back (Token::subsubsection);

   tokens_base.push_back (Token::codeblock);

   tokens_base.push_back (Token::note);
   tokens_base.push_back (Token::important);
   tokens_base.push_back (Token::warning);

   tokens_base.push_back (Token::namespace_);
   tokens_base.push_back (Token::class_);
   tokens_base.push_back (Token::inherit);
   tokens_base.push_back (Token::header);
   tokens_base.push_back (Token::guide);
   tokens_base.push_back (Token::declaration);
   tokens_base.push_back (Token::parameter);
   tokens_base.push_back (Token::type);
   tokens_base.push_back (Token::constructor);
   tokens_base.push_back (Token::destructor);
   tokens_base.push_back (Token::method);
   tokens_base.push_back (Token::variable);
   tokens_base.push_back (Token::brief);
   tokens_base.push_back (Token::division);

   tokens_base.push_back (Token::itemize);
   tokens_base.push_back (Token::enumerate);
   tokens_base.push_back (Token::item);

   tokens_base.push_back (Token::table);
   tokens_base.push_back (Token::row);

   tokens_base.push_back (Token::emph);
   tokens_base.push_back (Token::code);
   tokens_base.push_back (Token::image);
   tokens_base.push_back (Token::link);

   tokens_base.push_back (Token::include);

   tokens_base.push_back (Token::option_begin);
   tokens_base.push_back (Token::option_assign);
   tokens_base.push_back (Token::option_separator);
   tokens_base.push_back (Token::option_end);
   tokens_base.push_back (Token::block_begin);
   tokens_base.push_back (Token::block_end);
   tokens_base.push_back (Token::include_quote);
   tokens_base.push_back (Token::codeblock_marker);

   Tokens tokens_verbatim;
   tokens_verbatim.push_back (Token::codeblock_marker);
   tokens_verbatim.push_back (Token::lf);

   Tokens tokens_cur = tokens_base;

   size_t pos = 0;
   bool loop_flag = true;
   Tokens tokens;

   while (loop_flag)
   {
      Token token = read (pos, txt, tokens_cur);

      if (token != Token::eof)
      {
         tokens.push_back (token);
      }

      if (token == Token::codeblock_marker)
      {
         if (tokens_cur == tokens_base)
         {
            tokens_cur = tokens_verbatim;
         }
         else
         {
            tokens_cur = tokens_base;
         }
      }
      else if (token == Token::eof)
      {
         loop_flag = false;
      }
   }

   return tokens;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : preprocess
==============================================================================
*/

void  LexicalAnalyser::preprocess (std::string & txt)
{
   // change \r\n to \n

   bool loop_flag = true;

   while (loop_flag)
   {
      size_t pos = txt.find ("\r\n");

      if (pos == std::string::npos)
      {
         loop_flag = false;
      }
      else
      {
         txt.replace (pos, 2, "\n");
      }
   }

   // add trailing \x03 - end of text
   // txt += "\x03";
}



/*
==============================================================================
Name : read
==============================================================================
*/

Token  LexicalAnalyser::read (size_t & pos, const std::string & txt, const Tokens & tokens)
{
   // check eof

   if (pos == txt.size ()) return Token::eof;   // found

   // check start of token

   for (auto && token : tokens)
   {
      auto token_str = std::string (token);
      if (txt.compare (pos, token_str.size (), token_str) == 0)
      {
         Token ret (std::string (token), pos);

         pos += token_str.size ();

         return ret;  // found
      }
   }

   // find next token or eof

   size_t fpos = txt.size ();

   for (auto && token : tokens)
   {
      size_t spos = txt.find (std::string (token), pos);

      if (spos != std::string::npos)
      {
         if (spos < fpos) fpos = spos;
      }
   }

   std::string text = txt.substr (pos, fpos - pos);
   Token ret (text, pos);
   pos = fpos;

   return ret;
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

