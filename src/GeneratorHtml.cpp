/*****************************************************************************

      GeneratorHtml.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "GeneratorHtml.h"

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

GeneratorHtml::GeneratorHtml (const Conf & conf, Toc & toc)
:  GeneratorBase (conf, toc)
{
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (const DocLibrary & library)
{
   std::vector <std::string> cur;
   cur.push_back (library.id);

   std::string path = "index.html";

   if (conf ().format == Conf::Format::DocSet)
   {
      path = library.id + ".docset/Contents/Resources/Documents/" + path;
      make_plist (library);
      open_index (library);
   }

   // overview

   std::string output;

   process_header (output, cur);

   output += "<h1>";
   process (output, cur, library.title);
   output += "</h1>\n\n";

   process (output, cur, library.overview);

   process_footer (output);

   write (path, output);

   // books

   for (auto && book : library.books)
   {
      process (cur, book);
   }

   close_index ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (std::vector <std::string> & cur, const DocBook & book)
{
   cur.push_back (book.id);

   std::string rel_path = book.id + "/index.html";
   std::string path = rel_path;

   if (conf ().format == Conf::Format::DocSet)
   {
      path = book.parent ().id + ".docset/Contents/Resources/Documents/" + path;
   }

   // overview

   std::string output;

   process_header (output, cur);

   output += "<h1>";
   process (output, cur, book.title);
   output += "</h1>\n\n";

   process (output, cur, book.overview);

   process_footer (output);

   write (path, output);

   // index

   if (book.type == DocBook::Type::Guide)
   {
      add_index (process_no_style (book.title), "Guide", rel_path);
   }

   // chapters

   for (auto && chapter : book.chapters)
   {
      process (cur, chapter);
   }

   // end

   cur.resize (1);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (std::vector <std::string> & cur, const DocChapter & chapter)
{
   cur.push_back (chapter.id);

   std::string rel_path = chapter.parent ().id + "/" + chapter.id + ".html";
   std::string path = rel_path;

   if (conf ().format == Conf::Format::DocSet)
   {
      path = chapter.parent ().parent ().id + ".docset/Contents/Resources/Documents/" + path;
   }

   std::string output;

   process_header (output, cur);

   process_nav (output, chapter);

   if (chapter.type == DocChapter::Type::Class)
   {
      if (conf ().format == Conf::Format::DocSet)
      {
         output += "<a name=\"//apple_ref/cpp/Class/";
         output += escape_pourcent (chapter.name);
         output += "\" class=\"dashAnchor\"></a>\n";
      }
   }

   output += "<h1>";
   process (output, cur, chapter.title);
   output += "</h1>\n\n";

   if (chapter.type == DocChapter::Type::Class)
   {
      process (output, cur, chapter.cartouche);
   }

   process (output, cur, chapter.blocks);

   if (chapter.type == DocChapter::Type::Class)
   {
      process (output, cur, chapter.parameters);
      process (output, cur, chapter.types);
      process (output, cur, chapter.members);
   }

   process_nav (output, chapter);

   process_footer (output);

   write (path, output);

   // index

   if (chapter.type == DocChapter::Type::Class)
   {
      add_index (chapter.name, "Class", rel_path);
   }

   // end

   cur.resize (2);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (std::string & output, std::vector <std::string> & cur, const DocBlocks & blocks)
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

void  GeneratorHtml::process (std::string & output, std::vector <std::string> & cur, const DocSection & section)
{
   switch (section.level)
   {
   case DocSection::Level::Section:
      cur.resize (3);
      cur.push_back (section.id);
      if (conf ().format == Conf::Format::DocSet)
      {
         output += "<a name=\"//apple_ref/cpp/Section/";
         output += escape_pourcent (process_no_style (section.title));
         output += "\" class=\"dashAnchor\"></a>\n";
      }
      output += "<h2><a name=\"" + section.id + "\">";
      process (output, cur, section.title);
      output += "</a></h2>\n\n";
      break;

   case DocSection::Level::SubSection:
      cur.resize (4);
      cur.push_back (section.id_sub);
      output += "<h3><a name=\"" + section.id + "-" + section.id_sub + "\">";
      process (output, cur, section.title);
      output += "</a></h3>\n\n";
      break;

   case DocSection::Level::SubSubSection:
      cur.resize (5);
      cur.push_back (section.id_subsub);
      output += "<h4><a name=\"" + section.id + "-" + section.id_sub + "-" + section.id_subsub + "\">";
      process (output, cur, section.title);
      output += "</a></h4>\n\n";
      break;
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (std::string & output, std::vector <std::string> & cur, const DocInformation & information)
{
   switch (information.level)
   {
   case DocInformation::Level::Note:
      output += "<div class=\"note\"><p><strong>Note:</strong> ";
      process (output, cur, information.body);
      output += "</p></div>\n\n";
      break;

   case DocInformation::Level::Important:
      output += "<div class=\"important\"><p><strong>Important:</strong> ";
      process (output, cur, information.body);
      output += "</p></div>\n\n";
      break;

   case DocInformation::Level::Warning:
      output += "<div class=\"warning\"><p><strong>WARNING:</strong> ";
      process (output, cur, information.body);
      output += "</p></div>\n\n";
      break;
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (std::string & output, std::vector <std::string> & cur, const DocList & list)
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

void  GeneratorHtml::process (std::string & output, std::vector <std::string> & cur, const DocTable & table)
{
   output += "<table>\n";

   for (auto && row : table.rows)
   {
      output += "<tr>\n";

      for (auto && cell : row)
      {
         output += "<td><p>";

         process (output, cur, cell);

         output += "</p></td>\n";
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

void  GeneratorHtml::process (std::string & output, std::vector <std::string> & /* cur */, const DocCodeBlock & codeblock)
{
   output += "<div class=\"codeblock\"><table>\n";

   for (auto && line : codeblock.lines)
   {
      output += "<tr><td><pre>" + escape_xml (line.first) + "</pre></td></tr>\n";
   }

   output += "</table></div>\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (std::string & output, std::vector <std::string> & cur, const DocParagraph & paragraph)
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

void  GeneratorHtml::process (std::string & output, std::vector <std::string> & cur, const DocCartouche & cartouche)
{
   output += "<table>";

   if (!cartouche.inherit.empty ())
   {
      output += "<tr>";
      output += "<td><p>Inherits from</p></td>";
      output += "<td><p><code>" + cartouche.inherit + "</code></p></td>";
      output += "</tr>\n";
   }

   if (!cartouche.header.empty ())
   {
      output += "<tr>";
      output += "<td><p>Declared in</p></td>";
      output += "<td><p><code>" + cartouche.header + "</code></p></td>";
      output += "</tr>\n";
   }

   if (!cartouche.guide_id.empty ())
   {
      output += "<tr>";
      output += "<td><p>Companion Guide</p></td>";
      output += "<td><p>";
      process (output, cur, cartouche.guide);
      output += "</p></td>";
      output += "</tr>\n";
   }

   output += "</table>\n\n";

   if (!cartouche.declarations.empty ())
   {
      output += "<div class=\"codeblock\"><table>\n";

      for (auto && line : cartouche.declarations)
      {
         output += "<tr><td><pre>" + escape_xml (line) + "</pre></td></tr>\n";
      }

      output += "</table></div>\n\n";
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (std::string & output, std::vector <std::string> & cur, const DocParameters & parameters)
{
   if (parameters.empty ()) return; // abort

   output += "<h2>Template Parameters</h2>\n\n";

   output += "<table>";

   for (auto && parameter : parameters)
   {
      if (conf ().format == Conf::Format::DocSet)
      {
         output += "<a name=\"//apple_ref/cpp/Parameter/";
         output += escape_pourcent (parameter.type);
         output += "\" class=\"dashAnchor\"></a>\n";
      }

      output += "<tr>";
      output += "<td><p><code>" + parameter.type + "</code></p></td>";
      output += "<td><p>";
      process (output, cur, parameter.body);
      output += "</p></td>";
      output += "</tr>\n";
   }

   output += "</table>\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (std::string & output, std::vector <std::string> & cur, const DocTypes & types)
{
   if (types.empty ()) return; // abort

   output += "<h2>Member Types</h2>\n\n";

   output += "<table>";

   for (auto && type : types)
   {
      if (conf ().format == Conf::Format::DocSet)
      {
         output += "<a name=\"//apple_ref/cpp/Type/";
         output += escape_pourcent (type.type);
         output += "\" class=\"dashAnchor\"></a>\n";
      }

      output += "<tr>";

      if (type.id.empty ())
      {
         output += "<td><p><code>" + type.type + "</code></p></td>";
      }
      else
      {
         output += "<td><p><a href=\"" + make_href (cur, type.id) + "\"><code>" + type.type + "</code></a></p</td>";
      }

      output += "<td><p>";
      process (output, cur, type.body);
      output += "</p></td>";
      output += "</tr>\n";
   }

   output += "</table>\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (std::string & output, std::vector <std::string> & cur, const DocMembers & members)
{
   bool in_table_flag = false;

   enum class State
   {
      None,
      Functions,
      Variables,
   };

   State state = State::None;
   std::string division;

   // synopsys

   auto adjust_state = [&in_table_flag, &state, &division, &output](State target){
      if (state != target)
      {
         if (in_table_flag)
         {
            in_table_flag = false;
            output += "</table>\n\n";
         }

         state = target;

         switch (target)
         {
         case State::Functions:
            output += "<h2>Member Functions Synopsys</h2>\n\n";
            break;

         case State::Variables:
            output += "<h2>Member Variables Synopsys</h2>\n\n";
            break;

         default:
            assert (false);
            break;
         }
         output += division;
         division.clear ();
      }

      if (!in_table_flag)
      {
         in_table_flag = true;
         output += "<table>";
      }
   };

   for (auto && member : members)
   {
      if (member.type == DocMember::Type::Constructor)
      {
         adjust_state (State::Functions);

         output += "<tr>";
         output += "<td><p><a href=\"#member-function-constructor\">Constructor</a></p></td>";
         output += "<td><p>";
         process (output, cur, member.brief);
         output += "</p></td>";
         output += "</tr>\n";
      }
      else if (member.type == DocMember::Type::Destructor)
      {
         adjust_state (State::Functions);

         output += "<tr>";
         output += "<td><p><a href=\"#member-function-destructor\">Destructor</a></p></td>";
         output += "<td><p>";
         process (output, cur, member.brief);
         output += "</p></td>";
         output += "</tr>\n";
      }
      else if (member.type == DocMember::Type::Function)
      {
         adjust_state (State::Functions);

         output += "<tr>";
         output += "<td><p><code><a href=\"#member-function-" + escape_pourcent (member.name) + "\">" + member.name + "</a></code></p></td>";
         output += "<td><p>";
         process (output, cur, member.brief);
         output += "</p></td>";
         output += "</tr>\n";
      }
      else if (member.type == DocMember::Type::Variable)
      {
         adjust_state (State::Variables);

         output += "<tr>";
         output += "<td><p><code><a href=\"#member-variable-" + escape_pourcent (member.name) + "\">" + member.name + "</a></code></p></td>";
         output += "<td><p>";
         process (output, cur, member.brief);
         output += "</p></td>";
         output += "</tr>\n";
      }
      else if (member.type == DocMember::Type::Division)
      {
         if (in_table_flag)
         {
            in_table_flag = false;
            output += "</table>\n\n";
         }

         if (conf ().format == Conf::Format::DocSet)
         {
            division += "<a name=\"//apple_ref/cpp/Section/";
            division += escape_pourcent (process_no_style (member.brief));
            division += "\" class=\"dashAnchor\"></a>\n";
         }

         division += "<h3>";
         process (division, cur, member.brief);
         division += "</h3>\n\n";

         if (state != State::None)
         {
            output += division;
            division.clear ();
         }
      }
   }

   if (in_table_flag)
   {
      output += "</table>\n\n";
   }

   // details

   state = State::None;
   bool first_flag = true;

   for (auto && member : members)
   {
      if (member.type == DocMember::Type::Division) continue;

      if (member.type == DocMember::Type::Constructor)
      {
         if (state != State::Functions)
         {
            output += "<h2>Member Functions</h2>\n\n";

            state = State::Functions;
         }

         if (conf ().format == Conf::Format::DocSet)
         {
            output += "<a name=\"//apple_ref/cpp/Method/";
            output += "constructor";
            output += "\" class=\"dashAnchor\"></a>\n";
         }

         if (!first_flag) output += "<hr />";
         first_flag = false;

         output += "<h3 id=\"member-function-constructor\">Constructor</h3>\n";
      }
      else if (member.type == DocMember::Type::Destructor)
      {
         if (state != State::Functions)
         {
            output += "<h2>Member Functions</h2>\n\n";

            state = State::Functions;
         }

         if (conf ().format == Conf::Format::DocSet)
         {
            output += "<a name=\"//apple_ref/cpp/Method/";
            output += "destructor";
            output += "\" class=\"dashAnchor\"></a>\n";
         }

         if (!first_flag) output += "<hr />";
         first_flag = false;

         output += "<h3 id=\"member-function-destructor\">Destructor</h3>\n";
      }
      else if (member.type == DocMember::Type::Function)
      {
         if (state != State::Functions)
         {
            output += "<h2>Member Functions</h2>\n\n";

            state = State::Functions;
         }

         if (conf ().format == Conf::Format::DocSet)
         {
            output += "<a name=\"//apple_ref/cpp/Method/";
            output += escape_pourcent (member.name);
            output += "\" class=\"dashAnchor\"></a>\n";
         }

         if (!first_flag) output += "<hr />";
         first_flag = false;

         output += "<h3 id=\"member-function-" + escape_pourcent (member.name) + "\"><code>" + member.name + "</code></h3>\n";
      }
      else if (member.type == DocMember::Type::Variable)
      {
         if (state != State::Variables)
         {
            output += "<h2>Member Variables</h2>\n\n";

            state = State::Variables;
         }

         if (conf ().format == Conf::Format::DocSet)
         {
            output += "<a name=\"//apple_ref/cpp/Variable/";
            output += escape_pourcent (member.name);
            output += "\" class=\"dashAnchor\"></a>\n";
         }

         if (!first_flag) output += "<hr />";
         first_flag = false;

         output += "<h3 id=\"member-variable-" + escape_pourcent (member.name) + "\"><code>" + member.name + "</code></h3>\n";
      }

      process (output, cur, member.description);
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (std::string & output, std::vector <std::string> & cur, const DocInlines & inlines)
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

      case DocInline::Type::Image:
         output += "<center>";
         std::string rel_path = convert_pdf_to_png (cur, inlinee.meta);
         output += "<img src=\"" + rel_path + "\" />";
         if (!inlinee.node.empty ())
         {
            output += "<br />";
            output += "<div class=\"caption\"><p>";
            process (output, cur, inlinee.node);
            output += "</p></div>";
         }
         output += "</center>";
         break;
      }
   }
}



/*
==============================================================================
Name : make_href
==============================================================================
*/

std::string GeneratorHtml::make_href (const std::vector <std::string> & cur, const std::string & id)
{
   auto full_id = toc ().find (cur, id);

   return make_href (cur, full_id);
}



/*
==============================================================================
Name : make_href
==============================================================================
*/

std::string GeneratorHtml::make_href (const std::vector <std::string> & cur, const std::vector <std::string> & full_id)
{
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
      ret += full_id [2] + ".html";
   }
   else
   {
      ret += "index.html";
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
Name : process_no_style
==============================================================================
*/

std::string GeneratorHtml::process_no_style (const DocInlines & inlines)
{
   std::string ret;

   for (auto && inlinee : inlines)
   {
      switch (inlinee.type)
      {
      case DocInline::Type::Text:
         ret += inlinee.text;
         break;

      case DocInline::Type::Emphasis:
      case DocInline::Type::Code:
      case DocInline::Type::LinkId:
      case DocInline::Type::LinkUrl:
      case DocInline::Type::Image:
         ret += process_no_style (inlinee.node);
         break;
      }
   }

   return ret;
}



/*
==============================================================================
Name : process_nav
==============================================================================
*/

void  GeneratorHtml::process_nav (std::string & output, const DocChapter & chapter)
{
   output += "<div class=\"nav\" align=\"right\">\n";

   if (chapter.has_previous ())
   {
      output += "<a href=\"" + chapter.previous ().id + ".html" + "\">previous</a>";
   }

   if (chapter.has_previous () && chapter.has_next ())
   {
      output += "<span>&nbsp;</span>";
   }

   if (chapter.has_next ())
   {
      output += "<a href=\"" + chapter.next ().id + ".html" + "\">next</a>";
   }

   output += "</div>\n\n";
}



/*
==============================================================================
Name : process_header
==============================================================================
*/

void  GeneratorHtml::process_header (std::string & output, const std::vector <std::string> & cur)
{
   bool toc_flag = (cur.size () > 1) && (conf ().format == Conf::Format::Html);

   std::string title;

   if (cur.size () <= 2)
   {
      title += toc ().get_name (cur);
   }
   else
   {
      auto cur2 = cur;
      cur2.pop_back ();
      title += toc ().get_name (cur2);
      title += ": ";
      title += toc ().get_name (cur);
   }

   output += "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"\n";
   output += "  \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n";
   output += "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\" dir=\"ltr\">\n\n";

   output += "<head>\n";
   output += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n";

   output += "<title>" + title + "</title>\n";

   output += "<style>\n";

   output += "* {font-family: 'Lucida Grande', Helvetica, Arial, sans-serif; margin: 0; padding: 0; }\n";
   output += "body {background-color: #fff; }\n";
   output += "p {color: black; font-size: 13px; margin-bottom: 10px;}\n";
   output += "h1 {color: black; font-size: 28px; margin-bottom: 32px; padding-top: 24px; font-weight: normal; display: block; }\n";
   output += "h2 {color: #3c4c6c; display: block; font-size: 24px; font-weight: normal; margin-bottom: 20px; margin-top: 42px; border-bottom-color: #8391a8; border-bottom-style: solid; border-bottom-width: 1px;}\n";
   output += "h3 {color: black; font-size: 19px; margin-bottom: 4px; margin-top: 28px; font-weight: normal; display: block; }\n";
   output += "a {color: #36c; text-decoration: none; cursor:pointer; }\n";
   output += "a:active {color: #36c; text-decoration: none; cursor:pointer; }\n";
   output += "a:hover {color: #36c; text-decoration: underline; cursor:pointer; }\n";
   output += ".aerr {color: #f00}\n";

   output += "h2 a {color: #3c4c6c; text-decoration: none; cursor:auto; }\n";
   output += "h2 a:active {color: #3c4c6c; text-decoration: none; cursor:auto; }\n";
   output += "h2 a:hover {color: #3c4c6c; text-decoration: none; cursor:auto; }\n";

   output += "h3 a {color: black; text-decoration: none; cursor:auto; }\n";
   output += "h3 a:active {color: black; text-decoration: none; cursor:auto; }\n";
   output += "h3 a:hover {color: black; text-decoration: none; cursor:auto; }\n";

   output += "footer {font-size: 10px; position: fixed; display: block; bottom: 0px; background-color: #f1f5f9; border-top-color: #c7cfd5; border-top-style: solid; border-top-width: 1px; width: 100%; height:22px; padding-top: 7px; padding-left: 7px;}\n";
   output += "div {display: block;}\n";
   output += ".codeblock {margin-top:17px; margin-bottom:17px; clear: both; display: block; color: #333; }\n";
   output += "pre {font-family: Courier, Consolas, monospace; font-size: 12px; height: 14px; line-height: 14px; margin-bottom: 0px; margin-left: 6px; margin-right: 4px; margin-top: -1px;}\n";
   output += "small pre {color:#888;}\n";
   output += "emph pre {color:#000;}\n";
   output += "table {padding-top:5px; padding-bottom:6px; margin-bottom:12px; background-color: #f1f5f9; border-color: #c7cfd5; border-style: solid; border-width: 1px; width: 100%;}\n";
   output += "tr {}\n";
   output += "td > p {margin-left: 6px; height: 12px;}\n";

   output += ".note {margin-top:21px; margin-bottom:22px; padding-left: 8px; padding-right: 8px; background-color: #fff; border-color: #5088c5; border-style: solid; border-width: 1px; display: block;}\n";
   output += ".note strong {margin-right: 8px;}\n";
   output += ".note p {margin-top: 7px;}\n";

   output += ".important {margin-top:21px; margin-bottom:22px; padding-left: 8px; padding-right: 8px; background-color: #f1f5f9; border-color: #5088c5; border-style: solid; border-width: 1px; display: block;}\n";
   output += ".important strong {margin-right: 8px;}\n";
   output += ".important p {margin-top: 7px;}\n";

   output += ".warning {margin-top:21px; margin-bottom:22px; padding-left: 8px; padding-right: 8px; background-color: #f8e3e1; border-color: #c5443e; border-style: solid; border-width: 1px; display: block;}\n";
   output += ".warning strong {margin-right: 8px;}\n";
   output += ".warning p {margin-top: 7px;}\n";

   output += ".caption p {color: black; font-size: 10px; margin-bottom: 10px;}\n";

   output += "img {margin-top:10px; margin-bottom:10px;}\n";

   output += "ul {margin-left: 17px; margin-bottom: 10px;}\n";
   output += "ol {margin-left: 17px; margin-bottom: 10px;}\n";
   output += "li {color: black; font-size: 13px; margin-bottom: 7px;}\n";

   output += "code {font-family: Courier, Consolas, monospace;}\n";

   if (toc_flag)
   {
      output += "#content {padding-left: 26px; padding-right: 26px; position: absolute; top: 30px; left: 230px; width: 750px;}\n";
   }
   else
   {
      output += "#content {padding-left: 26px; padding-right: 26px; position: absolute; top: 30px; left: 30px; width: 750px;}\n";
   }

   output += "#toc {width: 230px; position: fixed; top: 30px; background-color: #f1f5f9; height: 100%; border-right-color: #c7cfd5; border-right-style: solid; border-right-width: 1px; padding-left: 0px; padding-top: 17px; overflow: auto;}\n";

   output += "#toc > ul {list-style-type: none;}\n";
   output += "#toc > ul > li {font-size: 11px; }\n";

   output += "#toc > ul > li > ul {list-style-type: none; margin-top:8px;}\n";
   output += "#toc > ul > li > ul > li {font-size: 11px; }\n";

   output += "#toc > p {font-size: 13px; margin-left: 17px;}\n";

   output += ".codeblock > p {margin-bottom: 3px; font-size: 11px;}\n";
   output += ".codeblock > p > strong {margin-right: 10px; color: #222;}\n";

   output += ".nav {font-size: 10px; margin-top: 20px; }\n";
   output += ".nav > span {margin-right: 20px;}\n";

   output += ".bottomspacer {height:100px;}\n";

   output += "#header {width:100%; position: fixed; background-color: #111; height: 30px; z-index: 900;}\n";

   output += "#header > p {color:#fff; font-size: 13px; padding-top: 6px; padding-left: 17px; }\n";
   output += "#header > p > a {color:#fff; font-size: 13px; text-decoration: none; cursor:pointer; padding-right: 56px;}\n";

   output += ".sectioncode {background-color: #f6f6f6; padding: 12px; margin-top: 18px;}\n";
   output += ".sectioncode > h3 {margin-top: 0px; padding-bottom: 8px;}\n";

   output += "hr { display: block; height: 1px; border: 0; border-top: 1px solid #eee; margin: 28px 0; padding: 0; }";

   output += "</style>\n";
   output += "</head>\n\n";

   output += "<body>\n\n";

   if (toc_flag)
   {
      auto cur_library = cur;
      cur_library.resize (1);
      auto a_library = make_href (cur, cur_library);

      auto cur_book = cur;
      cur_book.resize (2);
      auto a_book = make_href (cur, cur_book);

      output += "<div id=\"header\">\n";
      output += "<div style=\"width: 1006px;\"></div>\n";
      output += "<p>";
      output += "<a href=\"" + a_library + "\">" + toc ().get_name (cur_library) + "</a>";
      output += "<a href=\"" + a_book + "\">" + toc ().get_name (cur_book) + "</a>";
      output += "</p>\n";
      output += "</div>\n";

      output += "<div id=\"toc\">\n";

      output += "<p>" + toc ().get_name (cur_book) + "</p>\n";
      output += "<ul>\n";

      auto sub_toc = toc ().get_toc (cur_book);

      for (auto && item : sub_toc)
      {
         auto sub_cur = item.first;

         if (sub_cur.size () != 3) continue;

         auto sub_name = item.second;

         output += "<li>";
         output += "<a href=\"" + make_href (cur, sub_cur) + "\">" + toc ().get_name (sub_cur) + "</a>";

         if (sub_cur == cur)
         {
            output += "\t<ul>\n";

            auto sub_sub_toc = toc ().get_toc (sub_cur);

            for (auto && sub_item : sub_sub_toc)
            {
               auto sub_sub_cur = sub_item.first;

               if (sub_sub_cur.size () != 4) continue;

               output += "\t<li>";
               output += "<a href=\"" + make_href (cur, sub_sub_cur) + "\">" + toc ().get_name (sub_sub_cur) + "</a>";
               output += "</li>\n";
            }

            output += "\t</ul>\n";
         }

         output += "</li>\n";
      }

      output += "</ul>\n";
      output += "</div>\n\n";
   }

   output += "<div id=\"content\">\n";
}



/*
==============================================================================
Name : process_footer
==============================================================================
*/

void  GeneratorHtml::process_footer (std::string & output)
{
   output += "<div class=\"bottomspacer\">&nbsp;</div>\n";

   output += "</div>\n";
   output += "</body>\n";
   output += "</html>\n";
}



/*
==============================================================================
Name : make_plist
Reference :
   https://kapeli.com/docsets#dashDocset
==============================================================================
*/

void  GeneratorHtml::make_plist (const DocLibrary & library)
{
   std::string path = library.id + ".docset/Contents/Info.plist";

   std::string content;

   content += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
   content += "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n";
   content += "<plist version=\"1.0\">\n";
   content += "<dict>\n";
   content += "	<key>CFBundleIdentifier</key>\n";
   content += "	<string>" + library.id + "</string>\n";
   content += "	<key>CFBundleName</key>\n";
   content += "	<string>" + library.id + "</string>\n";
   content += "	<key>DocSetPlatformFamily</key>\n";
   content += "	<string>" + library.id + "</string>\n";
   content += "	<key>isDashDocset</key>\n";
   content += "	<true/>\n";
   content += "	<key>DashDocSetFamily</key>\n";
   content += "	<string>dashtoc</string>\n";
   content += "</dict>\n";
   content += "</plist>\n";

  write (path, content);
}



/*
==============================================================================
Name : open_index
Reference :
   https://kapeli.com/docsets#dashDocset
==============================================================================
*/

void  GeneratorHtml::open_index (const DocLibrary & library)
{
   close_index ();

   std::string rel_path = library.id + ".docset/Contents/Resources/docSet.dsidx";

   make_dirs (rel_path);

   std::string path;
   path += conf ().output_path + "/";
   path += rel_path;

   std::string cmd = "rm " + path;
   system (cmd.c_str ());

   int err = sqlite3_open (path.c_str (), &_db_ptr);
   assert (err == 0);

   err = sqlite3_exec (_db_ptr, "CREATE TABLE searchIndex(id INTEGER PRIMARY KEY, name TEXT, type TEXT, path TEXT);", nullptr, nullptr, nullptr);
   assert (err == 0);

   err = sqlite3_exec (_db_ptr, "CREATE UNIQUE INDEX anchor ON searchIndex (name, type, path);", nullptr, nullptr, nullptr);
   assert (err == 0);
}



/*
==============================================================================
Name : add_index
==============================================================================
*/

void  GeneratorHtml::add_index (std::string name, std::string type, std::string path)
{
   if (_db_ptr == nullptr) return;  // abort

   std::string expr;
   expr += "INSERT OR IGNORE INTO searchIndex(name, type, path) VALUES";
   expr += "('" + name + "', '" + type + "', '" + path + "');";

   int err = sqlite3_exec (_db_ptr, expr.c_str (), nullptr, nullptr, nullptr);
   assert (err == 0);
}



/*
==============================================================================
Name : close_index
==============================================================================
*/

void  GeneratorHtml::close_index ()
{
   if (_db_ptr != nullptr)
   {
      sqlite3_close (_db_ptr);
      _db_ptr = nullptr;
   }
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

