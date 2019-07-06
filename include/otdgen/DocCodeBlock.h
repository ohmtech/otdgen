/*****************************************************************************

      DocCodeBlock.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/DocBlock.h"
#include "otdgen/DocInline.h"



namespace otdgen
{



class DocCodeBlock
:  public DocBlock
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class LineType
   {
                  Normal,
                  Emphasis,
                  Fade,
   };

                  DocCodeBlock () = default;
                  DocCodeBlock (const DocCodeBlock & rhs) = default;
                  DocCodeBlock (DocCodeBlock && rhs) = default;
   virtual        ~DocCodeBlock () = default;

   DocCodeBlock &   operator = (const DocCodeBlock & rhs) = default;
   DocCodeBlock &   operator = (DocCodeBlock && rhs) = default;

   std::string    type;
   std::list <std::pair <std::string, LineType>>
                  lines;




/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const DocCodeBlock & rhs);
   bool           operator != (const DocCodeBlock & rhs);



}; // class DocCodeBlock



}  // namespace otdgen



// #include "DocCodeBlock.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

