/*****************************************************************************

      DocInformation.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DocBlock.h"
#include "DocInline.h"



namespace otdgen
{



class DocInformation
:  public DocBlock
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Level
   {
                  Note,
                  Important,
                  Warning,
   };

                  DocInformation () = default;
                  DocInformation (const DocInformation & rhs) = default;
                  DocInformation (DocInformation && rhs) = default;
   virtual        ~DocInformation () = default;

   DocInformation &   operator = (const DocInformation & rhs) = default;
   DocInformation &   operator = (DocInformation && rhs) = default;

   Level          level;
   DocInlines     body;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const DocInformation & rhs);
   bool           operator != (const DocInformation & rhs);



}; // class DocInformation



}  // namespace otdgen



// #include "DocInformation.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

