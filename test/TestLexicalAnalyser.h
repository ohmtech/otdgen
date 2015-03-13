/*****************************************************************************

      TestLexicalAnalyser.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace otdgen
{



class TestLexicalAnalyser
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestLexicalAnalyser () = default;
   virtual        ~TestLexicalAnalyser () = default;

   void           run ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_001 ();
   void           run_002 ();
   void           run_003 ();
   void           run_004 ();
   void           run_005 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestLexicalAnalyser (const TestLexicalAnalyser & rhs) = delete;
                  TestLexicalAnalyser (TestLexicalAnalyser && rhs) = delete;
   TestLexicalAnalyser &
                  operator = (const TestLexicalAnalyser & rhs) = delete;
   TestLexicalAnalyser &
                  operator = (TestLexicalAnalyser && rhs) = delete;
   bool           operator == (const TestLexicalAnalyser & rhs);
   bool           operator != (const TestLexicalAnalyser & rhs);



}; // class TestLexicalAnalyser



}  // namespace otdgen



// #include "TestLexicalAnalyser.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

