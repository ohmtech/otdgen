/*****************************************************************************

      Token.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "otdgen/Token.h"

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

Token::Token (const std::string & str, size_t pos)
:  _str (str)
,  _pos (pos)
{
   assert (!str.empty ());
}



/*
==============================================================================
Name : operator ==
==============================================================================
*/

bool  Token::operator == (const Token & rhs) const
{
   bool cmp_pos_flag = (_pos != size_t (-1)) && (rhs._pos != size_t (-1));

   if (cmp_pos_flag)
   {
      if (_str != rhs._str) return false;
      return _pos == rhs._pos;
   }
   else
   {
      return _str == rhs._str;
   }
}



/*
==============================================================================
Name : operator !=
==============================================================================
*/

bool  Token::operator != (const Token & rhs) const
{
   return !this->operator == (rhs);
}



/*
==============================================================================
Name : operator std::string
==============================================================================
*/

Token::operator std::string () const
{
   return _str;
}



/*
==============================================================================
Name : position
==============================================================================
*/

size_t   Token::position () const
{
   return _pos;
}



/*
==============================================================================
Name : is_whitespaces
==============================================================================
*/

bool  Token::is_whitespaces () const
{
   for (auto && c : _str)
   {
      bool ws_flag = false;
      ws_flag |= (c == ' ');
      ws_flag |= (c == '\t');
      ws_flag |= (c == '\r');
      ws_flag |= (c == '\n');

      if (!ws_flag) return false;
   }

   return true;
}



/*
==============================================================================
Name : is_symbol
==============================================================================
*/

bool  Token::is_symbol () const
{
   for (auto && c : _str)
   {
      bool ok_flag = false;
      ok_flag |= (c >= 'a') && (c <= 'z');
      ok_flag |= (c >= '0') && (c <= '9');

      if (!ok_flag) return false;
   }

   return true;
}



/*
==============================================================================
Name : is_key
==============================================================================
*/

bool  Token::is_key () const
{
   return is_symbol ();
}



/*
==============================================================================
Name : is_value
==============================================================================
*/

bool  Token::is_value () const
{
   for (auto && c : _str)
   {
      bool ok_flag = false;
      ok_flag |= (c >= 'a') && (c <= 'z');
      ok_flag |= (c >= 'A') && (c <= 'Z');
      ok_flag |= (c >= '0') && (c <= '9');
      ok_flag |= (c == '_');
      ok_flag |= (c == '/');
      ok_flag |= (c == '+');
      ok_flag |= (c == '-');
      ok_flag |= (c == '.');

      if (!ok_flag) return false;
   }

   return true;
}



/*
==============================================================================
Name : trim_whitespaces
==============================================================================
*/

void  Token::trim_whitespaces ()
{
   std::string str;

   for (auto && c : _str)
   {
      bool ws_flag = false;
      ws_flag |= (c == ' ');
      ws_flag |= (c == '\t');
      ws_flag |= (c == '\r');
      ws_flag |= (c == '\n');

      if (!ws_flag)
      {
         str.push_back (c);
      }
   }

   _str = str;
}


const Token Token::comment_ml_begin ("/*");
const Token Token::comment_ml_end ("*/");
const Token Token::comment_sl ("//");
const Token Token::lf ("\n");

const Token Token::library ("\\library");
const Token Token::book ("\\book");
const Token Token::chapter ("\\chapter");
const Token Token::section ("\\section");
const Token Token::subsection ("\\subsection");
const Token Token::subsubsection ("\\subsubsection");

const Token Token::codeblock ("\\codeblock");
const Token Token::codeblock_marker ("***");

const Token Token::note ("\\note");
const Token Token::important ("\\important");
const Token Token::warning ("\\warning");

const Token Token::namespace_ ("\\namespace");
const Token Token::class_ ("\\class");
const Token Token::inherit ("\\inherit");
const Token Token::header ("\\header");
const Token Token::guide ("\\guide");
const Token Token::declaration ("\\declaration");
const Token Token::parameter ("\\parameter");
const Token Token::type ("\\type");
const Token Token::constructor ("\\constructor");
const Token Token::destructor ("\\destructor");
const Token Token::method ("\\method");
const Token Token::variable ("\\variable");
const Token Token::function ("\\function");
const Token Token::brief ("\\brief");
const Token Token::division ("\\division");

const Token Token::itemize ("\\itemize");
const Token Token::enumerate ("\\enumerate");
const Token Token::item ("\\item");

const Token Token::table ("\\table");
const Token Token::row ("\\row");

const Token Token::emph ("\\emph");
const Token Token::code ("\\code");
const Token Token::image ("\\image");
const Token Token::link ("\\link");

const Token Token::include ("#include");
const Token Token::include_quote ("\"");

const Token Token::option_begin ("[");
const Token Token::option_assign ("=");
const Token Token::option_separator (",");
const Token Token::option_end ("]");

const Token Token::block_begin ("{");
const Token Token::block_end ("}");

const Token Token::eof ("\x03");



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

