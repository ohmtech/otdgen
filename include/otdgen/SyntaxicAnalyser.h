/*****************************************************************************

      SyntaxicAnalyser.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/Expression.h"
#include "otdgen/Token.h"

#include <map>
#include <string>



namespace otdgen
{



class SyntaxicAnalyser
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  SyntaxicAnalyser (Tokens & tokens, const std::string & source, const std::string & context);
   virtual        ~SyntaxicAnalyser () = default;

   void           process ();
   Tokens         tokens ();
   ExpressionRoot &
                  root ();



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           process_comment_ml ();
   void           process_comment_sl ();

   void           process (Tokens::iterator & it);
   void           process_command (Tokens::iterator & it);
   void           process_list (Tokens::iterator & it);
   void           process_table (Tokens::iterator & it);
   void           process_codeblock (Tokens::iterator & it);
   bool           ends_with (const std::string & str, const std::string & pattern);
   void           process_include (Tokens::iterator & it);
   void           process_paragraph (Tokens::iterator & it);

   void           error (Tokens::iterator it, const std::string & error);

   void           push_expressions (Expressions & expressions);
   void           pop_expressions ();
   Expressions &  cur_expressions ();
   template <class T>
   T &            add_expression ();

   Tokens &       _tokens;
   const std::string &
                  _source;
   const std::string
                  _context;
   std::string    _base_path;

   bool           _in_block_flag = false;

   ExpressionRoot _root;
   std::list <Expressions *>
                  _expressions_ptr_stack;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  SyntaxicAnalyser () = delete;
                  SyntaxicAnalyser (const SyntaxicAnalyser & rhs) = delete;
                  SyntaxicAnalyser (SyntaxicAnalyser && rhs) = delete;
   SyntaxicAnalyser &
                  operator = (const SyntaxicAnalyser & rhs) = delete;
   SyntaxicAnalyser &
                  operator = (SyntaxicAnalyser && rhs) = delete;
   bool           operator == (const SyntaxicAnalyser & rhs);
   bool           operator != (const SyntaxicAnalyser & rhs);



}; // class SyntaxicAnalyser



}  // namespace otdgen



#include "SyntaxicAnalyser.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

