/*****************************************************************************

      StructuralAnalyser.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "StructuralAnalyser.h"

#include "DocCodeBlock.h"
#include "DocInformation.h"
#include "DocList.h"
#include "DocParagraph.h"
#include "DocSection.h"
#include "DocTable.h"
#include "Expression.h"
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

DocLibrary  StructuralAnalyser::process (const ExpressionRoot & root)
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

   post_process (_library);

   return _library;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
==============================================================================
*/

void  StructuralAnalyser::process (const ExpressionCommand & command)
{
   const ExpressionParagraph & paragraph
      = dynamic_cast <const ExpressionParagraph &> (**command.bodies.begin ());

   if (command.name == std::string (Token::library))
   {
      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _library.id = it->second;

      _inlines_ptr = &_library.title;
      process_block (paragraph);
      _inlines_ptr = nullptr;

      _blocks_ptr = &_library.overview;
   }
   else if (command.name == std::string (Token::book))
   {
      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      DocBook::Type type = DocBook::Type::Reference;
      {
         auto it_type = command.options.find ("type");
         if (it_type != command.options.end ())
         {
            auto && type_str = it_type->second;

            if (type_str == "overview")
            {
               type = DocBook::Type::Overview;
            }
            else if (type_str == "guide")
            {
               type = DocBook::Type::Guide;
            }
             else if (type_str == "reference")
            {
               type = DocBook::Type::Reference;
            }
             else if (type_str == "sample")
            {
               type = DocBook::Type::Sample;
            }
             else if (type_str == "technote")
            {
               type = DocBook::Type::TechnicalNote;
            }
         }
      }

      _book_ptr = &*_library.books.emplace (_library.books.end ());
      _book_ptr->type = type;
      _book_ptr->id = it->second;
      _chapter_ptr = nullptr;

      _inlines_ptr = &_book_ptr->title;
      process_block (paragraph);
      _inlines_ptr = nullptr;

      _blocks_ptr = &_book_ptr->overview;
   }
   else if (command.name == std::string (Token::chapter))
   {
      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _chapter_ptr = &*_book_ptr->chapters.emplace (_book_ptr->chapters.end ());
      _chapter_ptr->id = it->second;

      _inlines_ptr = &_chapter_ptr->title;
      process_block (paragraph);
      _inlines_ptr = nullptr;

      _blocks_ptr = &_chapter_ptr->blocks;
   }
   else if (command.name == std::string (Token::section))
   {
      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      DocSection & block = dynamic_cast <DocSection &> (**_blocks_ptr->_content.insert (
         _blocks_ptr->_content.end (), std::make_shared <DocSection> ()
      ));
      block.level = DocSection::Level::Section;

      _cur_section = it->second;
      _cur_subsection.clear ();
      _cur_subsubsection.clear ();

      block.id = _cur_section;
      block.id_sub = _cur_subsection;
      block.id_subsub = _cur_subsubsection;

      _inlines_ptr = &block.title;
      process_block (paragraph);
      _inlines_ptr = nullptr;
   }
   else if (command.name == std::string (Token::subsection))
   {
      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      DocSection & block = dynamic_cast <DocSection &> (**_blocks_ptr->_content.insert (
         _blocks_ptr->_content.end (), std::make_shared <DocSection> ()
      ));
      block.level = DocSection::Level::SubSection;

      _cur_subsection = it->second;
      _cur_subsubsection.clear ();

      block.id = _cur_section;
      block.id_sub = _cur_subsection;
      block.id_subsub = _cur_subsubsection;

      _inlines_ptr = &block.title;
      process_block (paragraph);
      _inlines_ptr = nullptr;
   }
   else if (command.name == std::string (Token::subsubsection))
   {
      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      DocSection & block = dynamic_cast <DocSection &> (**_blocks_ptr->_content.insert (
         _blocks_ptr->_content.end (), std::make_shared <DocSection> ()
      ));
      block.level = DocSection::Level::SubSubSection;

      _cur_subsubsection = it->second;

      block.id = _cur_section;
      block.id_sub = _cur_subsection;
      block.id_subsub = _cur_subsubsection;

      _inlines_ptr = &block.title;
      process_block (paragraph);
      _inlines_ptr = nullptr;
   }
   else if (command.name == std::string (Token::note))
   {
      DocInformation & block = dynamic_cast <DocInformation &> (**_blocks_ptr->_content.insert (
         _blocks_ptr->_content.end (), std::make_shared <DocInformation> ()
      ));
      block.level = DocInformation::Level::Note;

      _inlines_ptr = &block.body;
      process_block (paragraph);
      _inlines_ptr = nullptr;
   }
   else if (command.name == std::string (Token::important))
   {
      DocInformation & block = dynamic_cast <DocInformation &> (**_blocks_ptr->_content.insert (
         _blocks_ptr->_content.end (), std::make_shared <DocInformation> ()
      ));
      block.level = DocInformation::Level::Important;

      _inlines_ptr = &block.body;
      process_block (paragraph);
      _inlines_ptr = nullptr;
   }
   else if (command.name == std::string (Token::warning))
   {
      DocInformation & block = dynamic_cast <DocInformation &> (**_blocks_ptr->_content.insert (
         _blocks_ptr->_content.end (), std::make_shared <DocInformation> ()
      ));
      block.level = DocInformation::Level::Warning;

      _inlines_ptr = &block.body;
      process_block (paragraph);
      _inlines_ptr = nullptr;
   }
   else if (command.name == std::string (Token::namespace_))
   {
      _book_ptr->namespace_ = process_block_no_style (paragraph);
   }
   else if (command.name == std::string (Token::class_))
   {
      std::string name = process_block_no_style (paragraph);

      _chapter_ptr = &*_book_ptr->chapters.emplace (_book_ptr->chapters.end ());
      _chapter_ptr->id = name;
      _chapter_ptr->type = DocChapter::Type::Class;

      auto & inlinee = *_chapter_ptr->title.emplace (_chapter_ptr->title.end ());
      inlinee.type = DocInline::Type::Text;
      inlinee.text = name + " Class Reference";

      _chapter_ptr->name = name;

      _blocks_ptr = &_chapter_ptr->blocks;
   }
   else if (command.name == std::string (Token::inherit))
   {
      _chapter_ptr->cartouche.inherit = process_block_no_style (paragraph);
   }
   else if (command.name == std::string (Token::header))
   {
      _chapter_ptr->cartouche.header = process_block_no_style (paragraph);
   }
   else if (command.name == std::string (Token::guide))
   {
      auto it = command.options.find ("id");
      assert (it != command.options.end ());

      _chapter_ptr->cartouche.guide_id = it->second;

      _inlines_ptr = &_chapter_ptr->cartouche.guide;
      process_block (paragraph);
      _inlines_ptr = nullptr;
   }
   else if (command.name == std::string (Token::declaration))
   {
      _chapter_ptr->cartouche.declaration = process_block_no_style (paragraph);
   }
   else if (command.name == std::string (Token::parameter))
   {
      auto & param = *_chapter_ptr->parameters.emplace (_chapter_ptr->parameters.end ());

      param.type = process_block_no_style (paragraph);

      auto it = command.bodies.begin ();
      ++it;
      assert (it != command.bodies.end ());

      const ExpressionParagraph & paragraph2
         = dynamic_cast <const ExpressionParagraph &> (**it);

      _inlines_ptr = &param.body;
      process_block (paragraph2);
      _inlines_ptr = nullptr;
   }
   else if (command.name == std::string (Token::type))
   {
      auto & type = *_chapter_ptr->types.emplace (_chapter_ptr->types.end ());

      {
         auto it = command.options.find ("id");
         if (it != command.options.end ())
         {
            type.id = it->second;
         }
      }

      type.type = process_block_no_style (paragraph);

      auto it = command.bodies.begin ();
      ++it;
      assert (it != command.bodies.end ());

      const ExpressionParagraph & paragraph2
         = dynamic_cast <const ExpressionParagraph &> (**it);

      _inlines_ptr = &type.body;
      process_block (paragraph2);
      _inlines_ptr = nullptr;
   }
   else if (command.name == std::string (Token::constructor))
   {
      auto & method = *_chapter_ptr->methods.emplace (_chapter_ptr->methods.end ());
      method.type = DocMethod::Type::Constructor;

      _method_ptr = &method;
      _blocks_ptr = &_method_ptr->description;
   }
   else if (command.name == std::string (Token::destructor))
   {
      auto & method = *_chapter_ptr->methods.emplace (_chapter_ptr->methods.end ());
      method.type = DocMethod::Type::Destructor;

      _method_ptr = &method;
      _blocks_ptr = &_method_ptr->description;
   }
   else if (command.name == std::string (Token::method))
   {
      auto & method = *_chapter_ptr->methods.emplace (_chapter_ptr->methods.end ());
      method.type = DocMethod::Type::Function;
      method.name = process_block_no_style (paragraph);

      _method_ptr = &method;
      _blocks_ptr = &_method_ptr->description;
   }
   else if (command.name == std::string (Token::brief))
   {
      _inlines_ptr = &_method_ptr->brief;
      process_block (paragraph);
      _inlines_ptr = nullptr;
   }
   else if (command.name == std::string (Token::division))
   {
      auto & method = *_chapter_ptr->methods.emplace (_chapter_ptr->methods.end ());
      method.type = DocMethod::Type::Division;

      _inlines_ptr = &method.brief;
      process_block (paragraph);
      _inlines_ptr = nullptr;
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  StructuralAnalyser::process (const ExpressionList & list)
{
   DocList & block = dynamic_cast <DocList &> (**_blocks_ptr->_content.insert (
      _blocks_ptr->_content.end (), std::make_shared <DocList> ()
   ));

   if (list.type == ExpressionList::Type::Itemize)
   {
      block.type = DocList::Type::Itemization;
   }
   else if (list.type == ExpressionList::Type::Enumerate)
   {
      block.type = DocList::Type::Enumeration;
   }

   for (auto && item : list.items)
   {
      const auto & expression = *item;

      const auto & paragraph = dynamic_cast <const ExpressionParagraph &> (expression);

      DocInlines & doc_item = *block.items.emplace (block.items.end ());

      _inlines_ptr = &doc_item;
      process_block (paragraph);
      _inlines_ptr = nullptr;
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  StructuralAnalyser::process (const ExpressionTable & table)
{
   DocTable & block = dynamic_cast <DocTable &> (**_blocks_ptr->_content.insert (
      _blocks_ptr->_content.end (), std::make_shared <DocTable> ()
   ));

   for (auto && row_uptr : table.rows)
   {
      const auto & row = dynamic_cast <const ExpressionRow &> (*row_uptr);

      auto & doc_row = *block.rows.emplace (block.rows.end ());

      for (auto && cell_uptr : row.cells)
      {
         const auto & paragraph = dynamic_cast <const ExpressionParagraph &> (*cell_uptr);

         DocInlines & doc_cell = *doc_row.emplace (doc_row.end ());

         _inlines_ptr = &doc_cell;
         process_block (paragraph);
         _inlines_ptr = nullptr;
      }
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  StructuralAnalyser::process (const ExpressionCodeBlock & codeblock)
{
   DocCodeBlock & block = dynamic_cast <DocCodeBlock &> (**_blocks_ptr->_content.insert (
      _blocks_ptr->_content.end (), std::make_shared <DocCodeBlock> ()
   ));

   block.type = DocCodeBlock::Type::None;

   auto it = codeblock.options.find ("language");

   if (it != codeblock.options.end ())
   {
      if (it->second == "c++")
      {
         block.type = DocCodeBlock::Type::Cpp;
      }
   }

   for (auto && line : codeblock.lines)
   {
      auto & pair = *block.lines.emplace (block.lines.end ());

      pair.first = line.first;

      switch (line.second)
      {
      case ExpressionCodeBlock::Style::Normal:
         pair.second = DocCodeBlock::LineType::Normal;
         break;

      case ExpressionCodeBlock::Style::Emph:
         pair.second = DocCodeBlock::LineType::Emphasis;
         break;

      case ExpressionCodeBlock::Style::Fade:
         pair.second = DocCodeBlock::LineType::Fade;
         break;
      }
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  StructuralAnalyser::process (const ExpressionParagraph & paragraph)
{
   DocParagraph & block = dynamic_cast <DocParagraph &> (**_blocks_ptr->_content.insert (
      _blocks_ptr->_content.end (), std::make_shared <DocParagraph> ()
   ));

   _inlines_ptr = &block.body;
   process_block (paragraph);
   _inlines_ptr = nullptr;
}



/*
==============================================================================
Name : process_block
==============================================================================
*/

void  StructuralAnalyser::process_block (const ExpressionParagraph & paragraph)
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

void  StructuralAnalyser::process_block (const Expression & expression)
{
   const ExpressionCommand * command_ptr = dynamic_cast <const ExpressionCommand *> (&expression);

   if (command_ptr != nullptr)
   {
      const ExpressionCommand & command = *command_ptr;

      if (command.name == std::string (Token::code))
      {
         DocInlines * cur_inlines_ptr = _inlines_ptr;
         auto & inlinee = *_inlines_ptr->emplace (_inlines_ptr->end ());
         inlinee.type = DocInline::Type::Code;

         _inlines_ptr = &inlinee.node;
         process_block (**command.bodies.begin ());
         _inlines_ptr = cur_inlines_ptr;
      }
      else if (command.name == std::string (Token::emph))
      {
         DocInlines * cur_inlines_ptr = _inlines_ptr;
         auto & inlinee = *_inlines_ptr->emplace (_inlines_ptr->end ());
         inlinee.type = DocInline::Type::Emphasis;

         _inlines_ptr = &inlinee.node;
         process_block (**command.bodies.begin ());
         _inlines_ptr = cur_inlines_ptr;
      }
      else if (command.name == std::string (Token::link))
      {
         DocInlines * cur_inlines_ptr = _inlines_ptr;
         auto & inlinee = *_inlines_ptr->emplace (_inlines_ptr->end ());

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
            inlinee.type = DocInline::Type::LinkId;
            inlinee.meta = ide;
         }
         else if (!href.empty ())
         {
            inlinee.type = DocInline::Type::LinkUrl;
            inlinee.meta = href;
         }

         _inlines_ptr = &inlinee.node;
         process_block (**command.bodies.begin ());
         _inlines_ptr = cur_inlines_ptr;
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
      auto & inlinee = *_inlines_ptr->emplace (_inlines_ptr->end ());
      inlinee.type = DocInline::Type::Text;
      inlinee.text = text_ptr->body;
   }
}



/*
==============================================================================
Name : process_block_no_style
==============================================================================
*/

std::string StructuralAnalyser::process_block_no_style (const ExpressionParagraph & paragraph)
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

std::string StructuralAnalyser::process_block_no_style (const Expression & expression)
{
   const ExpressionCommand * command_ptr = dynamic_cast <const ExpressionCommand *> (&expression);

   if (command_ptr != nullptr)
   {
      const ExpressionCommand & command = *command_ptr;

      if (command.name == std::string (Token::code))
      {
         return process_block_no_style (**command.bodies.begin ());
      }
      else if (command.name == std::string (Token::emph))
      {
         return process_block_no_style (**command.bodies.begin ());
      }
      else if (command.name == std::string (Token::link))
      {
         return process_block_no_style (**command.bodies.begin ());
      }
   }

   const ExpressionParagraph * paragraph_ptr = dynamic_cast <const ExpressionParagraph *> (&expression);

   if (paragraph_ptr != nullptr)
   {
      return process_block_no_style (*paragraph_ptr);
   }

   const ExpressionText * text_ptr = dynamic_cast <const ExpressionText *> (&expression);

   if (text_ptr != nullptr)
   {
      return text_ptr->body;
   }

   return "";
}



/*
==============================================================================
Name : post_process
==============================================================================
*/

void  StructuralAnalyser::post_process (DocLibrary & library)
{
   post_process (library.overview);

   const auto it_begin = library.books.begin ();
   const auto it_end = library.books.end ();
   auto it = it_begin;

   for (; it != it_end ; ++it)
   {
      auto it_next = it;
      ++it_next;

      auto & book = *it;
      book.parent_ptr = &library;

      if (it != it_begin)
      {
         auto it_prev = it;
         --it_prev;

         book.previous_ptr = &*it_prev;
      }

      if (it_next != it_end)
      {
         book.next_ptr = &*it_next;
      }

      post_process (book);
   }
}



/*
==============================================================================
Name : post_process
==============================================================================
*/

void  StructuralAnalyser::post_process (DocBook & book)
{
   post_process (book.overview);

   const auto it_begin = book.chapters.begin ();
   const auto it_end = book.chapters.end ();
   auto it = it_begin;

   for (; it != it_end ; ++it)
   {
      auto it_next = it;
      ++it_next;

      auto & chapter = *it;
      chapter.parent_ptr = &book;

      if (it != it_begin)
      {
         auto it_prev = it;
         --it_prev;

         chapter.previous_ptr = &*it_prev;
      }

      if (it_next != it_end)
      {
         chapter.next_ptr = &*it_next;
      }

      post_process (chapter);
   }
}



/*
==============================================================================
Name : post_process
==============================================================================
*/

void  StructuralAnalyser::post_process (DocChapter & chapter)
{
   post_process (chapter.blocks);
   post_process (chapter.methods);
}



/*
==============================================================================
Name : post_process
==============================================================================
*/

void  StructuralAnalyser::post_process (DocBlocks & blocks)
{
   for (auto && block_sptr : blocks._content)
   {
      auto & block = *block_sptr;

      if (dynamic_cast <DocSection *> (&block) != nullptr)
      {
         block.type = DocBlock::Type::Section;
      }
      else if (dynamic_cast <DocInformation *> (&block) != nullptr)
      {
         block.type = DocBlock::Type::Information;
      }
      else if (dynamic_cast <DocList *> (&block) != nullptr)
      {
         block.type = DocBlock::Type::List;
      }
      else if (dynamic_cast <DocTable *> (&block) != nullptr)
      {
         block.type = DocBlock::Type::Table;
      }
      else if (dynamic_cast <DocCodeBlock *> (&block) != nullptr)
      {
         block.type = DocBlock::Type::CodeBlock;
      }
      else if (dynamic_cast <DocParagraph *> (&block) != nullptr)
      {
         block.type = DocBlock::Type::Paragraph;
      }
      else
      {
         assert (false);
      }
   }
}



/*
==============================================================================
Name : post_process
==============================================================================
*/

void  StructuralAnalyser::post_process (DocMethods & methods)
{
   for (auto && method : methods)
   {
      post_process (method.description);
   }
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

