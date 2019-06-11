/*****************************************************************************

      main.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Central.h"
#include "Conf.h"
#include "GeneratorGitHubMarkDown.h"
#include "GeneratorHtml.h"
#include "LexicalAnalyser.h"
#include "StructuralAnalyser.h"
#include "Toc.h"

#include <iostream>
#include <set>
#include <string>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

void  run (const otdgen::Conf & conf, const std::string & path);
void  usage ();



/*
==============================================================================
Name : run
==============================================================================
*/

void  run (const otdgen::Conf & conf, const std::string & path)
{
   using namespace otdgen;

   try
   {
      Central central;

      ExpressionRoot root = central.process (path);

      Toc toc;
      toc.process (root);

      StructuralAnalyser analyser;
      DocLibrary library = analyser.process (root);

      if (conf.format == Conf::Format::Html)
      {
         GeneratorHtml generator (conf, toc);
         generator.process (library);
      }
      else if (conf.format == Conf::Format::GitHubMarkDown)
      {
         GeneratorGitHubMarkDown generator (conf, toc);
         generator.process (library);
      }
      else if (conf.format == Conf::Format::DocSet)
      {
         GeneratorHtml generator (conf, toc);
         generator.process (library);
      }
   }
   catch (...)
   {
      exit (-1);
   }
}



/*
==============================================================================
Name : usage
==============================================================================
*/

void  usage ()
{
   std::cout << "usage:\n";
   std::cout << "  otdgen --format=<format> --output=<output> source_file\n";
}



/*
==============================================================================
Name : main
==============================================================================
*/

int   main (int argc, const char * argv[])
{
   otdgen::Conf conf;

   bool ok_flag = argc > 1;

   if (ok_flag)
   {
      ok_flag = conf.parse (argc, argv);
   }

   if (!ok_flag)
   {
      usage ();
      return -1;
   }

   run (conf, conf.file);

   return 0;
}
