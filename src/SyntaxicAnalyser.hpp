/*****************************************************************************

      SyntaxicAnalyser.hpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#if defined (otdgen_SyntaxicAnalyser_CURRENT_CODEHEADER)
   #error Recursive inclusion of SyntaxicAnalyser code header.
#endif
#define  otdgen_SyntaxicAnalyser_CURRENT_CODEHEADER

#if ! defined (otdgen_SyntaxicAnalyser_CODEHEADER_INCLUDED)
#define  otdgen_SyntaxicAnalyser_CODEHEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : add_expression
==============================================================================
*/

template <class T>
T &   SyntaxicAnalyser::add_expression ()
{
   T * ptr = new T;

   std::unique_ptr <Expression> expression_uptr (ptr);

   cur_expressions ().push_back (std::move (expression_uptr));

   return *ptr;
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace otdgen



#endif   // otdgen_SyntaxicAnalyser_CODEHEADER_INCLUDED

#undef otdgen_SyntaxicAnalyser_CURRENT_CODEHEADER



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

