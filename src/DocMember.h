/*****************************************************************************

      DocMember.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DocBlocks.h"
#include "DocInline.h"

#include <list>



namespace otdgen
{



class DocMember
:  public DocBlock
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Type
   {
                  Constructor,
                  Destructor,
                  Function,
                  Variable,
                  Division,
   };

                  DocMember () = default;
                  DocMember (const DocMember & rhs) = default;
                  DocMember (DocMember && rhs) = default;
   virtual        ~DocMember () = default;

   DocMember &    operator = (const DocMember & rhs) = default;
   DocMember &    operator = (DocMember && rhs) = default;

   Type           type;
   std::string    name;
   DocInlines     brief;
   DocBlocks      description;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const DocMember & rhs);
   bool           operator != (const DocMember & rhs);



}; // class DocMember

using DocMembers = std::list <DocMember>;



}  // namespace otdgen



// #include "DocMember.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

