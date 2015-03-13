/*****************************************************************************

      GeneratorGitHubMarkDown.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "GeneratorGitHubMarkDown.h"

#include "Token.h"

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
==============================================================================
*/

std::string GeneratorGitHubMarkDown::process (const Root & root)
{
   std::string html;

   for (auto && expression_uptr : root.expressions)
   {
      const auto & expression = *expression_uptr;

      const Command * command_ptr = dynamic_cast <const Command *> (&expression);

      if (command_ptr != nullptr)
      {
         process (html, *command_ptr);
      }

      const List * list_ptr = dynamic_cast <const List *> (&expression);

      if (list_ptr != nullptr)
      {
         process (html, *list_ptr);
      }

      const Table * table_ptr = dynamic_cast <const Table *> (&expression);

      if (table_ptr!= nullptr)
      {
         process (html, *table_ptr);
      }

      const CodeBlock * codeblock_ptr = dynamic_cast <const CodeBlock *> (&expression);

      if (codeblock_ptr != nullptr)
      {
         process (html, *codeblock_ptr);
      }

      const Paragraph * paragraph_ptr = dynamic_cast <const Paragraph *> (&expression);

      if (paragraph_ptr != nullptr)
      {
         process (html, *paragraph_ptr);
      }
   }

   return html;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & html, const Command & command)
{
   std::string sub_html;

   const Paragraph & paragraph
      = dynamic_cast <const Paragraph &> (**command.bodies.begin ());

   process_block (sub_html, paragraph);

   if (command.name == std::string (Token::chapter))
   {
      html += "<h1>" + sub_html + "</h1>\n\n";
   }
   else if (command.name == std::string (Token::section))
   {
      html += "<h2>" + sub_html + "</h2>\n\n";
   }
   else if (command.name == std::string (Token::subsection))
   {
      html += "<h3>" + sub_html + "</h3>\n\n";
   }
   else if (command.name == std::string (Token::subsubsection))
   {
      html += "<h4>" + sub_html + "</h4>\n\n";
   }
   else if (command.name == std::string (Token::note))
   {
      html += "<blockquote><h6>Note</h6> " + sub_html + "</blockquote>\n\n";
   }
   else if (command.name == std::string (Token::important))
   {
      html += "<blockquote><h6>Important</h6> " + sub_html + "</blockquote>\n\n";
   }
   else if (command.name == std::string (Token::warning))
   {
      html += "<blockquote><h6>W A R N I N G</h6> " + sub_html + "</blockquote>\n\n";
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & html, const List & list)
{
   if (list.type == List::Type::Itemize)
   {
      html += "<ul>\n";
   }
   else if (list.type == List::Type::Enumerate)
   {
      html += "<ol>\n";
   }

   for (auto && item : list.items)
   {
      const auto & expression = *item;

      const auto & paragraph = dynamic_cast <const Paragraph &> (expression);

      html += "<li>";

      process_block (html, paragraph);

      html += "</li>\n";
   }

   if (list.type == List::Type::Itemize)
   {
      html += "</ul>\n\n";
   }
   else if (list.type == List::Type::Enumerate)
   {
      html += "</ol>\n\n";
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & html, const Table & table)
{
   html += "<table>\n";

   for (auto && row_uptr : table.rows)
   {
      const auto & row = dynamic_cast <const Row &> (*row_uptr);

      html += "<tr>\n";

      for (auto && cell_uptr : row.cells)
      {
         const auto & paragraph = dynamic_cast <const Paragraph &> (*cell_uptr);

         html += "<td>";

         process_block (html, paragraph);

         html += "</td>";
      }

      html += "</tr>\n";
   }

   html += "</table>\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & html, const CodeBlock & codeblock)
{
   html += "```";

   auto it = codeblock.options.find ("language");

   if (it != codeblock.options.end ())
   {
      html += it->second;
   }

   html += "\n";

   for (auto && line : codeblock.lines)
   {
      html += line.first + "\n";
   }

   html += "```\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & html, const Paragraph & paragraph)
{
   html += "<p>";
   process_block (html, paragraph);
   html += "</p>\n\n";
}



/*
==============================================================================
Name : process_block
==============================================================================
*/

void  GeneratorGitHubMarkDown::process_block (std::string & html, const Paragraph & paragraph)
{
   for (auto && expression_uptr : paragraph.expressions)
   {
      const auto & expression = *expression_uptr;

      process_block (html, expression);
   }
}



/*
==============================================================================
Name : process_block
==============================================================================
*/

void  GeneratorGitHubMarkDown::process_block (std::string & html, const Expression & expression)
{
   const Command * command_ptr = dynamic_cast <const Command *> (&expression);

   if (command_ptr != nullptr)
   {
      const Command & command = *command_ptr;

      if (command.name == std::string (Token::code))
      {
         html += "<code>";

         process_block (html, **command.bodies.begin ());

         html += "</code>";
      }
      else if (command.name == std::string (Token::emph))
      {
         html += "<em>";

         process_block (html, **command.bodies.begin ());

         html += "</em>";
      }
      else if (command.name == std::string (Token::link))
      {
         std::string ide;
         {
            auto it = command.options.find ("id");
            if (it != command.options.end ())
            {
               ide = it->second;
            }
         }

         std::string href;
         {
            auto it = command.options.find ("href");
            if (it != command.options.end ())
            {
               href = it->second;
            }
         }

         if (!ide.empty ())
         {
            html += "<a>"; // for now
         }
         else if (!href.empty ())
         {
            html += "<a href=\"http://" + href + "\">";
         }

         process_block (html, **command.bodies.begin ());

         html += "</a>";
      }
   }

   const Paragraph * paragraph_ptr = dynamic_cast <const Paragraph *> (&expression);

   if (paragraph_ptr != nullptr)
   {
      process_block (html, *paragraph_ptr);
   }

   const Text * text_ptr = dynamic_cast <const Text *> (&expression);

   if (text_ptr != nullptr)
   {
      html += text_ptr->body;
   }
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

