/*****************************************************************************

      DocBlock.hpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#if defined (otdgen_DocBlock_CURRENT_CODEHEADER)
   #error Recursive inclusion of DocBlock code header.
#endif
#define  otdgen_DocBlock_CURRENT_CODEHEADER

#if ! defined (otdgen_DocBlock_CODEHEADER_INCLUDED)
#define  otdgen_DocBlock_CODEHEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : function
==============================================================================
*/

template <class T>
const T &   DocBlock::cast () const
{
   return dynamic_cast <const T &> (*this);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace otdgen



#endif   // otdgen_DocBlock_CODEHEADER_INCLUDED

#undef otdgen_DocBlock_CURRENT_CODEHEADER



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

