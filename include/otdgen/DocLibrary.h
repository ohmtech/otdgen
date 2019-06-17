/*****************************************************************************

      DocLibrary.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/DocBlocks.h"
#include "otdgen/DocBook.h"
#include "otdgen/DocInline.h"



namespace otdgen
{



class DocLibrary
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  DocLibrary () = default;
                  DocLibrary (const DocLibrary & rhs) = default;
                  DocLibrary (DocLibrary && rhs) = default;
   virtual        ~DocLibrary () = default;

   DocLibrary &   operator = (const DocLibrary & rhs) = default;
   DocLibrary &   operator = (DocLibrary && rhs) = default;

   DocInlines     title;
   std::string    id;

   DocBlocks      overview;
   DocBooks       books;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:




/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const DocLibrary & rhs);
   bool           operator != (const DocLibrary & rhs);



}; // class DocLibrary



}  // namespace otdgen



// #include "DocLibrary.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

