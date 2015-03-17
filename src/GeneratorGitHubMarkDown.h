/*****************************************************************************

      GeneratorGitHubMarkDown.h
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

class GeneratorGitHubMarkDown
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  GeneratorGitHubMarkDown (const Conf & conf, Toc & toc);
   virtual        ~GeneratorGitHubMarkDown () = default;

   void           process (const Root & root);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           process (const Command & command);
   void           process (const List & list);
   void           process (const Table & table);
   void           process (const CodeBlock & codeblock);
   void           process (const Paragraph & paragraph);
   void           process_block (const Paragraph & paragraph);
   void           process_block (const Expression & expression);

   void           flush ();
   void           make_dirs (const std::string & filepath);
   std::string    make_id ();

   const Conf &   _conf;
   Toc &          _toc;

   std::string    _html;

   std::string    _cur_library;
   std::string    _cur_book;
   std::string    _cur_chapter;
   std::string    _cur_section;
   std::string    _cur_subsection;
   std::string    _cur_subsubsection;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  GeneratorGitHubMarkDown (const GeneratorGitHubMarkDown & rhs) = delete;
                  GeneratorGitHubMarkDown (GeneratorGitHubMarkDown && rhs) = delete;
   GeneratorGitHubMarkDown &
                  operator = (const GeneratorGitHubMarkDown & rhs) = delete;
   GeneratorGitHubMarkDown &
                  operator = (GeneratorGitHubMarkDown && rhs) = delete;
   bool           operator == (const GeneratorGitHubMarkDown & rhs);
   bool           operator != (const GeneratorGitHubMarkDown & rhs);



}; // class GeneratorGitHubMarkDown



}  // namespace otdgen



// #include "GeneratorGitHubMarkDown.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

