/*****************************************************************************

      DocParameter.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/DocBlock.h"
#include "otdgen/DocInline.h"

#include <list>



namespace otdgen
{



class DocParameter
:  public DocBlock
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  DocParameter () = default;
                  DocParameter (const DocParameter & rhs) = default;
                  DocParameter (DocParameter && rhs) = default;
   virtual        ~DocParameter () = default;

   DocParameter & operator = (const DocParameter & rhs) = default;
   DocParameter & operator = (DocParameter && rhs) = default;

   std::string    type;
   DocInlines     body;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const DocParameter & rhs);
   bool           operator != (const DocParameter & rhs);



}; // class DocParameter

using DocParameters = std::list <DocParameter>;


}  // namespace otdgen



// #include "DocParameter.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

