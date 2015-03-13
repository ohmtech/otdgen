/*****************************************************************************

      LexicalAnalyser.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Token.h"

#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>



namespace otdgen
{



class LexicalAnalyser
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  LexicalAnalyser () = default;
   virtual        ~LexicalAnalyser () = default;

   Tokens         process (std::string txt);



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           preprocess (std::string & txt);

   Token          read (size_t & pos, const std::string & txt, const Tokens & tokens);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  LexicalAnalyser (const LexicalAnalyser & rhs) = delete;
                  LexicalAnalyser (LexicalAnalyser && rhs) = delete;
   LexicalAnalyser &
                  operator = (const LexicalAnalyser & rhs) = delete;
   LexicalAnalyser &
                  operator = (LexicalAnalyser && rhs) = delete;
   bool           operator == (const LexicalAnalyser & rhs);
   bool           operator != (const LexicalAnalyser & rhs);



}; // class LexicalAnalyser



}  // namespace otdgen



// #include "LexicalAnalyser.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

