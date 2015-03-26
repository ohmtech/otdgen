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
#include "Toc.h"
#include "TestLexicalAnalyser.h"
#include "TestSyntaxicAnalyser.h"

#include <iostream>
#include <set>
#include <string>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

void  test ();
void  run (const otdgen::Conf & conf, const std::string & path);
void  usage ();

/*
==============================================================================
Name : run
==============================================================================
*/

void  test ()
{
   using namespace otdgen;

   {
      std::cout << "TestLexicalAnalyser\n";

      TestLexicalAnalyser test;
      test.run ();

      std::cout << "   OK\n";
   }

   {
      std::cout << "TestSyntaxicAnalyser\n";

      TestSyntaxicAnalyser test;
      test.run ();

      std::cout << "   OK\n";
   }
}



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

      Toc toc (conf);
      toc.process (root);

      if (conf.format == Conf::Format::Html)
      {
         GeneratorHtml generator (conf, toc);
         generator.process (root);
      }
      else if (conf.format == Conf::Format::GitHubMarkDown)
      {
         GeneratorGitHubMarkDown generator (conf, toc);
         generator.process (root);
      }
      else if (conf.format == Conf::Format::DocSet)
      {
         GeneratorHtml generator (conf, toc);
         generator.process (root);
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
   std::cout << "  otdgen --selftest\n";
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

   bool ok_flag = conf.parse (argc, argv);

   if (!ok_flag)
   {
      usage ();
      return -1;
   }


   if (conf.self_test)
   {
      test ();
   }
   else
   {
      run (conf, conf.file);
   }

   return 0;
}
