/*****************************************************************************

      DocBlock.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace otdgen
{



class DocBlock
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Type
   {
                  Section,
                  Information,
                  List,
                  Table,
                  CodeBlock,
                  Paragraph,
   };

                  DocBlock () = default;
                  DocBlock (const DocBlock & rhs) = default;
                  DocBlock (DocBlock && rhs) = default;
   virtual        ~DocBlock () = default;

   DocBlock &     operator = (const DocBlock & rhs) = default;
   DocBlock &     operator = (DocBlock && rhs) = default;

   Type           type;

   template <class T>
   const T &      cast () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const DocBlock & rhs);
   bool           operator != (const DocBlock & rhs);



}; // class DocBlock



}  // namespace otdgen



#include "DocBlock.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

