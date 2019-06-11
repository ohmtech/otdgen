/*****************************************************************************

      Conf.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/Conf.h"

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
      ok_flag |= option == "output";
      ok_flag |= option == "format";

      if (!ok_flag) return false;

      if (option == "output")
      {
         output_path = option_pair.second;
      }
      else if (option == "format")
      {
         std::string value = option_pair.second;

         if (value == "html")
         {
            format = Format::Html;
         }
         else if (value == "html-singlepage")
         {
            format = Format::HtmlSinglePage;
         }
         else if (value == "pdf")
         {
            format = Format::Pdf;
         }
         else if (value == "github")
         {
            format = Format::GitHubMarkDown;
         }
         else if (value == "docset")
         {
            format = Format::DocSet;
         }
         else
         {
            return false;
         }
      }
   }

   return true;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

