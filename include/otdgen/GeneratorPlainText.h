/*****************************************************************************

      GeneratorPlainText.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/DocInline.h"
#include "otdgen/DocMember.h"
#include "otdgen/DocParameter.h"
#include "otdgen/DocType.h"
#include "otdgen/GeneratorBase.h"

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

class GeneratorPlainText
:  public GeneratorBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  GeneratorPlainText (const Conf & conf, const Toc & toc);
   virtual        ~GeneratorPlainText () = default;

   void           process (const DocLibrary & library);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           process (std::vector <std::string> & cur, const DocBook & book);

   void           process (std::string & output, std::vector <std::string> & cur, const DocChapter & chapter);
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

   void           process_header (std::string & output, std::vector <std::string> & cur, const std::string & type, const DocInlines & title);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  GeneratorPlainText (const GeneratorPlainText & rhs) = delete;
                  GeneratorPlainText (GeneratorPlainText && rhs) = delete;
   GeneratorPlainText &
                  operator = (const GeneratorPlainText & rhs) = delete;
   GeneratorPlainText &
                  operator = (GeneratorPlainText && rhs) = delete;
   bool           operator == (const GeneratorPlainText & rhs);
   bool           operator != (const GeneratorPlainText & rhs);



}; // class GeneratorPlainText



}  // namespace otdgen



// #include "GeneratorPlainText.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

