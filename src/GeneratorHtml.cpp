/*****************************************************************************

      GeneratorHtml.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "GeneratorHtml.h"

#include "Conf.h"
#include "Toc.h"
#include "Token.h"

#include <fstream>
#include <iostream>

#include "sqlite3.h"

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
:  _conf (conf)
,  _toc (toc)
{
}



/*
==============================================================================
Name : process
==============================================================================
*/

void GeneratorHtml::process (const ExpressionRoot & root)
{
   for (auto && expression_uptr : root.expressions)
   {
      const auto & expression = *expression_uptr;

      const ExpressionCommand * command_ptr = dynamic_cast <const ExpressionCommand *> (&expression);

      if (command_ptr != nullptr)
      {
         process (*command_ptr);
      }

      const ExpressionList * list_ptr = dynamic_cast <const ExpressionList *> (&expression);

      if (list_ptr != nullptr)
      {
         process (*list_ptr);
      }

      const ExpressionTable * table_ptr = dynamic_cast <const ExpressionTable *> (&expression);

      if (table_ptr!= nullptr)
      {
         process (*table_ptr);
      }

      const ExpressionCodeBlock * codeblock_ptr = dynamic_cast <const ExpressionCodeBlock *> (&expression);

      if (codeblock_ptr != nullptr)
      {
         process (*codeblock_ptr);
      }

      const ExpressionParagraph * paragraph_ptr = dynamic_cast <const ExpressionParagraph *> (&expression);

      if (paragraph_ptr != nullptr)
      {
         process (*paragraph_ptr);
      }
   }

   flush ();

   if (_conf.format == Conf::Format::DocSet)
   {
      make_plist ();
      make_index ();
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

void  GeneratorHtml::process (const ExpressionCommand & command)
{
   const ExpressionParagraph & paragraph
      = dynamic_cast <const ExpressionParagraph &> (**command.bodies.begin ());

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

      _name_book.clear ();
      _name_chapter.clear ();

      start ();

      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _cur_library = it->second;
   }
   else if (command.name == std::string (Token::book))
   {
      flush ();

      _name_book = process_block_no_style (paragraph);
      _name_chapter.clear ();

      start ();

      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _cur_book = it->second;
   }
   else if (command.name == std::string (Token::chapter))
   {
      flush ();

      _name_chapter = process_block_no_style (paragraph);

      start ();

      process_navigation ();

      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _cur_chapter = it->second;

      _html += "<h1>";
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

      _html += "<h2><a name=\"" + make_id () + "\">";
      process_block (paragraph);
      _html += "</a></h2>\n\n";
   }
   else if (command.name == std::string (Token::subsection))
   {
      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _cur_subsection = it->second;
      _cur_subsubsection.clear ();

      _html += "<h3><a name=\"" + make_id () + "\">";
      process_block (paragraph);
      _html += "</a></h3>\n\n";
   }
   else if (command.name == std::string (Token::subsubsection))
   {
      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _cur_subsubsection = it->second;

      _html += "<h4><a name=\"" + make_id () + "\">";
      process_block (paragraph);
      _html += "</a></h4>\n\n";
   }
   else if (command.name == std::string (Token::note))
   {
      _html += "<div class=\"note\"><p><strong>Note:</strong> ";
      process_block (paragraph);
      _html += "</p></div>\n\n";
   }
   else if (command.name == std::string (Token::important))
   {
      _html += "<div class=\"important\"><p><strong>Important:</strong> ";
      process_block (paragraph);
      _html += "</p></div>\n\n";
   }
   else if (command.name == std::string (Token::warning))
   {
      _html += "<div class=\"warning\"><p><strong>WARNING:</strong> ";
      process_block (paragraph);
      _html += "</p></div>\n\n";
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (const ExpressionList & list)
{
   if (list.type == ExpressionList::Type::Itemize)
   {
      _html += "<ul>\n";
   }
   else if (list.type == ExpressionList::Type::Enumerate)
   {
      _html += "<ol>\n";
   }

   for (auto && item : list.items)
   {
      const auto & expression = *item;

      const auto & paragraph = dynamic_cast <const ExpressionParagraph &> (expression);

      _html += "<li>";

      process_block (paragraph);

      _html += "</li>\n";
   }

   if (list.type == ExpressionList::Type::Itemize)
   {
      _html += "</ul>\n\n";
   }
   else if (list.type == ExpressionList::Type::Enumerate)
   {
      _html += "</ol>\n\n";
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (const ExpressionTable & table)
{
   _html += "<table>\n";

   for (auto && row_uptr : table.rows)
   {
      const auto & row = dynamic_cast <const ExpressionRow &> (*row_uptr);

      _html += "<tr>\n";

      for (auto && cell_uptr : row.cells)
      {
         const auto & paragraph = dynamic_cast <const ExpressionParagraph &> (*cell_uptr);

         _html += "<td><p>";

         process_block (paragraph);

         _html += "</p></td>";
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

void  GeneratorHtml::process (const ExpressionCodeBlock & codeblock)
{
   _html += "<div class=\"codeblock\"><table>\n";

   for (auto && line : codeblock.lines)
   {
      _html += "<tr><td><pre>" + escape_xml (line.first) + "</pre></td></tr>\n";
   }

   _html += "</table></div>\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorHtml::process (const ExpressionParagraph & paragraph)
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

void  GeneratorHtml::process_block (const ExpressionParagraph & paragraph)
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

void  GeneratorHtml::process_block (const Expression & expression)
{
   const ExpressionCommand * command_ptr = dynamic_cast <const ExpressionCommand *> (&expression);

   if (command_ptr != nullptr)
   {
      const ExpressionCommand & command = *command_ptr;

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

   const ExpressionParagraph * paragraph_ptr = dynamic_cast <const ExpressionParagraph *> (&expression);

   if (paragraph_ptr != nullptr)
   {
      process_block (*paragraph_ptr);
   }

   const ExpressionText * text_ptr = dynamic_cast <const ExpressionText *> (&expression);

   if (text_ptr != nullptr)
   {
      _html += escape_xml (text_ptr->body);
   }
}



/*
==============================================================================
Name : process_block_no_style
==============================================================================
*/

std::string  GeneratorHtml::process_block_no_style (const ExpressionParagraph & paragraph)
{
   std::string ret;

   for (auto && expression_uptr : paragraph.expressions)
   {
      const auto & expression = *expression_uptr;

      ret += process_block_no_style (expression);
   }

   return ret;
}



/*
==============================================================================
Name : process_block_no_style
==============================================================================
*/

std::string  GeneratorHtml::process_block_no_style (const Expression & expression)
{
   std::string ret;

   const ExpressionCommand * command_ptr = dynamic_cast <const ExpressionCommand *> (&expression);

   if (command_ptr != nullptr)
   {
      const ExpressionCommand & command = *command_ptr;

      if (command.name == std::string (Token::code))
      {
         ret = process_block_no_style (**command.bodies.begin ());
      }
      else if (command.name == std::string (Token::emph))
      {
         ret = process_block_no_style (**command.bodies.begin ());
      }
      else if (command.name == std::string (Token::link))
      {
         ret = process_block_no_style (**command.bodies.begin ());
      }
   }

   const ExpressionParagraph * paragraph_ptr = dynamic_cast <const ExpressionParagraph *> (&expression);

   if (paragraph_ptr != nullptr)
   {
      ret = process_block_no_style (*paragraph_ptr);
   }

   const ExpressionText * text_ptr = dynamic_cast <const ExpressionText *> (&expression);

   if (text_ptr != nullptr)
   {
      ret = text_ptr->body;
   }

   return ret;
}



/*
==============================================================================
Name : process_navigation
==============================================================================
*/

void  GeneratorHtml::process_navigation ()
{
   if (_html.empty ()) return;   // abort

   std::string url_prev = _toc.make_url_previous_chapter ();
   std::string url_next = _toc.make_url_next_chapter ();

   _html += "<div class=\"nav\" align=\"right\">\n";

   if (!url_prev.empty ())
   {
      _html += "<a href=\"" + url_prev + "\">previous</a>";
   }

   if ((!url_prev.empty ()) && (!url_next.empty ()))
   {
      _html += "<span>&nbsp;</span>";
   }

   if (!url_next.empty ())
   {
      _html += "<a href=\"" + url_next + "\">next</a>";
   }

   _html += "</div>\n\n";
}



/*
==============================================================================
Name : start
==============================================================================
*/

void  GeneratorHtml::start ()
{
   _html += "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"\n";
   _html += "  \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n";
   _html += "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\" dir=\"ltr\">\n\n";

   _html += "<head>\n";
   _html += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n";

   _html += "<title>" + _name_book + ": " + _name_chapter + "</title>\n";

   _html += "<style>\n";

   _html += "* {font-family: 'Lucida Grande', Helvetica, Arial, sans-serif; margin: 0; padding: 0; }\n";
   _html += "body {background-color: #fff; }\n";
   _html += "p {color: black; font-size: 13px; margin-bottom: 10px;}\n";
   _html += "h1 {color: black; font-size: 28px; margin-bottom: 32px; padding-top: 24px; font-weight: normal; display: block; }\n";
   _html += "h2 {color: #3c4c6c; display: block; font-size: 24px; font-weight: normal; margin-bottom: 20px; margin-top: 42px; border-bottom-color: #8391a8; border-bottom-style: solid; border-bottom-width: 1px;}\n";
   _html += "h3 {color: black; font-size: 19px; margin-bottom: 4px; margin-top: 28px; font-weight: normal; display: block; }\n";
   _html += "a {color: #36c; text-decoration: none; cursor:pointer; }\n";
   _html += "a:active {color: #36c; text-decoration: none; cursor:pointer; }\n";
   _html += "a:hover {color: #36c; text-decoration: underline; cursor:pointer; }\n";
   _html += ".aerr {color: #f00}\n";

   _html += "h2 a {color: #3c4c6c; text-decoration: none; cursor:auto; }\n";
   _html += "h2 a:active {color: #3c4c6c; text-decoration: none; cursor:auto; }\n";
   _html += "h2 a:hover {color: #3c4c6c; text-decoration: none; cursor:auto; }\n";

   _html += "h3 a {color: black; text-decoration: none; cursor:auto; }\n";
   _html += "h3 a:active {color: black; text-decoration: none; cursor:auto; }\n";
   _html += "h3 a:hover {color: black; text-decoration: none; cursor:auto; }\n";

   _html += "footer {font-size: 10px; position: fixed; display: block; bottom: 0px; background-color: #f1f5f9; border-top-color: #c7cfd5; border-top-style: solid; border-top-width: 1px; width: 100%; height:22px; padding-top: 7px; padding-left: 7px;}\n";
   _html += "div {display: block;}\n";
   _html += ".codeblock {margin-top:17px; margin-bottom:17px; clear: both; display: block; color: #333; }\n";
   _html += "pre {font-family: Courier, Consolas, monospace; font-size: 12px; height: 14px; line-height: 14px; margin-bottom: 0px; margin-left: 6px; margin-right: 4px; margin-top: -1px;}\n";
   _html += "small pre {color:#888;}\n";
   _html += "emph pre {color:#000;}\n";
   _html += "table {padding-top:5px; padding-bottom:6px; margin-bottom:12px; background-color: #f1f5f9; border-color: #c7cfd5; border-style: solid; border-width: 1px; width: 100%;}\n";
   _html += "tr {}\n";
   _html += "td > p {margin-left: 6px; height: 12px;}\n";

   _html += ".note {margin-top:21px; margin-bottom:22px; padding-left: 8px; padding-right: 8px; background-color: #fff; border-color: #5088c5; border-style: solid; border-width: 1px; display: block;}\n";
   _html += ".note strong {margin-right: 8px;}\n";
   _html += ".note p {margin-top: 7px;}\n";

   _html += ".important {margin-top:21px; margin-bottom:22px; padding-left: 8px; padding-right: 8px; background-color: #f1f5f9; border-color: #5088c5; border-style: solid; border-width: 1px; display: block;}\n";
   _html += ".important strong {margin-right: 8px;}\n";
   _html += ".important p {margin-top: 7px;}\n";

   _html += ".warning {margin-top:21px; margin-bottom:22px; padding-left: 8px; padding-right: 8px; background-color: #f8e3e1; border-color: #c5443e; border-style: solid; border-width: 1px; display: block;}\n";
   _html += ".warning strong {margin-right: 8px;}\n";
   _html += ".warning p {margin-top: 7px;}\n";

   _html += "img {margin-top:10px; margin-bottom:10px;}\n";

   _html += "ul {margin-left: 17px; margin-bottom: 10px;}\n";
   _html += "ol {margin-left: 17px; margin-bottom: 10px;}\n";
   _html += "li {color: black; font-size: 13px; margin-bottom: 7px;}\n";

   _html += "code {font-family: Courier, Consolas, monospace;}\n";

   _html += "#content {padding-left: 26px; padding-right: 26px; position: absolute; top: 30px; left: 30px; width: 750px;}\n";

   _html += "#toc {width: 230px; position: fixed; top: 30px; background-color: #f1f5f9; height: 100%; border-right-color: #c7cfd5; border-right-style: solid; border-right-width: 1px; padding-left: 0px; padding-top: 17px; overflow: auto;}\n";

   _html += "#toc > ul {list-style-type: none;}\n";
   _html += "#toc > ul > li {font-size: 11px; }\n";

   _html += "#toc > ul > li > ul {list-style-type: none; margin-top:8px;}\n";
   _html += "#toc > ul > li > ul > li {font-size: 11px; }\n";

   _html += "#toc > p {font-size: 13px; margin-left: 17px;}\n";

   _html += ".codeblock > p {margin-bottom: 3px; font-size: 11px;}\n";
   _html += ".codeblock > p > strong {margin-right: 10px; color: #222;}\n";

   _html += ".nav {font-size: 10px; margin-top: 20px; }\n";
   _html += ".nav > span {margin-right: 20px;}\n";

   _html += ".bottomspacer {height:100px;}\n";

   _html += "#header {width:100%; position: fixed; background-color: #111; height: 30px; z-index: 900;}\n";

   _html += "#header > p {color:#fff; font-size: 13px; padding-top: 6px; padding-left: 17px; }\n";
   _html += "#header > p > a {color:#fff; font-size: 13px; text-decoration: none; cursor:pointer; padding-right: 56px;}\n";

   _html += ".sectioncode {background-color: #f6f6f6; padding: 12px; margin-top: 18px;}\n";
   _html += ".sectioncode > h3 {margin-top: 0px; padding-bottom: 8px;}\n";

   _html += "</style>\n";
   _html += "</head>\n\n";

   _html += "<body>\n\n";

   _html += "<div id=\"content\">\n";
}



/*
==============================================================================
Name : flush
==============================================================================
*/

void  GeneratorHtml::flush ()
{
   if (_html.empty ()) return;   // abort

   _html += "<div class=\"bottomspacer\">&nbsp;</div>\n";

   _html += "</div>\n";
   _html += "</body>\n";
   _html += "</html>\n";

   if (_conf.output_path.empty ())
   {
      std::cout << _html;

      std::cout << "==========================\n\n";
   }
   else
   {
      std::string path;
      path += _conf.output_path + "/";

      if (_conf.format == Conf::Format::Html)
      {
         if (_cur_book.empty ())
         {
            path += "index.html";
         }
         else if (_cur_chapter.empty ())
         {
            path += _cur_book + "/index.html";
         }
         else
         {
            path += _cur_book + "/" + _cur_chapter + ".html";
         }
      }
      else if (_conf.format == Conf::Format::DocSet)
      {
         path += _cur_library + ".docset/Contents/Resources/Documents/";

         if (_cur_book.empty ())
         {
            path += "index.html";
         }
         else if (_cur_chapter.empty ())
         {
            path += _cur_book + "/index.html";
         }
         else
         {
            path += _cur_book + "/" + _cur_chapter + ".html";
         }
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
Name : make_plist
Reference :
   https://kapeli.com/docsets#dashDocset
==============================================================================
*/

void  GeneratorHtml::make_plist ()
{
   std::string path;
   path += _conf.output_path + "/";
   path += _cur_library + ".docset/Contents/Info.plist";

   make_dirs (path);

   std::string plist;

   plist += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
   plist += "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n";
   plist += "<plist version=\"1.0\">\n";
   plist += "<dict>\n";
   plist += "	<key>CFBundleIdentifier</key>\n";
   plist += "	<string>" + _cur_library + "</string>\n";
   plist += "	<key>CFBundleName</key>\n";
   plist += "	<string>" + _cur_library + "</string>\n";
   plist += "	<key>DocSetPlatformFamily</key>\n";
   plist += "	<string>" + _cur_library + "</string>\n";
   plist += "	<key>isDashDocset</key>\n";
   plist += "	<true/>\n";
   plist += "</dict>\n";
   plist += "</plist>\n";

   std::ofstream ofs (path, std::ifstream::binary);
   assert (ofs);

   ofs.write (&plist [0], int (plist.size ()));

   ofs.close ();
}



/*
==============================================================================
Name : make_index
Reference :
   https://kapeli.com/docsets#dashDocset
==============================================================================
*/

void  GeneratorHtml::make_index ()
{
   std::string path;
   path += _conf.output_path + "/";
   path += _cur_library + ".docset/Contents/Resources/docSet.dsidx";

   std::string cmd = "rm " + path;
   system (cmd.c_str ());

   sqlite3 * db_ptr = nullptr;

   int err = sqlite3_open (path.c_str (), &db_ptr);
   assert (err == 0);

   err = sqlite3_exec (db_ptr, "CREATE TABLE searchIndex(id INTEGER PRIMARY KEY, name TEXT, type TEXT, path TEXT);", nullptr, nullptr, nullptr);
   assert (err == 0);

   err = sqlite3_exec (db_ptr, "CREATE UNIQUE INDEX anchor ON searchIndex (name, type, path);", nullptr, nullptr, nullptr);
   assert (err == 0);

   for (auto && pair : _toc.guides ())
   {
      std::string expr;
      expr += "INSERT OR IGNORE INTO searchIndex(name, type, path) VALUES";
      expr += "('" + pair.first + "', 'Guide', '" + pair.second + "');";

      err = sqlite3_exec (db_ptr, expr.c_str (), nullptr, nullptr, nullptr);
      assert (err == 0);
   }

   for (auto && pair : _toc.classes ())
   {
      std::string expr;
      expr += "INSERT OR IGNORE INTO searchIndex(name, type, path) VALUES";
      expr += "('" + pair.first + "', 'Class', '" + pair.second + "');";

      err = sqlite3_exec (db_ptr, expr.c_str (), nullptr, nullptr, nullptr);
      assert (err == 0);
   }

   for (auto && pair : _toc.methods ())
   {
      std::string expr;
      expr += "INSERT OR IGNORE INTO searchIndex(name, type, path) VALUES";
      expr += "('" + pair.first + "', 'Method', '" + pair.second + "');";

      err = sqlite3_exec (db_ptr, expr.c_str (), nullptr, nullptr, nullptr);
      assert (err == 0);
   }

   sqlite3_close (db_ptr);
   db_ptr = 0;
}



/*
==============================================================================
Name : make_dirs
==============================================================================
*/

void  GeneratorHtml::make_dirs (const std::string & filepath)
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

std::string GeneratorHtml::make_id ()
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



/*
==============================================================================
Name : escape_xml
==============================================================================
*/

std::string GeneratorHtml::escape_xml (const std::string & txt)
{
   std::string ret;

   for (auto && c : txt)
   {
      if (c == '"')
      {
         ret += "&quot;";
      }
      else if (c == '&')
      {
         ret += "&amp;";
      }
      else if (c == '\'')
      {
         ret += "&apos;";
      }
      else if (c == '<')
      {
         ret += "&lt;";
      }
      else if (c == '>')
      {
         ret += "&gt;";
      }
      else
      {
         ret.push_back (c);
      }
   }

   return ret;
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

