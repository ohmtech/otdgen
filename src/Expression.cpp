/*****************************************************************************

      Expression.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Expression.h"

#include <iostream>

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : Expression::indent
==============================================================================
*/

void  Expression::indent (size_t cnt) const
{
   for (size_t i = 0 ; i < cnt * 3 ; ++i) std::cout << " ";
}



/*
==============================================================================
Name : Root::add_command
==============================================================================
*/

Command &   Root::add_command (std::string name)
{
   Command * ptr = new Command;
   ptr->name = name;

   expressions.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Root::add_codeblock
==============================================================================
*/

CodeBlock &   Root::add_codeblock ()
{
   CodeBlock * ptr = new CodeBlock;

   expressions.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Root::add_include
==============================================================================
*/

Include &   Root::add_include (std::string path)
{
   Include * ptr = new Include;
   ptr->path = path;

   expressions.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Root::add_paragraph
==============================================================================
*/

Paragraph & Root::add_paragraph ()
{
   Paragraph * ptr = new Paragraph;

   expressions.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Root::add_list_itemize
==============================================================================
*/

List & Root::add_list_itemize ()
{
   List * ptr = new List;
   ptr->type = List::Type::Itemize;

   expressions.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Root::add_list_enumerate
==============================================================================
*/

List & Root::add_list_enumerate ()
{
   List * ptr = new List;
   ptr->type = List::Type::Enumerate;

   expressions.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Root::add_table
==============================================================================
*/

Table &  Root::add_table ()
{
   Table * ptr = new Table;

   expressions.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Root::operator ==
==============================================================================
*/

bool  Root::operator == (const Expression & rhs) const
{
   const Root * rhs_ptr = dynamic_cast <const Root *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const Root & orhs = *rhs_ptr;

   if (expressions.size () != orhs.expressions.size ()) return false;

   auto it = expressions.begin ();
   auto rit = orhs.expressions.begin ();
   const auto it_end = expressions.end ();

   for (; it != it_end ; ++it, ++rit)
   {
      Expression & expr = **it;
      Expression & rexpr = **rit;

      if (!(expr == rexpr)) return false;
   }

   return true;
}



/*
==============================================================================
Name : Root::trace
==============================================================================
*/

void  Root::trace (size_t icnt) const
{
   indent (icnt);
   std::cout << "Root\n";

   auto it = expressions.begin ();
   const auto it_end = expressions.end ();

   for (; it != it_end ; ++it)
   {
      Expression & expr = **it;

      expr.trace (icnt + 1);
   }
}



/*
==============================================================================
Name : Command::add_command
==============================================================================
*/

Command &   Command::add_command (std::string name_)
{
   Command * ptr = new Command;
   ptr->name = name_;

   bodies.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Command::add_paragraph
==============================================================================
*/

Paragraph & Command::add_paragraph ()
{
   Paragraph * ptr = new Paragraph;

   bodies.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Command::operator ==
==============================================================================
*/

bool  Command::operator == (const Expression & rhs) const
{
   const Command * rhs_ptr = dynamic_cast <const Command *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const Command & orhs = *rhs_ptr;

   if (name != orhs.name) return false;
   if (options != orhs.options) return false;
   if (bodies.size () != orhs.bodies.size ()) return false;

   auto it = bodies.begin ();
   auto rit = orhs.bodies.begin ();
   const auto it_end = bodies.end ();

   for (; it != it_end ; ++it, ++rit)
   {
      Expression & expr = **it;
      Expression & rexpr = **rit;

      if (!(expr == rexpr)) return false;
   }

   return true;
}



/*
==============================================================================
Name : Command::trace
==============================================================================
*/

void  Command::trace (size_t icnt) const
{
   indent (icnt);
   std::cout << "Command\n";

   indent (icnt + 1);
   std::cout << "name: \"" << name << "\"\n";

   indent (icnt + 1);
   std::cout << "options:\n";

   {
      auto it = options.begin ();
      const auto it_end = options.end ();

      for (; it != it_end ; ++it)
      {
         indent (icnt + 2);
         std::cout << "\"" << it->first << "\" = \"" << it->second << "\"\n";
      }
   }

   indent (icnt + 1);
   std::cout << "bodies:\n";

   {
      auto it = bodies.begin ();
      const auto it_end = bodies.end ();

      for (; it != it_end ; ++it)
      {
         Expression & expr = **it;

         expr.trace (icnt + 2);
      }
   }
}



/*
==============================================================================
Name : List::add_item
==============================================================================
*/

Paragraph & List::add_item ()
{
   Paragraph * ptr = new Paragraph;

   items.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : List::operator ==
==============================================================================
*/

bool  List::operator == (const Expression & rhs) const
{
   const List * rhs_ptr = dynamic_cast <const List *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const List & orhs = *rhs_ptr;

   if (type != orhs.type) return false;
   if (items.size () != orhs.items.size ()) return false;

   auto it = items.begin ();
   auto rit = orhs.items.begin ();
   const auto it_end = items.end ();

   for (; it != it_end ; ++it, ++rit)
   {
      Expression & expr = **it;
      Expression & rexpr = **rit;

      if (!(expr == rexpr)) return false;
   }

   return true;
}



/*
==============================================================================
Name : List::trace
==============================================================================
*/

void  List::trace (size_t icnt) const
{
   indent (icnt);
   std::cout << "List\n";

   indent (icnt + 1);
   if (type == Type::Itemize)
   {
      std::cout << "type: itemize\n";
   }
   else if (type == Type::Enumerate)
   {
      std::cout << "type: enumerate\n";
   }

   indent (icnt + 1);
   std::cout << "items:\n";

   {
      auto it = items.begin ();
      const auto it_end = items.end ();

      for (; it != it_end ; ++it)
      {
         Expression & expr = **it;

         expr.trace (icnt + 2);
      }
   }
}



/*
==============================================================================
Name : Table::add_row
==============================================================================
*/

Row & Table::add_row ()
{
   Row * ptr = new Row;

   rows.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Table::operator ==
==============================================================================
*/

bool  Table::operator == (const Expression & rhs) const
{
   const Table * rhs_ptr = dynamic_cast <const Table *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const Table & orhs = *rhs_ptr;

   if (rows.size () != orhs.rows.size ()) return false;

   auto it = rows.begin ();
   auto rit = orhs.rows.begin ();
   const auto it_end = rows.end ();

   for (; it != it_end ; ++it, ++rit)
   {
      Expression & expr = **it;
      Expression & rexpr = **rit;

      if (!(expr == rexpr)) return false;
   }

   return true;
}



/*
==============================================================================
Name : Table::trace
==============================================================================
*/

void  Table::trace (size_t icnt) const
{
   indent (icnt);
   std::cout << "Table\n";

   indent (icnt + 1);
   std::cout << "rows:\n";

   {
      auto it = rows.begin ();
      const auto it_end = rows.end ();

      for (; it != it_end ; ++it)
      {
         Expression & expr = **it;

         expr.trace (icnt + 2);
      }
   }
}



/*
==============================================================================
Name : Row::add_cell
==============================================================================
*/

Paragraph & Row::add_cell ()
{
   Paragraph * ptr = new Paragraph;

   cells.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Row::operator ==
==============================================================================
*/

bool  Row::operator == (const Expression & rhs) const
{
   const Row * rhs_ptr = dynamic_cast <const Row *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const Row & orhs = *rhs_ptr;

   if (cells.size () != orhs.cells.size ()) return false;

   auto it = cells.begin ();
   auto rit = orhs.cells.begin ();
   const auto it_end = cells.end ();

   for (; it != it_end ; ++it, ++rit)
   {
      Expression & expr = **it;
      Expression & rexpr = **rit;

      if (!(expr == rexpr)) return false;
   }

   return true;
}



/*
==============================================================================
Name : Row::trace
==============================================================================
*/

void  Row::trace (size_t icnt) const
{
   indent (icnt);
   std::cout << "Row\n";

   indent (icnt + 1);
   std::cout << "cells:\n";

   {
      auto it = cells.begin ();
      const auto it_end = cells.end ();

      for (; it != it_end ; ++it)
      {
         Expression & expr = **it;

         expr.trace (icnt + 2);
      }
   }
}



/*
==============================================================================
Name : CodeBlock::add_line
==============================================================================
*/

void  CodeBlock::add_line (std::string line, Style style)
{
   lines.emplace_back (line, style);
}



/*
==============================================================================
Name : Root::add_paragraph
==============================================================================
*/

Paragraph & CodeBlock::add_paragraph ()
{
   Paragraph * ptr = new Paragraph;

   captions.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : CodeBlock::operator ==
==============================================================================
*/

bool  CodeBlock::operator == (const Expression & rhs) const
{
   const CodeBlock * rhs_ptr = dynamic_cast <const CodeBlock *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const CodeBlock & orhs = *rhs_ptr;

   if (options != orhs.options) return false;
   if (lines != orhs.lines) return false;

   auto it = captions.begin ();
   auto rit = orhs.captions.begin ();
   const auto it_end = captions.end ();

   for (; it != it_end ; ++it, ++rit)
   {
      Expression & expr = **it;
      Expression & rexpr = **rit;

      if (!(expr == rexpr)) return false;
   }

   return true;
}



/*
==============================================================================
Name : CodeBlock::trace
==============================================================================
*/

void  CodeBlock::trace (size_t icnt) const
{
   indent (icnt);
   std::cout << "CodeBlock\n";

   indent (icnt + 1);
   std::cout << "options:\n";

   {
      auto it = options.begin ();
      const auto it_end = options.end ();

      for (; it != it_end ; ++it)
      {
         indent (icnt + 2);
         std::cout << "\"" << it->first << "\" = \"" << it->second << "\"\n";
      }
   }

   indent (icnt + 1);
   std::cout << "lines:\n";

   {
      auto it = lines.begin ();
      const auto it_end = lines.end ();

      for (; it != it_end ; ++it)
      {
         auto && line = *it;

         indent (icnt + 2);
         std::cout << line.first;

         switch (line.second)
         {
         case Style::Normal:
            // nothing
            break;

         case Style::Fade:
            std::cout << "   (Fade)";
            break;

         case Style::Emph:
            std::cout << "   (Emph)";
            break;
         }

         std::cout << "\n";
      }
   }

   indent (icnt + 1);
   std::cout << "captions:\n";

   {
      auto it = captions.begin ();
      const auto it_end = captions.end ();

      for (; it != it_end ; ++it)
      {
         Expression & expr = **it;

         expr.trace (icnt + 2);
      }
   }
}



/*
==============================================================================
Name : Include::operator ==
==============================================================================
*/

bool  Include::operator == (const Expression & rhs) const
{
   const Include * rhs_ptr = dynamic_cast <const Include *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const Include & orhs = *rhs_ptr;

   return path == orhs.path;
}



/*
==============================================================================
Name : Command::trace
==============================================================================
*/

void  Include::trace (size_t icnt) const
{
   indent (icnt);
   std::cout << "Include\n";

   indent (icnt + 1);
   std::cout << path << "\n";
}



/*
==============================================================================
Name : Paragraph::add_text
==============================================================================
*/

Text &   Paragraph::add_text (std::string text)
{
   Text * ptr = new Text;
   ptr->body = text;

   expressions.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Paragraph::add_command
==============================================================================
*/

Command & Paragraph::add_command (std::string name)
{
   Command * ptr = new Command;

   ptr->name = name;

   expressions.push_back (std::move (std::unique_ptr <Expression> (ptr)));

   return *ptr;
}



/*
==============================================================================
Name : Paragraph::operator ==
==============================================================================
*/

bool  Paragraph::operator == (const Expression & rhs) const
{
   const Paragraph * rhs_ptr = dynamic_cast <const Paragraph *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const Paragraph & orhs = *rhs_ptr;

   if (expressions.size () != orhs.expressions.size ()) return false;

   auto it = expressions.begin ();
   auto rit = orhs.expressions.begin ();
   const auto it_end = expressions.end ();

   for (; it != it_end ; ++it, ++rit)
   {
      Expression & expr = **it;
      Expression & rexpr = **rit;

      if (!(expr == rexpr)) return false;
   }

   return true;
}



/*
==============================================================================
Name : Command::trace
==============================================================================
*/

void  Paragraph::trace (size_t icnt) const
{
   indent (icnt);
   std::cout << "Paragraph\n";

   auto it = expressions.begin ();
   const auto it_end = expressions.end ();

   for (; it != it_end ; ++it)
   {
      Expression & expr = **it;

      expr.trace (icnt + 1);
   }
}



/*
==============================================================================
Name : Text::operator ==
==============================================================================
*/

bool  Text::operator == (const Expression & rhs) const
{
   const Text * rhs_ptr = dynamic_cast <const Text *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const Text & orhs = *rhs_ptr;

   return body == orhs.body;
}



/*
==============================================================================
Name : Text::trace
==============================================================================
*/

void  Text::trace (size_t icnt) const
{
   indent (icnt);
   std::cout << "Text\n";

   indent (icnt + 1);
   std::cout << "\"" << body << "\"\n";
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

