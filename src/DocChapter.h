/*****************************************************************************

      DocChapter.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DocBlocks.h"
#include "DocCartouche.h"
#include "DocInline.h"
#include "DocMember.h"
#include "DocParameter.h"
#include "DocType.h"

#include <list>
#include <string>



namespace otdgen
{



class DocBook;

class DocChapter
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
   enum class Type
   {
                  Normal,
                  Class,
   };

                  DocChapter () = default;
                  DocChapter (const DocChapter & rhs) = default;
                  DocChapter (DocChapter && rhs) = default;
   virtual        ~DocChapter () = default;

   DocChapter &   operator = (const DocChapter & rhs) = default;
   DocChapter &   operator = (DocChapter && rhs) = default;

   const DocBook &
                  parent () const;
   bool           has_previous () const;
   const DocChapter &
                  previous () const;
   bool           has_next () const;
   const DocChapter &
                  next () const;

   Type           type = Type::Normal;
   DocInlines     title;
   std::string    name; // class name
   std::string    id;

   DocBlocks      blocks;
   DocCartouche   cartouche;
   DocParameters  parameters;
   DocTypes       types;
   DocMembers     members;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   DocBook *      parent_ptr = nullptr;
   DocChapter *   previous_ptr = nullptr;
   DocChapter *   next_ptr = nullptr;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const DocChapter & rhs);
   bool           operator != (const DocChapter & rhs);



}; // class DocChapter

using DocChapters = std::list <DocChapter>;



}  // namespace otdgen



// #include "DocChapter.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

