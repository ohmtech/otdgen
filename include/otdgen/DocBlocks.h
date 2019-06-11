/*****************************************************************************

      DocBlocks.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/DocBlock.h"

#include <list>
#include <memory>



namespace otdgen
{



class DocBlocks
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   class const_iterator
   {
   public:
                  const_iterator () = default;
                  const_iterator (const const_iterator &) = default;
                  const_iterator (std::list <std::shared_ptr <DocBlock>>::const_iterator it);

      const_iterator &
                  operator ++ ();
      bool        operator == (const const_iterator & rhs) const;
      bool        operator != (const const_iterator & rhs) const;
      const DocBlock &
                  operator * ();
      const DocBlock *
                  operator -> ();

   private:
      std::list <std::shared_ptr <DocBlock>>::const_iterator
                  _it;
   };

                  DocBlocks () = default;
                  DocBlocks (const DocBlocks & rhs) = default;
                  DocBlocks (DocBlocks && rhs) = default;
   virtual        ~DocBlocks () = default;

   DocBlocks &    operator = (const DocBlocks & rhs) = default;
   DocBlocks &    operator = (DocBlocks && rhs) = default;

   const_iterator begin () const;
   const_iterator end () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

   std::list <std::shared_ptr <DocBlock>>
                  _content;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   bool           operator == (const DocBlocks & rhs);
   bool           operator != (const DocBlocks & rhs);



}; // class DocBlocks



}  // namespace otdgen



// #include "DocBlocks.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

