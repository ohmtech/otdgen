/*****************************************************************************

      DocMethod.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "DocBlocks.h"
#include "DocInline.h"

#include <list>



namespace otdgen
{



class DocMethod
:  public DocBlock
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Type
   {
                  Constructor,
                  Destructor,
                  Function,
                  Division,
   };

                  DocMethod () = default;
                  DocMethod (const DocMethod & rhs) = default;
                  DocMethod (DocMethod && rhs) = default;
   virtual        ~DocMethod () = default;

   DocMethod &    operator = (const DocMethod & rhs) = default;
   DocMethod &    operator = (DocMethod && rhs) = default;

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
   bool           operator == (const DocMethod & rhs);
   bool           operator != (const DocMethod & rhs);



}; // class DocMethod

using DocMethods = std::list <DocMethod>;



}  // namespace otdgen



// #include "DocMethod.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

