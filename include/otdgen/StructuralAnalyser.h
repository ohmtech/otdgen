/*****************************************************************************

      StructuralAnalyser.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/DocLibrary.h"



namespace otdgen
{



class Expression;
class ExpressionCodeBlock;
class ExpressionCommand;
class ExpressionList;
class ExpressionParagraph;
class ExpressionTable;
class ExpressionRoot;

class StructuralAnalyser
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  StructuralAnalyser () = default;
   virtual        ~StructuralAnalyser () = default;

   DocLibrary     process (const ExpressionRoot & root);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   void           process (const ExpressionCommand & command);
   void           process (const ExpressionList & list);
   void           process (const ExpressionTable & table);
   void           process (const ExpressionCodeBlock & codeblock);
   void           process (const ExpressionParagraph & paragraph);

   void           process_block (const ExpressionParagraph & paragraph);
   void           process_block (const Expression & expression);

   std::string    process_block_no_style (const ExpressionParagraph & paragraph);
   std::string    process_block_no_style (const Expression & expression);

   void           post_process (DocLibrary & library);
   void           post_process (DocBook & book);
   void           post_process (DocChapter & chapter);
   void           post_process (DocBlocks & blocks);
   void           post_process (DocMembers & members);

   DocLibrary     _library;
   DocBook *      _book_ptr = nullptr;
   DocChapter *   _chapter_ptr = nullptr;

   DocInlines *   _inlines_ptr = nullptr;
   DocBlocks *    _blocks_ptr = nullptr;
   DocMember *    _member_ptr = nullptr;

   std::string    _cur_section;
   std::string    _cur_subsection;
   std::string    _cur_subsubsection;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  StructuralAnalyser (const StructuralAnalyser & rhs) = delete;
                  StructuralAnalyser (StructuralAnalyser && rhs) = delete;
   StructuralAnalyser &
                  operator = (const StructuralAnalyser & rhs) = delete;
   StructuralAnalyser &
                  operator = (StructuralAnalyser && rhs) = delete;
   bool           operator == (const StructuralAnalyser & rhs);
   bool           operator != (const StructuralAnalyser & rhs);



}; // class StructuralAnalyser



}  // namespace otdgen



// #include "StructuralAnalyser.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

