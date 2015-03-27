/*****************************************************************************

      GeneratorBase.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "GeneratorBase.h"

#include "Conf.h"

#include <fstream>
#include <iostream>

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

GeneratorBase::GeneratorBase (const Conf & conf, const Toc & toc)
:  _conf (conf)
,  _toc (toc)
{
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : write
==============================================================================
*/

void  GeneratorBase::write (const std::string & rel_path, const std::string & content)
{
   if (_conf.output_path.empty ())
   {
      std::cout << content;
      std::cout << "==========================\n\n";
   }
   else
   {
      // make the dirs

      make_dirs (rel_path);

      // fill content

      std::string path = _conf.output_path + "/" + rel_path;

      std::ofstream ofs (path, std::ifstream::binary);
      assert (ofs);

      ofs.write (&content [0], int (content.size ()));

      ofs.close ();
   }
}



/*
==============================================================================
Name : make_dirs
==============================================================================
*/

void  GeneratorBase::make_dirs (const std::string & rel_path)
{
   std::string path = _conf.output_path + "/" + rel_path;

   size_t pos = path.rfind ("/");
   assert (pos != std::string::npos);

   std::string basepath = path.substr (0, pos - 0);

   std::string cmd = "mkdir -p " + basepath;
   system (cmd.c_str ());
}



/*
==============================================================================
Name : conf
==============================================================================
*/

const Conf &   GeneratorBase::conf () const
{
   return _conf;
}



/*
==============================================================================
Name : toc
==============================================================================
*/

const Toc & GeneratorBase::toc () const
{
   return _toc;
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

