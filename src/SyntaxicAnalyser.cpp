/*****************************************************************************

      SyntaxicAnalyser.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/SyntaxicAnalyser.h"

#include "otdgen/Error.h"

#include <iostream>

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

SyntaxicAnalyser::SyntaxicAnalyser (Tokens & tokens, const std::string & source, const std::string & context)
:  _tokens (tokens)
,  _source (source)
,  _context (context)
{
   size_t pos = context.rfind ("/");
   assert (pos != std::string::npos);

   _base_path = context.substr (0, pos) + "/";

   _expressions_ptr_stack.push_back (&_root.expressions);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  SyntaxicAnalyser::process ()
{
   process_comment_ml ();
   process_comment_sl ();

   auto it = _tokens.begin ();

   process (it);
}



/*
==============================================================================
Name : tokens
==============================================================================
*/

Tokens   SyntaxicAnalyser::tokens ()
{
   return _tokens;
}



/*
==============================================================================
Name : root
==============================================================================
*/

ExpressionRoot &   SyntaxicAnalyser::root ()
{
   return _root;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process_comment_ml
Description :
   Remove multi line comments.
==============================================================================
*/

void  SyntaxicAnalyser::process_comment_ml ()
{
   auto it = _tokens.begin ();
   const auto it_end = _tokens.end ();

   bool erase_flag = false;

   for (; it != it_end ;)
   {
      auto && token = *it;

      if (token == Token::comment_ml_begin)
      {
         it = _tokens.erase (it);
         erase_flag = true;
      }
      else if (token == Token::comment_ml_end)
      {
         it = _tokens.erase (it);
         erase_flag = false;
      }
      else if (erase_flag)
      {
         it = _tokens.erase (it);
      }
      else
      {
         ++it;
      }
   }
}



/*
==============================================================================
Name : process_comment_sl
Description :
   Remove single line comments.
==============================================================================
*/

void  SyntaxicAnalyser::process_comment_sl ()
{
   auto it = _tokens.begin ();
   const auto it_end = _tokens.end ();

   bool erase_flag = false;

   for (; it != it_end ;)
   {
      auto && token = *it;

      if (token == Token::comment_sl)
      {
         it = _tokens.erase (it);
         erase_flag = true;
      }
      else if (token == Token::lf)
      {
         if (erase_flag)
         {
            it = _tokens.erase (it);
         }
         else
         {
            ++it;
         }

         erase_flag = false;
      }
      else if (erase_flag)
      {
         it = _tokens.erase (it);
      }
      else
      {
         ++it;
      }
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  SyntaxicAnalyser::process (Tokens::iterator & it)
{
   const auto it_end = _tokens.end ();

   for (; it != it_end ;)
   {
      auto && token = *it;

      if (
         (token == Token::library)
         || (token == Token::book)
         || (token == Token::chapter)
         || (token == Token::section)
         || (token == Token::subsection)
         || (token == Token::subsubsection)

         || (token == Token::note)
         || (token == Token::important)
         || (token == Token::warning)

         || (token == Token::namespace_)
         || (token == Token::class_)
         || (token == Token::inherit)
         || (token == Token::header)
         || (token == Token::guide)
         || (token == Token::parameter)
         || (token == Token::type)
         || (token == Token::constructor)
         || (token == Token::destructor)
         || (token == Token::method)
         || (token == Token::variable)
         || (token == Token::function)
         || (token == Token::brief)
         || (token == Token::division)
         )
      {
         process_command (it);

         if (it == it_end) break;
         ++it;
      }
      else if (
         (token == Token::itemize)
         || (token == Token::enumerate)
         )
      {
         process_list (it);
      }
      else if (token == Token::table)
      {
         process_table (it);
      }
      else if (
         (token == Token::codeblock)
         || (token == Token::declaration)
         )
      {
         process_codeblock (it);
      }
      else if (token == Token::include)
      {
         process_include (it);
      }
      else if ((_in_block_flag) && (token == Token::block_end))
      {
         --it;
         return;
      }
      else if (
         (token == Token::emph)
         || (token == Token::code)
         || (token == Token::image)
         || (token == Token::link)
         )
      {
         process_paragraph (it);
      }
      else if (token == Token::lf)
      {
         // drop
         ++it;
      }
      else
      {
         // at top level, everything else is text

         process_paragraph (it);
      }
   }
}



/*
==============================================================================
Name : process_command
==============================================================================
*/

void  SyntaxicAnalyser::process_command (Tokens::iterator & it)
{
   ExpressionCommand & command = add_expression <ExpressionCommand> ();
   command.name = *it;
   ++it;

   const auto it_end = _tokens.end ();

   enum
   {
      opt_or_body,
      opt_key,
      opt_assign,
      opt_value,
      opt_continue_or_end,
      expect_body,
      body,
      end_body,
      begin_body_or_end,
   };

   std::string key;

   Tokens::iterator it_body_end;

   auto state = opt_or_body;

   for (; it != it_end ; ++it)
   {
      if (it->is_whitespaces ()) continue;

      auto & token = *it;

      if (state == opt_or_body)
      {
         if (token == Token::option_begin)
         {
            state = opt_key;
         }
         else if (token == Token::block_begin)
         {
            state = body;
         }
         else
         {
            error (it, "Expected '[' or '{'.");
         }
      }
      else if (state == opt_key)
      {
         token.trim_whitespaces ();
         if (!token.is_key ()) error (it, "Wrong option key.");

         key = token;

         state = opt_assign;
      }
      else if (state == opt_assign)
      {
         if (token != Token::option_assign) error (it, "Expected '='.");

         state = opt_value;
      }
      else if (state == opt_value)
      {
         token.trim_whitespaces ();
         if (!token.is_value ()) error (it, "Wrong option value.");

         std::string value = token;

         if (key == "path")
         {
            value = _base_path + value;
         }

         command.options [key] = value;

         state = opt_continue_or_end;
      }
      else if (state == opt_continue_or_end)
      {
         if (token == Token::option_separator)
         {
            state = opt_key;
         }
         else if (token == Token::option_end)
         {
            state = expect_body;
         }
         else
         {
            error (it, "Expected '[' or '{'.");
         }
      }
      else if (state == expect_body)
      {
         if (token != Token::block_begin) error (it, "Expected '{'.");

         state = body;
      }
      else if (state == body)
      {
         size_t nbr_bodies = command.bodies.size ();

         push_expressions (command.bodies);

         bool in_block_flag = _in_block_flag;
         _in_block_flag = true;

         process (it);

         _in_block_flag = in_block_flag;

         pop_expressions ();

         if (nbr_bodies == command.bodies.size ())
         {
            // add an empty one

            command.add_paragraph ();
         }

         state = end_body;
      }
      else if (state == end_body)
      {
         if (token != Token::block_end) error (it, "Expected '}'.");

         it_body_end = it;

         state = begin_body_or_end;
      }
      else if (state == begin_body_or_end)
      {
         if (token == Token::block_begin)
         {
            state = body;
         }
         else
         {
            it = it_body_end;
            break;
         }
      }
   }
}



/*
==============================================================================
Name : process_list
==============================================================================
*/

void  SyntaxicAnalyser::process_list (Tokens::iterator & it)
{
   ExpressionList & list = add_expression <ExpressionList> ();

   if (*it == Token::itemize)
   {
      list.type = ExpressionList::Type::Itemize;
   }
   else if (*it == Token::enumerate)
   {
      list.type = ExpressionList::Type::Enumerate;
   }

   ++it;

   const auto it_end = _tokens.end ();

   enum
   {
      begin,
      item_or_end,
      item_begin,
      item_body,
      item_end,
   };

   std::string key;

   auto state = begin;

   for (; it != it_end ; ++it)
   {
      if (it->is_whitespaces ()) continue;

      auto & token = *it;

      if (state == begin)
      {
         if (token != Token::block_begin) error (it, "Expected '{'.");

         state = item_or_end;
      }
      else if (state == item_or_end)
      {
         if (token == Token::item)
         {
            state = item_begin;
         }
         else if (token == Token::block_end)
         {
            ++it;
            break;
         }
      }
      else if (state == item_begin)
      {
         if (token != Token::block_begin) error (it, "Expected '{'.");

         state = item_body;
      }
      else if (state == item_body)
      {
         push_expressions (list.items);

         bool in_block_flag = _in_block_flag;
         _in_block_flag = true;

         process (it);

         _in_block_flag = in_block_flag;

         pop_expressions ();

         state = item_end;
      }
      else if (state == item_end)
      {
         if (token != Token::block_end) error (it, "Expected '}'.");

         state = item_or_end;
      }
   }
}



/*
==============================================================================
Name : process_table
==============================================================================
*/

void  SyntaxicAnalyser::process_table (Tokens::iterator & it)
{
   ExpressionTable & table = add_expression <ExpressionTable> ();
   ++it;

   push_expressions (table.rows);

   bool in_block_flag = _in_block_flag;
   _in_block_flag = true;

   const auto it_end = _tokens.end ();

   enum
   {
      begin,
      row_or_end,
      row_begin_or_end,
      row_begin,
      row_body,
      row_end,
   };

   std::string key;

   auto state = begin;

   bool row_flag = false;

   for (; it != it_end ; ++it)
   {
      if (it->is_whitespaces ()) continue;

      auto & token = *it;

      if (state == begin)
      {
         if (token != Token::block_begin) error (it, "Expected '{'.");

         state = row_or_end;
      }
      else if (state == row_or_end)
      {
         if (token == Token::row)
         {
            if (row_flag)
            {
               pop_expressions ();
            }

            ExpressionRow & row = add_expression <ExpressionRow> ();
            push_expressions (row.cells);
            row_flag = true;

            state = row_begin;
         }
         else if (token == Token::block_end)
         {
            ++it;
            break;
         }
      }
      else if (state == row_begin_or_end)
      {
         if (token == Token::row)
         {
            if (row_flag)
            {
               pop_expressions ();
            }

            ExpressionRow & row = add_expression <ExpressionRow> ();
            push_expressions (row.cells);
            row_flag = true;

            state = row_begin;
         }
         else if (token == Token::block_begin)
         {
            state = row_body;
         }
         else if (token == Token::block_end)
         {
            ++it;
            break;
         }
      }
      else if (state == row_begin)
      {
         if (token != Token::block_begin) error (it, "Expected '{'.");

         state = row_body;
      }
      else if (state == row_body)
      {
         process (it);

         state = row_end;
      }
      else if (state == row_end)
      {
         if (token != Token::block_end) error (it, "Expected '}'.");

         state = row_begin_or_end;
      }
   }

   if (row_flag)
   {
      pop_expressions ();
   }

   _in_block_flag = in_block_flag;

   pop_expressions ();
}



/*
==============================================================================
Name : process_codeblock
==============================================================================
*/

void  SyntaxicAnalyser::process_codeblock (Tokens::iterator & it)
{
   ExpressionCodeBlock & codeblock = add_expression <ExpressionCodeBlock> ();
   if (*it == Token::declaration)
   {
      codeblock.options ["language"] = "c++";
      codeblock.cartouche = true;
   }
   ++it;

   const auto it_end = _tokens.end ();

   enum
   {
      opt_or_body,
      opt_key,
      opt_assign,
      opt_value,
      opt_continue_or_end,
      expect_body,
      body,
      caption_or_end,
      caption,
      end_caption,
   };

   std::string key;
   bool line_lf_flag = false;

   auto state = opt_or_body;

   for (; it != it_end ; ++it)
   {
      if (state == body)
      {
         if (it->is_whitespaces ())
         {
            if (!line_lf_flag)
            {
               line_lf_flag  = true;
               continue;
            }
            else
            {
               codeblock.lines.emplace_back ("", ExpressionCodeBlock::Style::Normal);
               continue;
            }
         }
      }
      else
      {
         if (it->is_whitespaces ()) continue;
      }

      auto & token = *it;

      if (state == opt_or_body)
      {
         if (token == Token::option_begin)
         {
            state = opt_key;
         }
         else if (token == Token::codeblock_marker)
         {
            state = body;
         }
         else
         {
            error (it, "Expected '[' or '***'.");
         }
      }
      else if (state == opt_key)
      {
         token.trim_whitespaces ();
         if (!token.is_key ()) error (it, "Wrong option key.");

         key = token;

         state = opt_assign;
      }
      else if (state == opt_assign)
      {
         if (token != Token::option_assign) error (it, "Expected '='.");

         state = opt_value;
      }
      else if (state == opt_value)
      {
         token.trim_whitespaces ();
         if (!token.is_value ()) error (it, "Wrong option value.");

         std::string value = token;

         codeblock.options [key] = value;

         state = opt_continue_or_end;
      }
      else if (state == opt_continue_or_end)
      {
         if (token == Token::option_separator)
         {
            state = opt_key;
         }
         else if (token == Token::option_end)
         {
            state = expect_body;
         }
         else
         {
            error (it, "Expected ',' or ']'.");
         }
      }
      else if (state == expect_body)
      {
         if (token != Token::codeblock_marker) error (it, "Expected '***'.");

         state = body;
      }
      else if (state == body)
      {
         if (token == Token::codeblock_marker)
         {
            state = caption_or_end;
         }
         else
         {
            std::string line (token);

            ExpressionCodeBlock::Style style = ExpressionCodeBlock::Style::Normal;

            if (ends_with (line, "\\fade"))
            {
               line = line.substr (0, line.size () - 5);
               style = ExpressionCodeBlock::Style::Fade;
            }
            else if (ends_with (line, "\\emph"))
            {
               line = line.substr (0, line.size () - 5);
               style = ExpressionCodeBlock::Style::Emph;
            }

            size_t pos = line.find_last_not_of ("\t ");
            if (pos != std::string::npos)
            {
               line = line.substr (0, pos + 1 - 0);
            }

            codeblock.lines.emplace_back (line, style);
            line_lf_flag = false;
         }
      }
      else if (state == caption_or_end)
      {
         if (token == Token::block_begin)
         {
            state = caption;
         }
         else
         {
            --it;
            break;
         }
      }
      else if (state == caption)
      {
         push_expressions (codeblock.captions);

         bool in_block_flag = _in_block_flag;
         _in_block_flag = true;

         process (it);

         _in_block_flag = in_block_flag;

         pop_expressions ();

         state = end_caption;
      }
      else if (state == end_caption)
      {
         if (token != Token::block_end) error (it, "Expected '}'.");
      }
   }
}



/*
==============================================================================
Name : ends_with
==============================================================================
*/

bool  SyntaxicAnalyser::ends_with (const std::string & str, const std::string & pattern)
{
   if (str.size () < pattern.size ()) return false;

   return str.compare (str.size () - pattern.size (), pattern.size (), pattern) == 0;
}



/*
==============================================================================
Name : process_include
==============================================================================
*/

void  SyntaxicAnalyser::process_include (Tokens::iterator & it)
{
   ExpressionInclude & include = add_expression <ExpressionInclude> ();
   ++it;

   const auto it_end = _tokens.end ();

   enum
   {
      begin_quote,
      path,
      end_quote,
   };

   std::string key;

   auto state = begin_quote;

   for (; it != it_end ; ++it)
   {
      if (it->is_whitespaces ()) continue;

      auto & token = *it;

      if (state == begin_quote)
      {
         if (token != Token::include_quote) error (it, "Expected '\"'.");
         state = path;
      }
      else if (state == path)
      {
         include.path = std::string (token);

         state = end_quote;
      }
      else if (state == end_quote)
      {
         if (token != Token::include_quote) error (it, "Expected '\"'.");
         ++it;
         break;
      }
   }
}



/*
==============================================================================
Name : process_paragraph
==============================================================================
*/

void  SyntaxicAnalyser::process_paragraph (Tokens::iterator & it)
{
   ExpressionParagraph & paragraph = add_expression <ExpressionParagraph> ();
   push_expressions (paragraph.expressions);

   const auto it_end = _tokens.end ();
   bool token_cr_flag = false;

   for (; it != it_end ; ++it)
   {
      auto && token = *it;

      if (token != Token ("\n"))
      {
         token_cr_flag = false;
      }

      if (
         (token == Token::emph)
         || (token == Token::code)
         || (token == Token::image)
         || (token == Token::link)
         )
      {
         process_command (it);
      }
      else if ((_in_block_flag) && (token == Token::block_end))
      {
         break;
      }
      else if (token == Token::lf)
      {
         if (token_cr_flag) break;

         ExpressionText & text = add_expression <ExpressionText> ();

         text.body = " ";

         token_cr_flag = true;
      }
      else
      {
         // interpret as text

         ExpressionText & text = add_expression <ExpressionText> ();

         text.body = std::string (token);
      }

      if (it == it_end) break;
   }

   // post process

   {
      auto & expressions = cur_expressions ();

      auto eit = expressions.begin ();
      const auto eit_end = expressions.end ();

      for (; eit != eit_end ;)
      {
         auto eit_next = eit;
         ++eit_next;

         if (eit_next != eit_end)
         {
            auto & expression = **eit;
            auto & next_expression = **eit_next;

            ExpressionText * text_ptr = dynamic_cast <ExpressionText *> (&expression);
            ExpressionText * next_text_ptr = dynamic_cast <ExpressionText *> (&next_expression);

            if ((text_ptr != nullptr) && (next_text_ptr != nullptr))
            {
               text_ptr->body += next_text_ptr->body;

               expressions.erase (eit_next);
            }
            else
            {
               ++eit;
            }
         }
         else
         {
            ++eit;
         }
      }
   }

   // post process
   {
      auto & expressions = cur_expressions ();

      auto eit = expressions.begin ();
      const auto eit_end = expressions.end ();

      if (eit != eit_end)
      {
         auto & expression = **eit;
         ExpressionText * text_ptr = dynamic_cast <ExpressionText *> (&expression);
         if (text_ptr != nullptr)
         {
            // trim
            size_t pos = text_ptr->body.find_first_not_of ("\t ");
            assert (pos != std::string::npos);

            text_ptr->body = text_ptr->body.substr (pos);
         }
      }
   }

   // post process
   {
      auto & expressions = cur_expressions ();

      auto eit = expressions.begin ();
      const auto eit_end = expressions.end ();

      if (eit != eit_end)
      {
         auto eit_last = eit_end;
         --eit_last;

         auto & expression = **eit_last;
         ExpressionText * text_ptr = dynamic_cast <ExpressionText *> (&expression);
         if (text_ptr != nullptr)
         {
            // trim
            size_t pos = text_ptr->body.find_last_not_of ("\t ");

            if (pos != std::string::npos)
            {
               text_ptr->body = text_ptr->body.substr (0, pos + 1 - 0);
            }
            else
            {
               expressions.erase (eit_last);
            }
         }
      }
   }

   //

   pop_expressions ();
}



/*
==============================================================================
Name : error
==============================================================================
*/

void  SyntaxicAnalyser::error (Tokens::iterator it, const std::string & error)
{
   size_t position = it->position ();

   size_t line = 1;
   size_t last_line_pos = 0;

   for (size_t i = 0 ; i < position ; ++i)
   {
      char c = _source [i];
      if (c == '\n')
      {
         line += 1;
         last_line_pos = i + 1;
      }
   }

   size_t column = position - last_line_pos;

   /*
   Example :
   /Users/raf/Desktop/dev/otdgen/src/fnc.h:16:10: fatal error: 'Line.h' file not found
   #include "Line.h"
            ^
   */

   std::cout
      << _context << ":" << line << ":" << column + 1 << ": fatal error: " << error
      << std::endl;

   size_t pos = _source.find ("\n", last_line_pos);
   if (pos == std::string::npos)
   {
      pos = _source.size ();
   }

   std::string line_str = _source.substr (last_line_pos, pos - last_line_pos);

   std::cout << line_str << std::endl;

   for (size_t i = 0 ; i < column ; ++i)
   {
      std::cout << " ";
   }

   std::cout << "^" << std::endl;

   throw Error (_context, line, column);
}



/*
==============================================================================
Name : push_expressions
==============================================================================
*/

void  SyntaxicAnalyser::push_expressions (Expressions & expressions)
{
   _expressions_ptr_stack.push_back (&expressions);
}



/*
==============================================================================
Name : pop_expressions
==============================================================================
*/

void  SyntaxicAnalyser::pop_expressions ()
{
   assert (!_expressions_ptr_stack.empty ());

   _expressions_ptr_stack.pop_back ();
}



/*
==============================================================================
Name : cur_expressions
==============================================================================
*/

Expressions &  SyntaxicAnalyser::cur_expressions ()
{
   assert (!_expressions_ptr_stack.empty ());

   return *_expressions_ptr_stack.back ();
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

