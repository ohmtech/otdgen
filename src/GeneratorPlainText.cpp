/*****************************************************************************

      GeneratorPlainText.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/GeneratorPlainText.h"

#include "otdgen/Conf.h"
#include "otdgen/DocBlocks.h"
#include "otdgen/DocBook.h"
#include "otdgen/DocChapter.h"
#include "otdgen/DocCodeBlock.h"
#include "otdgen/DocInformation.h"
#include "otdgen/DocLibrary.h"
#include "otdgen/DocList.h"
#include "otdgen/DocParagraph.h"
#include "otdgen/DocSection.h"
#include "otdgen/DocTable.h"
#include "otdgen/Toc.h"

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

GeneratorPlainText::GeneratorPlainText (const Conf & conf, const Toc & toc)
:  GeneratorBase (conf, toc)
{
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (const DocLibrary & library)
{
   std::vector <std::string> cur;
   cur.push_back (library.id);

   // overview

   std::string output;

   process_header (output, cur, "Library", library.title);
   process (output, cur, library.overview);

   write (library.id + ".txt", output);

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

void  GeneratorPlainText::process (std::vector <std::string> & cur, const DocBook & book)
{
   cur.push_back (book.id);

   // overview

   std::string output;

   process_header (output, cur, "Book", book.title);
   process (output, cur, book.overview);

   // chapters

   for (auto && chapter : book.chapters)
   {
      process (output, cur, chapter);
   }

   write (book.id + ".txt", output);

   cur.resize (1);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & cur, const DocChapter & chapter)
{
   cur.push_back (chapter.id);

   process_header (output, cur, "Chapter", chapter.title);

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

   cur.resize (2);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & cur, const DocBlocks & blocks)
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

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & cur, const DocSection & section)
{
   switch (section.level)
   {
   case DocSection::Level::Section:
      cur.resize (3);
      cur.push_back (section.id);
      process_header (output, cur, "Section", section.title);
      break;

   case DocSection::Level::SubSection:
      cur.resize (4);
      cur.push_back (section.id_sub);
      output += "--- ";
      process (output, cur, section.title);
      output += " ---\n\n";
      break;

   case DocSection::Level::SubSubSection:
      cur.resize (5);
      cur.push_back (section.id_subsub);
      output += "---- ";
      process (output, cur, section.title);
      output += " ----\n\n";
      break;
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & cur, const DocInformation & information)
{
   switch (information.level)
   {
   case DocInformation::Level::Note:
      output += "Note: ";
      process (output, cur, information.body);
      output += "\n\n";
      break;

   case DocInformation::Level::Important:
      output += "Important: ";
      process (output, cur, information.body);
      output += "\n\n";
      break;

   case DocInformation::Level::Warning:
      output += "Warning: ";
      process (output, cur, information.body);
      output += "\n\n";
      break;
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & cur, const DocList & list)
{
   for (auto && item : list.items)
   {
      output += "- ";
      process (output, cur, item);
      output += "\n";
   }

   output += "\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & cur, const DocTable & table)
{
   const size_t repetitions = 57;

   output += '|' + std::string (repetitions, '-') + "|\n";

   for (auto && row : table.rows)
   {
      output += "| ";

      for (auto && cell : row)
      {
         process (output, cur, cell);
         output += " | ";
      }

      output += "\n";
   }

   output += '|' + std::string (repetitions, '-') + "|\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & /* cur */, const DocCodeBlock & codeblock)
{
   const size_t repetitions = 59;

   output += std::string (repetitions, '*');

   switch (codeblock.type)
   {
   case DocCodeBlock::Type::None:
      output += " code (unspecified language): \n";
      break;

   case DocCodeBlock::Type::Cpp:
      output += " code (c++): \n";
      break;
   }

   for (auto && line : codeblock.lines)
   {
      output += line.first + "\n";
   }

   output += std::string (repetitions, '*') + "\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & cur, const DocParagraph & paragraph)
{
   process (output, cur, paragraph.body);

   output += "\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & cur, const DocCartouche & cartouche)
{
   if (!cartouche.inherit.empty ())
   {
      output += "Inherits from: ";
      output += escape_xml (cartouche.inherit);
      output += "\n";
   }

   if (!cartouche.header.empty ())
   {
      output += "Declared in: ";
      output += escape_xml (cartouche.header);
      output += "\n";
   }

   if (!cartouche.guide_id.empty ())
   {
      output += "Companion Guide: ";
      process (output, cur, cartouche.guide);
      output += "\n";
   }

   output += "\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & cur, const DocParameters & parameters)
{
   if (parameters.empty ()) return; // abort

   output += "-- Template Parameters --\n\n";

   for (auto && parameter : parameters)
   {
      output += "- " + escape_xml (parameter.type) + ": ";
      process (output, cur, parameter.body);
      output += "\n";
   }

   output += "\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & cur, const DocTypes & types)
{
   if (types.empty ()) return; // abort

   output += "-- Member Types --\n\n";

   for (auto && type : types)
   {
      output += "- " + escape_xml (type.type) + ": ";
      process (output, cur, type.body);
      output += "\n";
   }

   output += "\n\n";
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & cur, const DocMembers & members)
{
   bool in_table_flag = false;

   enum class State
   {
      None,
      Methods,
      Variables,
      Functions,
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
            output += "\n\n";
         }

         state = target;

         switch (target)
         {
         case State::Methods:
            output += "-- Member Functions Synopsys --\n\n";
            break;

         case State::Variables:
            output += "-- Member Variables Synopsys --\n\n";
            break;

         case State::Functions:
            output += "-- Non-member Functions Synopsys --\n\n";
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
      }
   };

   for (auto && member : members)
   {
      if (member.type == DocMember::Type::Constructor)
      {
         adjust_state (State::Methods);

         output += "Constructor: ";
         process (output, cur, member.brief);
         output += "\n";
      }
      else if (member.type == DocMember::Type::Destructor)
      {
         adjust_state (State::Methods);

         output += "Destructor: ";
         process (output, cur, member.brief);
         output += "\n";
      }
      else if (member.type == DocMember::Type::Method)
      {
         adjust_state (State::Methods);

         output += "- " + escape_xml (member.name) + ": ";;
         process (output, cur, member.brief);
         output += "\n";
      }
      else if (member.type == DocMember::Type::Variable)
      {
         adjust_state (State::Variables);

         output += "- " + escape_xml (member.name) + ": ";;
         process (output, cur, member.brief);
         output += "\n";
      }
      else if (member.type == DocMember::Type::Function)
      {
         adjust_state (State::Functions);

         output += "- " + escape_xml (member.name) + ": ";
         process (output, cur, member.brief);
         output += "\n";
      }
      else if (member.type == DocMember::Type::Division)
      {
         if (in_table_flag)
         {
            in_table_flag = false;
         }

         division += "\n\n--- ";
         process (division, cur, member.brief);
         division += " ---\n\n";

         if (state != State::None)
         {
            output += division;
            division.clear ();
         }
      }
   }

   if (in_table_flag)
   {
      output += "\n\n";
   }

   // details

   state = State::None;

   for (auto && member : members)
   {
      if (member.type == DocMember::Type::Division) continue;

      if (member.type == DocMember::Type::Constructor)
      {
         if (state != State::Methods)
         {
            output += "-- Member Functions --\n\n";

            state = State::Methods;
         }

         output += "--- Constructor ---\n\n";
      }
      else if (member.type == DocMember::Type::Destructor)
      {
         if (state != State::Methods)
         {
            output += "-- Member Functions --\n\n";

            state = State::Methods;
         }

         output += "--- Destructor ---\n\n";
      }
      else if (member.type == DocMember::Type::Method)
      {
         if (state != State::Methods)
         {
            output += "-- Member Functions --\n\n";

            state = State::Methods;
         }

         output += "- " + escape_xml (member.name) + "\n\n";
      }
      else if (member.type == DocMember::Type::Variable)
      {
         if (state != State::Variables)
         {
            output += "-- Member Variables --\n\n";

            state = State::Variables;
         }

         output += "- " + escape_xml (member.name) + "\n\n";
      }
      else if (member.type == DocMember::Type::Function)
      {
         if (state != State::Functions)
         {
            output += "-- Non-member Functions --\n\n";

            state = State::Functions;
         }

         output += "- " + escape_xml (member.name) + "\n\n";
      }

      process (output, cur, member.description);
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  GeneratorPlainText::process (std::string & output, std::vector <std::string> & cur, const DocInlines & inlines)
{
   for (auto && inlinee : inlines)
   {
      switch (inlinee.type)
      {
      case DocInline::Type::Text:
         output += inlinee.text;
         break;

      case DocInline::Type::Emphasis:
         process (output, cur, inlinee.node);
         break;

      case DocInline::Type::Code:
         process (output, cur, inlinee.node);
         break;

      case DocInline::Type::LinkId:
         process (output, cur, inlinee.node);
         break;

      case DocInline::Type::LinkUrl:
         process (output, cur, inlinee.node);
         break;

      case DocInline::Type::Image:
         output += "[Image";
         auto image_path = inlinee.meta;
         if (!image_path.empty ())
         {
            auto name = image_path.substr(image_path.find_last_of("/\\") + 1);
            output += ": " + name;
         }
         output += "]";
         break;
      }
   }
}



/*
==============================================================================
Name : process_header
==============================================================================
*/

void  GeneratorPlainText::process_header (std::string & output, std::vector <std::string> & cur, const std::string & type, const DocInlines & title)
{
   assert (cur.size () > 0);

   const size_t max_char_repetitions = 89;
   const auto head_char = '-';

   auto breadcrumb = [] (std::vector <std::string> & cur) {
      std::string out;
      for (auto it = cur.begin (); it != cur.end () - 1; ++it)
      {
         out += *it + " > ";
      }
      out += *(cur.rbegin());
      return out;
   };

   const size_t ntimes = max_char_repetitions - (cur.size () * 10);

   output += std::string (ntimes, head_char) + "\n ";

   output += type + ": " + breadcrumb (cur) + "\n ";

   process (output, cur, title);

   output += "\n" + std::string (ntimes, head_char) + "\n\n";
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
