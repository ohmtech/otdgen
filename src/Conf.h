/*****************************************************************************

      Conf.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <string>



namespace otdgen
{



class Conf
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   enum class Format
   {
                  Html,
                  Pdf,
                  GitHubMarkDown,
   };

                  Conf () = default;
   virtual        ~Conf () = default;

   Format         format = Format::GitHubMarkDown;
   bool           single_page = false;
   std::string    output_path;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Conf (const Conf & rhs) = delete;
                  Conf (Conf && rhs) = delete;
   Conf &         operator = (const Conf & rhs) = delete;
   Conf &         operator = (Conf && rhs) = delete;
   bool           operator == (const Conf & rhs);
   bool           operator != (const Conf & rhs);



}; // class Conf



}  // namespace otdgen



// #include "Conf.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

