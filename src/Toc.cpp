/*****************************************************************************

      Toc.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Toc.h"

#include "Conf.h"
#include "Expression.h"
#include "Token.h"

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
Description :
   Parse the expression tree and construct table of content.
==============================================================================
*/

void  Toc::process (const ExpressionRoot & root)
{
   _id_set.clear ();

   std::vector <std::string> cur_id;

   for (auto && expression_uptr : root.expressions)
   {
      const auto & expression = *expression_uptr;

      process (cur_id, expression);
   }
}



/*
==============================================================================
Name : find
Description :
   Returns the full id from the partial id 'ide' in the context of full id
   'cur'
==============================================================================
*/

std::vector <std::string>  Toc::find (std::vector <std::string> cur, const std::string & ide) const
{
   std::vector <std::string> rel_id = split (ide);

   while (!cur.empty ())
   {
      std::vector <std::string> full_id = cur;
      full_id.insert (full_id.end (), rel_id.begin (), rel_id.end ());

      if (_id_set.find (full_id) != _id_set.end ())
      {
         return full_id;   // found
      }

      cur.pop_back ();
   }

   // id not found

   std::vector <std::string> empty;
   return empty;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
==============================================================================
*/

void  Toc::process (std::vector <std::string> & cur_id, const Expression & expression)
{
   auto command_ptr = dynamic_cast <const ExpressionCommand *> (&expression);

   if (command_ptr == nullptr) return; // abort

   const ExpressionCommand & command = *command_ptr;

   process (cur_id, command);

   _id_set.insert (cur_id);
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  Toc::process (std::vector <std::string> & cur_id, const ExpressionCommand & command)
{
   auto it = command.options.find ("id");
   if (it == command.options.end ()) return; // abort

   const std::string & ide = it->second;

   size_t level;

   if (command.name == std::string (Token::library))
   {
      level = 0;
   }
   else if (command.name == std::string (Token::book))
   {
      level = 1;
   }
   else if (command.name == std::string (Token::chapter))
   {
      level = 2;
   }
   else if (command.name == std::string (Token::section))
   {
      level = 3;
   }
   else if (command.name == std::string (Token::subsection))
   {
      level = 4;
   }
   else if (command.name == std::string (Token::subsubsection))
   {
      level = 5;
   }
   else
   {
      return;  // abort
   }

   cur_id.resize (level);
   cur_id.push_back (ide);
}



/*
==============================================================================
Name : split
Description :
   Split on '/' to construct an id.
==============================================================================
*/

std::vector <std::string>   Toc::split (const std::string & ide) const
{
   std::vector <std::string> ret;

   size_t pos = 0;

   while (true)
   {
      size_t pos2 = ide.find ("/", pos);
      if (pos2 == std::string::npos)
      {
         ret.push_back (ide.substr (pos));
         break;
      }
      else
      {
         ret.push_back (ide.substr (pos, pos2 - pos));
         pos = pos2 + 1;
      }
   }

   return ret;
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

