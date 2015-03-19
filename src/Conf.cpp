/*****************************************************************************

      Conf.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Conf.h"

#include <map>

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : parse
==============================================================================
*/

bool  Conf::parse (int argc, const char * argv[])
{
   std::map <std::string, std::string> options;

   // parse

   for (int i = 1 ; i < argc ; ++i)
   {
      std::string arg = argv [i];

      if (arg.find ("--") == 0)
      {
         size_t pos = arg.find ("=");

         if (pos == std::string::npos)
         {
            std::string key = arg.substr (2);

            options [key] = "";
         }
         else
         {
            std::string key = arg.substr (2, pos - 2);
            std::string value = arg.substr (pos + 1);

            options [key] = value;
         }
      }
      else
      {
         if (i != argc - 1) return false;
         file = arg;
      }
   }

   // check options

   for (auto && option_pair : options)
   {
      auto && option = option_pair.first;

      bool ok_flag = false;
      ok_flag |= option == "selftest";
      ok_flag |= option == "output";

      if (!ok_flag) return false;

      if (option == "selftest")
      {
         self_test = true;
      }
      else if (option == "output")
      {
         output_path = option_pair.second;
      }
   }

   return true;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

