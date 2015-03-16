/*****************************************************************************

      main.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Central.h"
#include "Conf.h"
#include "GeneratorGitHubMarkDown.h"
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

      Root root = central.process (path);

      Toc toc (conf);
      toc.process (root);

      GeneratorGitHubMarkDown generator (conf, toc);
      generator.process (root);
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
   std::cout << "  otdgen source_file\n";
}



/*
==============================================================================
Name : main
==============================================================================
*/

int   main (int argc, const char * argv[])
{
   if (argc != 2)
   {
      usage ();
      return -1;
   }

   std::string arg = argv [1];

   if (arg == "--selftest")
   {
      test ();
   }
   else
   {
      otdgen::Conf conf;
      conf.output_path = "/Users/raf/Desktop/dev/flip/documentation/markdown";
      run (conf, arg);
   }

   return 0;
}
