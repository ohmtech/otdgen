/*****************************************************************************

      GeneratorGitHubMarkDown.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DocInline.h"
#include "DocMember.h"
#include "DocParameter.h"
#include "DocType.h"
#include "GeneratorBase.h"

#include <string>
#include <vector>



namespace otdgen
{



class Conf;
class DocBlocks;
class DocBook;
class DocCartouche;
class DocChapter;
class DocCodeBlock;
class DocInformation;
class DocLibrary;
class DocList;
class DocParagraph;
class DocSection;
class DocTable;

class GeneratorGitHubMarkDown
:  public GeneratorBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  GeneratorGitHubMarkDown (const Conf & conf, const Toc & toc);
   virtual        ~GeneratorGitHubMarkDown () = default;

   void           process (const DocLibrary & library);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           process (std::vector <std::string> & cur, const DocBook & book);
   void           process (std::vector <std::string> & cur, const DocChapter & chapter);

   void           process (std::string & output, std::vector <std::string> & cur, const DocBlocks & blocks);
   void           process (std::string & output, std::vector <std::string> & cur, const DocSection & section);
   void           process (std::string & output, std::vector <std::string> & cur, const DocInformation & information);
   void           process (std::string & output, std::vector <std::string> & cur, const DocList & list);
   void           process (std::string & output, std::vector <std::string> & cur, const DocTable & table);
   void           process (std::string & output, std::vector <std::string> & cur, const DocCodeBlock & codeblock);
   void           process (std::string & output, std::vector <std::string> & cur, const DocParagraph & paragraph);
   void           process (std::string & output, std::vector <std::string> & cur, const DocCartouche & cartouche);
   void           process (std::string & output, std::vector <std::string> & cur, const DocParameters & parameters);
   void           process (std::string & output, std::vector <std::string> & cur, const DocTypes & types);
   void           process (std::string & output, std::vector <std::string> & cur, const DocMembers & members);

   void           process (std::string & output, std::vector <std::string> & cur, const DocInlines & inlines);
   std::string    make_href (const std::vector <std::string> & cur, const std::string & id);

   void           process_nav (std::string & output, const DocChapter & chapter);



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

