/*****************************************************************************

      DocInline.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <list>
#include <string>



namespace otdgen
{



class DocInline
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Type
   {
                  Text,
                  Emphasis,
                  Code,
                  LinkId,
                  LinkUrl,
   };

                  DocInline () = default;
                  DocInline (const DocInline & rhs) = default;
                  DocInline (DocInline && rhs) = default;
   virtual        ~DocInline () = default;

   DocInline &    operator = (const DocInline & rhs) = default;
   DocInline &    operator = (DocInline && rhs) = default;

   Type           type;
   std::string    text;
   std::string    meta;

   std::list <DocInline>
                  node;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const DocInline & rhs);
   bool           operator != (const DocInline & rhs);



}; // class DocInline

using DocInlines = std::list <DocInline>;



}  // namespace otdgen



// #include "DocInline.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

