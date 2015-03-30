/*****************************************************************************

      DocCartouche.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DocBlock.h"
#include "DocInline.h"



namespace otdgen
{



class DocCartouche
:  public DocBlock
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  DocCartouche () = default;
                  DocCartouche (const DocCartouche & rhs) = default;
                  DocCartouche (DocCartouche && rhs) = default;
   virtual        ~DocCartouche () = default;

   DocCartouche & operator = (const DocCartouche & rhs) = default;
   DocCartouche & operator = (DocCartouche && rhs) = default;

   std::string    inherit;
   std::string    header;
   std::string    guide_id;
   DocInlines     guide;
   std::list <std::string>
                  declarations;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const DocCartouche & rhs);
   bool           operator != (const DocCartouche & rhs);



}; // class DocCartouche



}  // namespace otdgen



// #include "DocCartouche.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

