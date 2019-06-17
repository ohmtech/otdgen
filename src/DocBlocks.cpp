/*****************************************************************************

      DocBlocks.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/DocBlocks.h"

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : const_iterator::ctor
==============================================================================
*/

DocBlocks::const_iterator::const_iterator (std::list <std::shared_ptr <DocBlock>>::const_iterator it)
:  _it (it)
{
}



/*
==============================================================================
Name : const_iterator::operator ++
==============================================================================
*/

DocBlocks::const_iterator &   DocBlocks::const_iterator::operator ++ ()
{
   ++_it;

   return *this;
}



/*
==============================================================================
Name : const_iterator::operator ==
==============================================================================
*/

bool  DocBlocks::const_iterator::operator == (const const_iterator & rhs) const
{
   return _it == rhs._it;
}



/*
==============================================================================
Name : const_iterator::operator !=
==============================================================================
*/

bool  DocBlocks::const_iterator::operator != (const const_iterator & rhs) const
{
   return _it != rhs._it;
}



/*
==============================================================================
Name : const_iterator::operator *
==============================================================================
*/

const DocBlock &  DocBlocks::const_iterator::operator * ()
{
   return **_it;
}



/*
==============================================================================
Name : const_iterator::operator ->
==============================================================================
*/

const DocBlock *  DocBlocks::const_iterator::operator -> ()
{
   return &**_it;
}



/*
==============================================================================
Name : begin
==============================================================================
*/

DocBlocks::const_iterator  DocBlocks::begin () const
{
   return _content.begin ();
}



/*
==============================================================================
Name : end
==============================================================================
*/

DocBlocks::const_iterator  DocBlocks::end () const
{
   return _content.end ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

