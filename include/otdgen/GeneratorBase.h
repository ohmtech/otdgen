/*****************************************************************************

      GeneratorBase.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <string>
#include <vector>



namespace otdgen
{



class Conf;
class Toc;

class GeneratorBase
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  GeneratorBase (const Conf & conf, const Toc & toc);
   virtual        ~GeneratorBase () = default;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:

   void           write (const std::string & rel_path, const std::string & content);
   void           make_dirs (const std::string & rel_path);
   const Conf &   conf () const;
   const Toc &    toc () const;

   std::string    escape_xml (const std::string & txt);
   std::string    escape_pourcent (const std::string & txt);

   std::string    convert_image (const std::vector <std::string> & cur, const std::string & src_path);
   void           convert_pdf_to_png (const std::string & dst_path, const std::string & src_path);
   void           convert_svg_to_png (const std::string & dst_path, const std::string & src_path);



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   const Conf &   _conf;
   const Toc &    _toc;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  GeneratorBase (const GeneratorBase & rhs) = delete;
                  GeneratorBase (GeneratorBase && rhs) = delete;
   GeneratorBase &operator = (const GeneratorBase & rhs) = delete;
   GeneratorBase &operator = (GeneratorBase && rhs) = delete;
   bool           operator == (const GeneratorBase & rhs);
   bool           operator != (const GeneratorBase & rhs);



}; // class GeneratorBase



}  // namespace otdgen



// #include "GeneratorBase.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

