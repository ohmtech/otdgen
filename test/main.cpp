/*****************************************************************************

      main.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "TestLexicalAnalyser.h"
#include "TestSyntaxicAnalyser.h"

#include <iostream>
#include <set>
#include <string>



/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

void  run_test ();
void  usage ();



/*
==============================================================================
Name : run
==============================================================================
*/

void  run_test ()
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
Name : main
==============================================================================
*/

int   main (int /* argc */, const char * /* argv */[])
{
   run_test ();

   return 0;
}
