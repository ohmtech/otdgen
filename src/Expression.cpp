/*****************************************************************************

      Expression.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/Expression.h"

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
Name : ExpressionRoot::add_command
==============================================================================
*/

ExpressionCommand &  ExpressionRoot::add_command (std::string name)
{
   ExpressionCommand * ptr = new ExpressionCommand;
   ptr->name = name;

   expressions.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionRoot::add_codeblock
==============================================================================
*/

ExpressionCodeBlock &   ExpressionRoot::add_codeblock ()
{
   ExpressionCodeBlock * ptr = new ExpressionCodeBlock;

   expressions.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionRoot::add_include
==============================================================================
*/

ExpressionInclude &  ExpressionRoot::add_include (std::string path)
{
   ExpressionInclude * ptr = new ExpressionInclude;
   ptr->path = path;

   expressions.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionRoot::add_paragraph
==============================================================================
*/

ExpressionParagraph &   ExpressionRoot::add_paragraph ()
{
   ExpressionParagraph * ptr = new ExpressionParagraph;

   expressions.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionRoot::add_list_itemize
==============================================================================
*/

ExpressionList &  ExpressionRoot::add_list_itemize ()
{
   ExpressionList * ptr = new ExpressionList;
   ptr->type = ExpressionList::Type::Itemize;

   expressions.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionRoot::add_list_enumerate
==============================================================================
*/

ExpressionList &  ExpressionRoot::add_list_enumerate ()
{
   ExpressionList * ptr = new ExpressionList;
   ptr->type = ExpressionList::Type::Enumerate;

   expressions.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionRoot::add_table
==============================================================================
*/

ExpressionTable & ExpressionRoot::add_table ()
{
   ExpressionTable * ptr = new ExpressionTable;

   expressions.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionRoot::operator ==
==============================================================================
*/

bool  ExpressionRoot::operator == (const Expression & rhs) const
{
   const ExpressionRoot * rhs_ptr = dynamic_cast <const ExpressionRoot *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const ExpressionRoot & orhs = *rhs_ptr;

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
Name : ExpressionRoot::trace
==============================================================================
*/

void  ExpressionRoot::trace (size_t icnt) const
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
Name : ExpressionCommand::add_command
==============================================================================
*/

ExpressionCommand &  ExpressionCommand::add_command (std::string name_)
{
   ExpressionCommand * ptr = new ExpressionCommand;
   ptr->name = name_;

   bodies.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionCommand::add_paragraph
==============================================================================
*/

ExpressionParagraph &   ExpressionCommand::add_paragraph ()
{
   ExpressionParagraph * ptr = new ExpressionParagraph;

   bodies.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : Command::operator ==
==============================================================================
*/

bool  ExpressionCommand::operator == (const Expression & rhs) const
{
   const ExpressionCommand * rhs_ptr = dynamic_cast <const ExpressionCommand *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const ExpressionCommand & orhs = *rhs_ptr;

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
Name : ExpressionCommand::trace
==============================================================================
*/

void  ExpressionCommand::trace (size_t icnt) const
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
Name : ExpressionList::add_item
==============================================================================
*/

ExpressionParagraph &   ExpressionList::add_item ()
{
   ExpressionParagraph * ptr = new ExpressionParagraph;

   items.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionList::operator ==
==============================================================================
*/

bool  ExpressionList::operator == (const Expression & rhs) const
{
   const ExpressionList * rhs_ptr = dynamic_cast <const ExpressionList *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const ExpressionList & orhs = *rhs_ptr;

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
Name : ExpressionList::trace
==============================================================================
*/

void  ExpressionList::trace (size_t icnt) const
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
Name : ExpressionTable::add_row
==============================================================================
*/

ExpressionRow &   ExpressionTable::add_row ()
{
   ExpressionRow * ptr = new ExpressionRow;

   rows.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionTable::operator ==
==============================================================================
*/

bool  ExpressionTable::operator == (const Expression & rhs) const
{
   const ExpressionTable * rhs_ptr = dynamic_cast <const ExpressionTable *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const ExpressionTable & orhs = *rhs_ptr;

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
Name : ExpressionTable::trace
==============================================================================
*/

void  ExpressionTable::trace (size_t icnt) const
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
Name : ExpressionRow::add_cell
==============================================================================
*/

ExpressionParagraph &   ExpressionRow::add_cell ()
{
   ExpressionParagraph * ptr = new ExpressionParagraph;

   cells.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionRow::operator ==
==============================================================================
*/

bool  ExpressionRow::operator == (const Expression & rhs) const
{
   const ExpressionRow * rhs_ptr = dynamic_cast <const ExpressionRow *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const ExpressionRow & orhs = *rhs_ptr;

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
Name : ExpressionRow::trace
==============================================================================
*/

void  ExpressionRow::trace (size_t icnt) const
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
Name : ExpressionCodeBlock::add_line
==============================================================================
*/

void  ExpressionCodeBlock::add_line (std::string line, Style style)
{
   lines.emplace_back (line, style);
}



/*
==============================================================================
Name : ExpressionCodeBlock::add_paragraph
==============================================================================
*/

ExpressionParagraph &   ExpressionCodeBlock::add_paragraph ()
{
   ExpressionParagraph * ptr = new ExpressionParagraph;

   captions.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionCodeBlock::operator ==
==============================================================================
*/

bool  ExpressionCodeBlock::operator == (const Expression & rhs) const
{
   const ExpressionCodeBlock * rhs_ptr = dynamic_cast <const ExpressionCodeBlock *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const ExpressionCodeBlock & orhs = *rhs_ptr;

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
Name : ExpressionCodeBlock::trace
==============================================================================
*/

void  ExpressionCodeBlock::trace (size_t icnt) const
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
Name : ExpressionInclude::operator ==
==============================================================================
*/

bool  ExpressionInclude::operator == (const Expression & rhs) const
{
   const ExpressionInclude * rhs_ptr = dynamic_cast <const ExpressionInclude *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const ExpressionInclude & orhs = *rhs_ptr;

   return path == orhs.path;
}



/*
==============================================================================
Name : ExpressionCommand::trace
==============================================================================
*/

void  ExpressionInclude::trace (size_t icnt) const
{
   indent (icnt);
   std::cout << "Include\n";

   indent (icnt + 1);
   std::cout << path << "\n";
}



/*
==============================================================================
Name : ExpressionParagraph::add_text
==============================================================================
*/

ExpressionText &  ExpressionParagraph::add_text (std::string text)
{
   ExpressionText * ptr = new ExpressionText;
   ptr->body = text;

   expressions.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionParagraph::add_command
==============================================================================
*/

ExpressionCommand &  ExpressionParagraph::add_command (std::string name)
{
   ExpressionCommand * ptr = new ExpressionCommand;

   ptr->name = name;

   expressions.emplace_back (std::unique_ptr <Expression> (ptr));

   return *ptr;
}



/*
==============================================================================
Name : ExpressionParagraph::operator ==
==============================================================================
*/

bool  ExpressionParagraph::operator == (const Expression & rhs) const
{
   const ExpressionParagraph * rhs_ptr = dynamic_cast <const ExpressionParagraph *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const ExpressionParagraph & orhs = *rhs_ptr;

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
Name : ExpressionParagraph::trace
==============================================================================
*/

void  ExpressionParagraph::trace (size_t icnt) const
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
Name : ExpressionText::operator ==
==============================================================================
*/

bool  ExpressionText::operator == (const Expression & rhs) const
{
   const ExpressionText * rhs_ptr = dynamic_cast <const ExpressionText *> (&rhs);

   if (rhs_ptr == nullptr) return false;

   const ExpressionText & orhs = *rhs_ptr;

   return body == orhs.body;
}



/*
==============================================================================
Name : ExpressionText::trace
==============================================================================
*/

void  ExpressionText::trace (size_t icnt) const
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

