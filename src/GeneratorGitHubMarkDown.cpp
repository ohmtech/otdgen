/*****************************************************************************

      GeneratorGitHubMarkDown.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "GeneratorGitHubMarkDown.h"

#include "Conf.h"
#include "Toc.h"
#include "Token.h"

#include <fstream>
#include <iostream>

#include <cstdlib>
#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

GeneratorGitHubMarkDown::GeneratorGitHubMarkDown (const Conf & conf, Toc & toc)
:  _conf (conf)
,  _toc (toc)
{
}



/*
==============================================================================
Name : process
==============================================================================
*/

void GeneratorGitHubMarkDown::process (const Root & root)
{
   for (auto && expression_uptr : root.expressions)
   {
      const auto & expression = *expression_uptr;

      const Command * command_ptr = dynamic_cast <const Command *> (&expression);

      if (command_ptr != nullptr)
      {
         process (*command_ptr);
      }

      const List * list_ptr = dynamic_cast <const List *> (&expression);

      if (list_ptr != nullptr)
      {
         process (*list_ptr);
      }

      const Table * table_ptr = dynamic_cast <const Table *> (&expression);

      if (table_ptr!= nullptr)
      {
         process (*table_ptr);
      }

      const CodeBlock * codeblock_ptr = dynamic_cast <const CodeBlock *> (&expression);

      if (codeblock_ptr != nullptr)
      {
         process (*codeblock_ptr);
      }

      const Paragraph * paragraph_ptr = dynamic_cast <const Paragraph *> (&expression);

      if (paragraph_ptr != nullptr)
      {
         process (*paragraph_ptr);
      }
   }

   flush ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (const Command & command)
{
   const Paragraph & paragraph
      = dynamic_cast <const Paragraph &> (**command.bodies.begin ());

   if (
      (command.name == std::string (Token::library))
      || (command.name == std::string (Token::book))
      || (command.name == std::string (Token::chapter))
      )
   {
      process_navigation ();
   }

   _toc.set_current (command);

   if (command.name == std::string (Token::library))
   {
      flush ();

      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _cur_library = it->second;
   }
   else if (command.name == std::string (Token::book))
   {
      flush ();

      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _cur_book = it->second;
   }
   else if (command.name == std::string (Token::chapter))
   {
      flush ();

      _html += "\n";

      process_navigation ();

      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _cur_chapter = it->second;

      _html += "<h1 id=\"\">";
      process_block (paragraph);
      _html += "</h1>\n\n";
   }
   else if (command.name == std::string (Token::section))
   {
      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _cur_section = it->second;
      _cur_subsection.clear ();
      _cur_subsubsection.clear ();

      _html += "<h2 id=\"" + make_id () + "\">";
      process_block (paragraph);
      _html += "</h2>\n\n";
   }
   else if (command.name == std::string (Token::subsection))
   {
      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _cur_subsection = it->second;
      _cur_subsubsection.clear ();

      _html += "<h3 id=\"" + make_id () + "\">";
      process_block (paragraph);
      _html += "</h3>\n\n";
   }
   else if (command.name == std::string (Token::subsubsection))
   {
      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _cur_subsubsection = it->second;

      _html += "<h4 id=\"" + make_id () + "\">";
      process_block (paragraph);
      _html += "</h4>\n\n";
   }
   else if (command.name == std::string (Token::note))
   {
      _html += "<blockquote><h6>Note</h6> ";
      process_block (paragraph);
      _html += "</blockquote>\n\n";
   }
   else if (command.name == std::string (Token::important))
   {
      _html += "<blockquote><h6>Important</h6> ";
      process_block (paragraph);
      _html += "</blockquote>\n\n";
   }
   else if (command.name == std::string (Token::warning))
   {
      _html += "<blockquote><h6>W A R N I N G</h6> ";
      process_block (paragraph);
      _html += "</blockquote>\n\n";
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (const List & list)
{
   if (list.type == List::Type::Itemize)
   {
      _html += "<ul>\n";
   }
   else if (list.type == List::Type::Enumerate)
   {
      _html += "<ol>\n";
   }

   for (auto && item : list.items)
   {
      const auto & expression = *item;

      const auto & paragraph = dynamic_cast <const Paragraph &> (expression);

      _html += "<li>";

      process_block (paragraph);

      _html += "</li>\n";
   }

   if (list.type == List::Type::Itemize)
   {
      _html += "</ul>\n\n";
   }
   else if (list.type == List::Type::Enumerate)
   {
      _html += "</ol>\n\n";
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (const Table & table)
{
   _html += "<table>\n";

   for (auto && row_uptr : table.rows)
   {
      const auto & row = dynamic_cast <const Row &> (*row_uptr);

      _html += "<tr>\n";

      for (auto && cell_uptr : row.cells)
      {
         const auto & paragraph = dynamic_cast <const Paragraph &> (*cell_uptr);

         _html += "<td>";

         process_block (paragraph);

         _html += "</td>";
      }

      _html += "</tr>\n";
   }

   _html += "</table>\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (const CodeBlock & codeblock)
{
   _html += "```";

   auto it = codeblock.options.find ("language");

   if (it != codeblock.options.end ())
   {
      _html += it->second;
   }

   _html += "\n";

   for (auto && line : codeblock.lines)
   {
      _html += line.first + "\n";
   }

   _html += "```\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (const Paragraph & paragraph)
{
   _html += "<p>";
   process_block (paragraph);
   _html += "</p>\n\n";
}



/*
==============================================================================
Name : process_block
==============================================================================
*/

void  GeneratorGitHubMarkDown::process_block (const Paragraph & paragraph)
{
   for (auto && expression_uptr : paragraph.expressions)
   {
      const auto & expression = *expression_uptr;

      process_block (expression);
   }
}



/*
==============================================================================
Name : process_block
==============================================================================
*/

void  GeneratorGitHubMarkDown::process_block (const Expression & expression)
{
   const Command * command_ptr = dynamic_cast <const Command *> (&expression);

   if (command_ptr != nullptr)
   {
      const Command & command = *command_ptr;

      if (command.name == std::string (Token::code))
      {
         _html += "<code>";

         process_block (**command.bodies.begin ());

         _html += "</code>";
      }
      else if (command.name == std::string (Token::emph))
      {
         _html += "<em>";

         process_block (**command.bodies.begin ());

         _html += "</em>";
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
            std::string url = _toc.make_url (ide);

            _html += "<a href=\"" + url + "\">";
         }
         else if (!href.empty ())
         {
            _html += "<a href=\"http://" + href + "\">";
         }

         process_block (**command.bodies.begin ());

         _html += "</a>";
      }
   }

   const Paragraph * paragraph_ptr = dynamic_cast <const Paragraph *> (&expression);

   if (paragraph_ptr != nullptr)
   {
      process_block (*paragraph_ptr);
   }

   const Text * text_ptr = dynamic_cast <const Text *> (&expression);

   if (text_ptr != nullptr)
   {
      _html += text_ptr->body;
   }
}



/*
==============================================================================
Name : process_navigation
==============================================================================
*/

void  GeneratorGitHubMarkDown::process_navigation ()
{
   if (_html.empty ()) return;   // abort

   std::string url_prev = _toc.make_url_previous_chapter ();
   std::string url_next = _toc.make_url_next_chapter ();

   _html += "<p>";

   if (!url_prev.empty ())
   {
      _html += "<a href=\"" + url_prev + "\"><sup>previous</sup></a>";
   }

   if (!url_next.empty ())
   {
      _html += "<a href=\"" + url_next + "\"><sup>next</sup></a>";
   }

   _html += "</p>\n\n";
}


/*
==============================================================================
Name : flush
==============================================================================
*/

void  GeneratorGitHubMarkDown::flush ()
{
   if (_html.empty ()) return;   // abort

   if (_conf.output_path.empty ())
   {
      std::cout << _html;

      std::cout << "==========================\n\n";
   }
   else
   {
      std::string path;
      path += _conf.output_path + "/";

      if (_cur_book.empty ())
      {
         path += "README.md";
      }
      else if (_cur_chapter.empty ())
      {
         path += _cur_book + "/README.md";
      }
      else
      {
         path += _cur_book + "/" + _cur_chapter + ".md";
      }

      make_dirs (path);

      std::ofstream ofs (path, std::ifstream::binary);
      assert (ofs);

      ofs.write (&_html [0], int (_html.size ()));

      ofs.close ();
   }

   _html.clear ();
}



/*
==============================================================================
Name : filepath
==============================================================================
*/

void  GeneratorGitHubMarkDown::make_dirs (const std::string & filepath)
{
   size_t pos = filepath.rfind ("/");
   assert (pos != std::string::npos);

   std::string basepath = filepath.substr (0, pos - 0);

   std::string cmd = "mkdir -p " + basepath;
   system (cmd.c_str ());
}



/*
==============================================================================
Name : make_id
==============================================================================
*/

std::string GeneratorGitHubMarkDown::make_id ()
{
   std::string ret;
   ret += _cur_section;

   if (!_cur_subsection.empty ())
   {
      ret += "-" + _cur_subsection;
   }

   if (!_cur_subsubsection.empty ())
   {
      ret += "-" + _cur_subsubsection;
   }

   return ret;
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

