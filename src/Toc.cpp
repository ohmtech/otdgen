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



/*
==============================================================================
Name : get_name
Description :
   Returns the undecorated title for the full id 'cur'
==============================================================================
*/

std::string Toc::get_name (std::vector <std::string> cur) const
{
   auto it = _id_name_map.find (cur);

   if (it != _id_name_map.end ())
   {
      return it->second;
   }

   return "";
}



/*
==============================================================================
Name : get_toc
Description :
   Returns the partial toc matching 'cur'
==============================================================================
*/

std::list <std::pair <std::vector <std::string>, std::string>> Toc::get_toc (std::vector <std::string> cur) const
{
   std::list <std::pair <std::vector <std::string>, std::string>> ret;

   for (auto && pair : _id_name_list)
   {
      auto sub_cur = pair.first;

      if (sub_cur.size () < cur.size ()) continue;

      auto name = pair.second;

      bool match_flag = true;

      for (size_t i = 0 ; i < cur.size () ; ++i)
      {
         if (sub_cur [i] != cur [i])
         {
            match_flag = false;
            break;
         }
      }

      if (match_flag)
      {
         ret.push_back (std::make_pair (sub_cur, name));
      }
   }

   return ret;
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

   bool ok_flag = process (cur_id, command);

   if (ok_flag)
   {
      _id_set.insert (cur_id);

      std::string name = make_undecorated_name (command);

      _id_name_map [cur_id] = name;
      _id_name_list.push_back (std::make_pair (cur_id, name));
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

bool  Toc::process (std::vector <std::string> & cur_id, const ExpressionCommand & command)
{
   auto it = command.options.find ("id");

   std::string ide;

   if (it == command.options.end ())
   {
      if (command.name == std::string (Token::class_))
      {
         ide = make_undecorated_name (command);
      }
      else
      {
         return false;  // abort
      }
   }
   else
   {
      ide = it->second;
   }

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
   else if (command.name == std::string (Token::class_))
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
      return false;  // abort
   }

   cur_id.resize (level);
   cur_id.push_back (ide);

   return true;
}



/*
==============================================================================
Name : make_undecorated_name
==============================================================================
*/

std::string Toc::make_undecorated_name (const ExpressionCommand & command)
{
   std::string name;

   const ExpressionParagraph & paragraph
      = dynamic_cast <const ExpressionParagraph &> (**command.bodies.begin ());

   for (const auto & expr_sptr : paragraph.expressions)
   {
      const auto & expr = *expr_sptr;

      const auto * expr_text_ptr = dynamic_cast <const ExpressionText *> (&expr);

      if (expr_text_ptr != nullptr)
      {
         name += expr_text_ptr->body;
      }

      const auto * expr_command_ptr = dynamic_cast <const ExpressionCommand *> (&expr);

      if (expr_command_ptr != nullptr)
      {
         name += make_undecorated_name (*expr_command_ptr);
      }
   }

   return name;
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

