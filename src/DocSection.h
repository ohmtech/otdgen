/*****************************************************************************

      DocSection.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DocBlock.h"
#include "DocInline.h"



namespace otdgen
{



class DocSection
:  public DocBlock
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Level
   {
                  Section,
                  SubSection,
                  SubSubSection,
   };

                  DocSection () = default;
                  DocSection (const DocSection & rhs) = default;
                  DocSection (DocSection && rhs) = default;
   virtual        ~DocSection () = default;

   DocSection &   operator = (const DocSection & rhs) = default;
   DocSection &   operator = (DocSection && rhs) = default;

   Level          level;
   DocInlines     title;
   std::string    id;
   std::string    id_sub;
   std::string    id_subsub;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const DocSection & rhs);
   bool           operator != (const DocSection & rhs);



}; // class DocSection



}  // namespace otdgen



// #include "DocSection.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

