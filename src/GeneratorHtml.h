/*****************************************************************************

      GeneratorHtml.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DocInline.h"
#include "DocMethod.h"
#include "DocParameter.h"
#include "DocType.h"
#include "GeneratorBase.h"

#include <string>
#include <vector>

#include "sqlite3.h"



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

class GeneratorHtml
:  public GeneratorBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  GeneratorHtml (const Conf & conf, Toc & toc);
   virtual        ~GeneratorHtml () = default;

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
   void           process (std::string & output, std::vector <std::string> & cur, const DocMethods & methods);

   void           process (std::string & output, std::vector <std::string> & cur, const DocInlines & inlines);
   std::string    make_href (const std::vector <std::string> & cur, const std::string & id);
   std::string    process_no_style (const DocInlines & inlines);

   void           process_nav (std::string & output, const DocChapter & chapter);

   void           process_header (std::string & output, const std::string & title);
   void           process_footer (std::string & output);

   void           make_plist (const DocLibrary & library);
   void           open_index (const DocLibrary & library);
   void           add_index (std::string name, std::string type, std::string path);
   void           close_index ();
   std::string    escape_xml (const std::string & txt);
   std::string    escape_pourcent (const std::string & txt);

   sqlite3 *      _db_ptr = nullptr;



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

