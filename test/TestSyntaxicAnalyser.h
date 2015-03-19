/*****************************************************************************

      TestSyntaxicAnalyser.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace otdgen
{



class TestSyntaxicAnalyser
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  TestSyntaxicAnalyser () = default;
   virtual        ~TestSyntaxicAnalyser () = default;

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
   void           run_006 ();
   void           run_007 ();
   void           run_008 ();
   void           run_009 ();
   void           run_010 ();
   void           run_011 ();
   void           run_012 ();
   void           run_013 ();
   void           run_014 ();
   void           run_015 ();
   void           run_016 ();
   void           run_017 ();
   void           run_018 ();
   void           run_019 ();
   void           run_020 ();
   void           run_021 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestSyntaxicAnalyser (const TestSyntaxicAnalyser & rhs) = delete;
                  TestSyntaxicAnalyser (TestSyntaxicAnalyser && rhs) = delete;
   TestSyntaxicAnalyser &
                  operator = (const TestSyntaxicAnalyser & rhs) = delete;
   TestSyntaxicAnalyser &
                  operator = (TestSyntaxicAnalyser && rhs) = delete;
   bool           operator == (const TestSyntaxicAnalyser & rhs);
   bool           operator != (const TestSyntaxicAnalyser & rhs);



}; // class TestSyntaxicAnalyser



}  // namespace otdgen



// #include "TestSyntaxicAnalyser.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

