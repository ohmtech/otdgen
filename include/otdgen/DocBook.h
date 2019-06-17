/*****************************************************************************

      DocBook.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/DocBlock.h"
#include "otdgen/DocChapter.h"
#include "otdgen/DocInline.h"

#include <list>
#include <string>



namespace otdgen
{



class DocLibrary;

class DocBook
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Type
   {
                  Overview,
                  Guide,
                  Reference,
                  Sample,
                  TechnicalNote,
   };

                  DocBook () = default;
                  DocBook (const DocBook & rhs) = default;
                  DocBook (DocBook && rhs) = default;
   virtual        ~DocBook () = default;

   DocBook &      operator = (const DocBook & rhs) = default;
   DocBook &      operator = (DocBook && rhs) = default;

   Type           type = Type::Reference;
   DocInlines     title;
   std::string    id;
   std::string    namespace_;

   DocBlocks      overview;
   DocChapters    chapters;

   const DocLibrary &
                  parent () const;

   DocLibrary *   parent_ptr = nullptr;
   DocBook *      previous_ptr = nullptr;
   DocBook *      next_ptr = nullptr;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const DocBook & rhs);
   bool           operator != (const DocBook & rhs);



}; // class DocBook

using DocBooks = std::list <DocBook>;



}  // namespace otdgen



// #include "DocBook.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

