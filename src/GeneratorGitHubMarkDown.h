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



class GeneratorGitHubMarkDown
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  GeneratorGitHubMarkDown () = default;
   virtual        ~GeneratorGitHubMarkDown () = default;

   std::string    process (const Root & root);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           process (std::string & html, const Command & command);
   void           process (std::string & html, const List & list);
   void           process (std::string & html, const Table & table);
   void           process (std::string & html, const CodeBlock & codeblock);
   void           process (std::string & html, const Paragraph & paragraph);
   void           process_block (std::string & html, const Paragraph & paragraph);
   void           process_block (std::string & html, const Expression & expression);



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

