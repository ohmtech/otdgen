/*****************************************************************************

      TestLexicalAnalyser.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "TestLexicalAnalyser.h"

#include "LexicalAnalyser.h"

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestLexicalAnalyser::run ()
{
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestLexicalAnalyser::run_001 ()
{
   LexicalAnalyser analyser;
   auto tokens = analyser.process ("/********/");

   Tokens tokens2;
   tokens2.emplace_back ("/*", 0);
   tokens2.emplace_back ("***", 2);
   tokens2.emplace_back ("***", 5);
   tokens2.emplace_back ("*/", 8);

   assert (tokens == tokens2);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestLexicalAnalyser::run_002 ()
{
   LexicalAnalyser analyser;
   auto tokens = analyser.process ("\\chapter\\code");

   Tokens tokens2;
   tokens2.emplace_back ("\\chapter", 0);
   tokens2.emplace_back ("\\code", 8);

   assert (tokens == tokens2);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestLexicalAnalyser::run_003 ()
{
   LexicalAnalyser analyser;
   auto tokens = analyser.process ("\\chapter [id=opt] {Hello world !}");

   Tokens tokens2;
   tokens2.emplace_back ("\\chapter", 0);
   tokens2.emplace_back (" ", 8);
   tokens2.emplace_back ("[", 9);
   tokens2.emplace_back ("id", 10);
   tokens2.emplace_back ("=", 12);
   tokens2.emplace_back ("opt", 13);
   tokens2.emplace_back ("]", 16);
   tokens2.emplace_back (" ", 17);
   tokens2.emplace_back ("{", 18);
   tokens2.emplace_back ("Hello world !", 19);
   tokens2.emplace_back ("}", 19 + 13);

   assert (tokens == tokens2);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestLexicalAnalyser::run_004 ()
{
   LexicalAnalyser analyser;
   auto tokens = analyser.process ("#include \"something.otd\"");

   Tokens tokens2;
   tokens2.emplace_back ("#include", 0);
   tokens2.emplace_back (" ", 8);
   tokens2.emplace_back ("\"", 9);
   tokens2.emplace_back ("something.otd", 10);
   tokens2.emplace_back ("\"", 10 + 13);

   assert (tokens == tokens2);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestLexicalAnalyser::run_005 ()
{
   LexicalAnalyser analyser;
   auto tokens = analyser.process ("Hello\nWorld");

   Tokens tokens2;
   tokens2.emplace_back ("Hello", 0);
   tokens2.emplace_back ("\n", 5);
   tokens2.emplace_back ("World", 6);

   assert (tokens == tokens2);
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

