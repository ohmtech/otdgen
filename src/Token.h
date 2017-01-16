/*****************************************************************************

      Token.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <string>
#include <list>



namespace otdgen
{



class Token;

using Tokens = std::list <Token>;

class Token
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  Token (const std::string & str, size_t pos = size_t (-1));
                  Token (const Token & rhs) = default;
                  Token (Token && rhs) = default;
   virtual        ~Token () = default;

   Token &        operator = (const Token & rhs) = default;
   Token &        operator = (Token && rhs) = default;

   bool           operator == (const Token & rhs) const;
   bool           operator != (const Token & rhs) const;

                  operator std::string () const;
   size_t         position () const;

   bool           is_whitespaces () const;
   bool           is_symbol () const;
   bool           is_key () const;
   bool           is_value () const;

   void           trim_whitespaces ();

   static const Token
                  comment_ml_begin;
   static const Token
                  comment_ml_end;
   static const Token
                  comment_sl;
   static const Token
                  lf;

   static const Token
                  library;
   static const Token
                  book;
   static const Token
                  chapter;
   static const Token
                  section;
   static const Token
                  subsection;
   static const Token
                  subsubsection;

   static const Token
                  codeblock;
   static const Token
                  codeblock_marker;

   static const Token
                  note;
   static const Token
                  important;
   static const Token
                  warning;

   static const Token
                  namespace_;
   static const Token
                  class_;
   static const Token
                  inherit;
   static const Token
                  header;
   static const Token
                  guide;
   static const Token
                  declaration;
   static const Token
                  parameter;
   static const Token
                  type;
   static const Token
                  constructor;
   static const Token
                  destructor;
   static const Token
                  method;
   static const Token
                  variable;
   static const Token
                  function;
   static const Token
                  brief;
   static const Token
                  division;

   static const Token
                  itemize;
   static const Token
                  enumerate;
   static const Token
                  item;

   static const Token
                  table;
   static const Token
                  row;

   static const Token
                  emph;
   static const Token
                  code;
   static const Token
                  image;
   static const Token
                  link;

   static const Token
                  include;
   static const Token
                  include_quote;

   static const Token
                  option_begin;
   static const Token
                  option_assign;
   static const Token
                  option_separator;
   static const Token
                  option_end;
   static const Token
                  block_begin;
   static const Token
                  block_end;

   static const Token
                  eof;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
   std::string    _str;
   size_t         _pos = size_t (-1);



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Token () = delete;



}; // class Token



}  // namespace otdgen



// #include "Token.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

