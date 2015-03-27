/*****************************************************************************

      GeneratorGitHubMarkDown.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "GeneratorGitHubMarkDown.h"

#include "Conf.h"
#include "DocBlocks.h"
#include "DocBook.h"
#include "DocChapter.h"
#include "DocCodeBlock.h"
#include "DocInformation.h"
#include "DocLibrary.h"
#include "DocList.h"
#include "DocParagraph.h"
#include "DocSection.h"
#include "DocTable.h"
#include "Toc.h"

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

GeneratorGitHubMarkDown::GeneratorGitHubMarkDown (const Conf & conf, const Toc & toc)
:  GeneratorBase (conf, toc)
{
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (const DocLibrary & library)
{
   std::vector <std::string> cur;
   cur.push_back (library.id);

   // overview

   std::string output;

   output += "<h1>";
   process (output, cur, library.title);
   output += "</h1>\n\n";

   process (output, cur, library.overview);

   write ("README.md", output);

   // books

   for (auto && book : library.books)
   {
      process (cur, book);
   }
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::vector <std::string> & cur, const DocBook & book)
{
   cur.push_back (book.id);

   // overview

   std::string output;

   output += "<h1>";
   process (output, cur, book.title);
   output += "</h1>\n\n";

   process (output, cur, book.overview);

   write (book.id + "/README.md", output);

   // chapters

   for (auto && chapter : book.chapters)
   {
      process (cur, chapter);
   }

   cur.resize (1);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::vector <std::string> & cur, const DocChapter & chapter)
{
   cur.push_back (chapter.id);

   std::string output;

   process_nav (output, chapter);

   output += "<h1>";
   process (output, cur, chapter.title);
   output += "</h1>\n\n";

   process (output, cur, chapter.blocks);

   process_nav (output, chapter);

   write (chapter.parent ().id + "/" + chapter.id + ".md", output);

   cur.resize (2);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & output, std::vector <std::string> & cur, const DocBlocks & blocks)
{
   for (auto && block : blocks)
   {
      switch (block.type)
      {
      case DocBlock::Type::Section:
         process (output, cur, block.cast <DocSection> ());
         break;

      case DocBlock::Type::Information:
         process (output, cur, block.cast <DocInformation> ());
         break;

      case DocBlock::Type::List:
         process (output, cur, block.cast <DocList> ());
         break;

      case DocBlock::Type::Table:
         process (output, cur, block.cast <DocTable> ());
         break;

      case DocBlock::Type::CodeBlock:
         process (output, cur, block.cast <DocCodeBlock> ());
         break;

      case DocBlock::Type::Paragraph:
         process (output, cur, block.cast <DocParagraph> ());
         break;
      }
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & output, std::vector <std::string> & cur, const DocSection & section)
{
   switch (section.level)
   {
   case DocSection::Level::Section:
      cur.resize (3);
      cur.push_back (section.id);
      output += "<h2 id=\"" + section.id + "\">";
      process (output, cur, section.title);
      output += "</h2>\n\n";
      break;

   case DocSection::Level::SubSection:
      cur.resize (4);
      cur.push_back (section.id_sub);
      output += "<h3 id=\"" + section.id + "-" + section.id_sub + "\">";
      process (output, cur, section.title);
      output += "</h3>\n\n";
      break;

   case DocSection::Level::SubSubSection:
      cur.resize (5);
      cur.push_back (section.id_subsub);
      output += "<h4 id=\"" + section.id + "-" + section.id_sub + "-" + section.id_subsub + "\">";
      process (output, cur, section.title);
      output += "</h4>\n\n";
      break;
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & output, std::vector <std::string> & cur, const DocInformation & information)
{
   switch (information.level)
   {
   case DocInformation::Level::Note:
      output += "<blockquote><h6>Note</h6> ";
      process (output, cur, information.body);
      output += "</blockquote>\n\n";
      break;

   case DocInformation::Level::Important:
      output += "<blockquote><h6>Important</h6> ";
      process (output, cur, information.body);
      output += "</blockquote>\n\n";
      break;

   case DocInformation::Level::Warning:
      output += "<blockquote><h6>W A R N I N G</h6> ";
      process (output, cur, information.body);
      output += "</blockquote>\n\n";
      break;
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & output, std::vector <std::string> & cur, const DocList & list)
{
   switch (list.type)
   {
   case DocList::Type::Itemization:
      output += "<ul>\n";
      break;

   case DocList::Type::Enumeration:
      output += "<ol>\n";
      break;
   }

   for (auto && item : list.items)
   {
      output += "<li>";
      process (output, cur, item);
      output += "</li>\n";
   }

   switch (list.type)
   {
   case DocList::Type::Itemization:
      output += "</ul>\n\n";
      break;

   case DocList::Type::Enumeration:
      output += "</ol>\n\n";
      break;
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & output, std::vector <std::string> & cur, const DocTable & table)
{
   output += "<table>\n";

   for (auto && row : table.rows)
   {
      output += "<tr>\n";

      for (auto && cell : row)
      {
         output += "<td>";

         process (output, cur, cell);

         output += "</td>\n";
      }

      output += "</tr>\n";
   }

   output += "</table>\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & output, std::vector <std::string> & /* cur */, const DocCodeBlock & codeblock)
{
   switch (codeblock.type)
   {
   case DocCodeBlock::Type::None:
      output += "```\n";
      break;

   case DocCodeBlock::Type::Cpp:
      output += "```c++\n";
      break;
   }

   for (auto && line : codeblock.lines)
   {
      output += line.first + "\n";
   }

   output += "```\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & output, std::vector <std::string> & cur, const DocParagraph & paragraph)
{
   output += "<p>";

   process (output, cur, paragraph.body);

   output += "</p>\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorGitHubMarkDown::process (std::string & output, std::vector <std::string> & cur, const DocInlines & inlines)
{
   for (auto && inlinee : inlines)
   {
      switch (inlinee.type)
      {
      case DocInline::Type::Text:
         output += inlinee.text;
         break;

      case DocInline::Type::Emphasis:
         output += "<em>";
         process (output, cur, inlinee.node);
         output += "</em>";
         break;

      case DocInline::Type::Code:
         output += "<code>";
         process (output, cur, inlinee.node);
         output += "</code>";
         break;

      case DocInline::Type::LinkId:
         output += "<a href=\"" + make_href (cur, inlinee.meta) + "\">";
         process (output, cur, inlinee.node);
         output += "</a>";
         break;

      case DocInline::Type::LinkUrl:
         output += "<a href=\"http://" + inlinee.meta + "\">";
         process (output, cur, inlinee.node);
         output += "</a>";
         break;
      }
   }
}



/*
==============================================================================
Name : make_href
==============================================================================
*/

std::string GeneratorGitHubMarkDown::make_href (const std::vector <std::string> & cur, const std::string & id)
{
   auto full_id = toc ().find (cur, id);

   std::string ret;

   // go back to library

   if (cur.size () > 1)
   {
      ret = "../";
   }

   // add full path

   if (full_id.size () > 1)
   {
      ret += full_id [1] + "/";
   }

   if (full_id.size () > 2)
   {
      ret += full_id [2] + ".md";
   }

   for (size_t i = 3 ; i < full_id.size () ; ++i)
   {
      ret += (i == 3) ? '#' : '-';
      ret += full_id [i];
   }

   return ret;
}



/*
==============================================================================
Name : process_nav
==============================================================================
*/

void  GeneratorGitHubMarkDown::process_nav (std::string & output, const DocChapter & chapter)
{
   output += "<p><sup>";

   if (chapter.has_previous ())
   {
      output += "<a href=\"" + chapter.previous ().id + ".md" + "\">previous</a>";
   }

   if (chapter.has_previous () && chapter.has_next ())
   {
      output += " | ";
   }

   if (chapter.has_next ())
   {
      output += "<a href=\"" + chapter.next ().id + ".md" + "\">next</a>";
   }

   output += "</sup></p>\n\n";
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

