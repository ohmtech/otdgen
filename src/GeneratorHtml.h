/*****************************************************************************

      GeneratorHtml.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Expression.h"

#include <string>



namespace otdgen
{



class Conf;
class Toc;

class GeneratorHtml
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  GeneratorHtml (const Conf & conf, Toc & toc);
   virtual        ~GeneratorHtml () = default;

   void           process (const ExpressionRoot & root);



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

   void           process_navigation ();

   void           start ();
   void           flush ();
   void           make_plist ();
   void           make_index ();
   void           make_dirs (const std::string & filepath);
   std::string    make_id ();
   std::string    escape_xml (const std::string & txt);

   const Conf &   _conf;
   Toc &          _toc;

   std::string    _html;

   std::string    _cur_library;
   std::string    _cur_book;
   std::string    _cur_chapter;
   std::string    _cur_section;
   std::string    _cur_subsection;
   std::string    _cur_subsubsection;

   std::string    _name_book;
   std::string    _name_chapter;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  GeneratorHtml (const GeneratorHtml & rhs) = delete;
                  GeneratorHtml (GeneratorHtml && rhs) = delete;
   GeneratorHtml &
                  operator = (const GeneratorHtml & rhs) = delete;
   GeneratorHtml &
                  operator = (GeneratorHtml && rhs) = delete;
   bool           operator == (const GeneratorHtml & rhs);
   bool           operator != (const GeneratorHtml & rhs);



}; // class GeneratorHtml



}  // namespace otdgen



// #include "GeneratorHtml.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

