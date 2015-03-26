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
==============================================================================
*/

Toc::Toc (const Conf & conf)
:  _conf (conf)
{
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  Toc::process (const ExpressionRoot & root)
{
   _id_set.clear ();
   _chapter_id_list.clear ();
   _guides.clear ();
   _classes.clear ();
   _methods.clear ();

   AbsoluteId cur_id;

   for (auto && expression_uptr : root.expressions)
   {
      const auto & expression = *expression_uptr;

      process (cur_id, expression);
   }
}



/*
==============================================================================
Name : set_current
==============================================================================
*/

void  Toc::set_current (const ExpressionCommand & command)
{
   process (_cur_id, command);
}



/*
==============================================================================
Name : make_url
==============================================================================
*/

std::string Toc::make_url (const std::string & ide) const
{
   // construct absolute ids from depth first and see if they match map

   RelativeId relative_id = make (ide);
   assert (relative_id.size () <= DEEPNESS);

   for (size_t i = 0 ; i < DEEPNESS - relative_id.size () + 1 ; ++i)
   {
      AbsoluteId abs_id = _cur_id;
      size_t pos = DEEPNESS - relative_id.size () - i;

      for (size_t j = 0 ; j < relative_id.size () ; ++j)
      {
         abs_id [pos + j] = relative_id [j];
      }

      for (size_t j = pos + relative_id.size () ; j < DEEPNESS ; ++j)
      {
         abs_id [j].clear ();
      }

      if (_id_set.find (abs_id) != _id_set.end ())
      {
         return make_url (abs_id);
      }
   }

   return "";
}



/*
==============================================================================
Name : make_url_previous_chapter
==============================================================================
*/

std::string Toc::make_url_previous_chapter () const
{
   AbsoluteId cur_chapter_id = _cur_id;
   for (size_t i = 3 ; i < DEEPNESS ; ++i)
   {
      cur_chapter_id [i].clear ();
   }

   auto it = std::find (_chapter_id_list.begin (), _chapter_id_list.end (), cur_chapter_id);

   if (it == _chapter_id_list.end ()) return "";
   if (it == _chapter_id_list.begin ()) return "";

   --it;

   AbsoluteId chapter_id = *it;
   for (size_t i = 0 ; i < 2 ; ++i)
   {
      if (chapter_id [i] != cur_chapter_id [i]) return "";
   }

   return make_url (*it);
}



/*
==============================================================================
Name : make_url_next_chapter
==============================================================================
*/

std::string Toc::make_url_next_chapter () const
{
   AbsoluteId cur_chapter_id = _cur_id;
   for (size_t i = 3 ; i < DEEPNESS ; ++i)
   {
      cur_chapter_id [i].clear ();
   }

   auto it = std::find (_chapter_id_list.begin (), _chapter_id_list.end (), cur_chapter_id);

   if (it == _chapter_id_list.end ()) return "";

   ++it;

   AbsoluteId chapter_id = *it;
   for (size_t i = 0 ; i < 2 ; ++i)
   {
      if (chapter_id [i] != cur_chapter_id [i]) return "";
   }

   return make_url (*it);
}



/*
==============================================================================
Name : guides
==============================================================================
*/

const Toc::NamePathMap &  Toc::guides () const
{
   return _guides;
}



/*
==============================================================================
Name : classes
==============================================================================
*/

const Toc::NamePathMap &  Toc::classes () const
{
   return _classes;
}



/*
==============================================================================
Name : methods
==============================================================================
*/

const Toc::NamePathMap &  Toc::methods () const
{
   return _methods;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
==============================================================================
*/

void  Toc::process (AbsoluteId & cur_id, const Expression & expression)
{
   auto command_ptr = dynamic_cast <const ExpressionCommand *> (&expression);

   if (command_ptr == nullptr) return; // abort

   const ExpressionCommand & command = *command_ptr;

   process (cur_id, command);

   _id_set.insert (cur_id);

   if (command.name == std::string (Token::chapter))
   {
      _chapter_id_list.push_back (cur_id);
   }

   {
      auto it = command.options.find ("type");
      if (it != command.options.end ())
      {
         std::string type = it->second;
         std::string name;

         const ExpressionParagraph & paragraph
            = dynamic_cast <const ExpressionParagraph &> (**command.bodies.begin ());

         for (auto && expression_uptr : paragraph.expressions)
         {
            const auto & sub_expression = *expression_uptr;

            const ExpressionText * text_ptr = dynamic_cast <const ExpressionText *> (&sub_expression);

            if (text_ptr != nullptr)
            {
               name += text_ptr->body;
            }
         }

         std::string url = make_url (cur_id);

         if (type == "guide")
         {
            _guides [name] = url;
         }
         else if (type == "class")
         {
            _classes [name] = url;
         }
         else if (type == "method")
         {
            _methods [name] = url;
         }
      }
   }
}



/*
==============================================================================
Name : process
==============================================================================
*/

void  Toc::process (AbsoluteId & cur_id, const ExpressionCommand & command)
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

   cur_id [level] = ide;
   for (size_t i = level + 1 ; i < DEEPNESS ; ++i)
   {
      cur_id [i].clear ();
   }
}



/*
==============================================================================
Name : make
==============================================================================
*/

Toc::RelativeId   Toc::make (const std::string & ide) const
{
   RelativeId ret;

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



/*
==============================================================================
Name : make_url
Example :
   flip / reference / overview
   flip / reference / int / method
   -> int / method
   
   flip / guide / overview
   flip / reference / overview
   -> .. / reference / overview
==============================================================================
*/

std::string Toc::make_url (const AbsoluteId & ide) const
{
   if (_conf.format == Conf::Format::Html)
   {
      return make_base_url (_cur_id) + make_rel_url_html (ide);
   }
   else if (_conf.format == Conf::Format::GitHubMarkDown)
   {
      return make_base_url (_cur_id) + make_rel_url_github_markdown (ide);
   }
   else if (_conf.format == Conf::Format::DocSet)
   {
      return make_rel_url_html (ide);
   }
   else
   {
      return "";
   }
}



/*
==============================================================================
Name : make_base_url
Example :
   flip
   -> ./
   
   flip / reference
   -> ../

   flip / reference / overview
   -> ../
==============================================================================
*/

std::string Toc::make_base_url (const AbsoluteId & ide) const
{
   if (ide [1].empty ())
   {
      return "";
   }
   else
   {
      return "../";
   }
}



/*
==============================================================================
Name : make_rel_url_github_markdown
Example :
   flip
   -> README.md

   flip / reference
   -> reference/README.md

   flip / reference / overview
   -> reference/overview.md

   flip / reference / overview / first
   -> reference/overview.md#content-user-first
==============================================================================
*/

std::string Toc::make_rel_url_github_markdown (const AbsoluteId & ide) const
{
   if (ide [1].empty ())
   {
      return "README.md";
   }
   else if (ide [2].empty ())
   {
      return ide [1] + "/README.md";
   }
   else if (ide [3].empty ())
   {
      return ide [1] + "/" + ide [2] + ".md";
   }
   else
   {
      std::string ret = ide [1] + "/" + ide [2] + ".md";

      for (size_t i = 3 ; i < DEEPNESS ; ++i)
      {
         if (ide [i].empty ()) break;

         ret += (i == 3) ? "#" : "-";

         ret += ide [i];
      }

      return ret;
   }
}



/*
==============================================================================
Name : make_rel_url_html
==============================================================================
*/

std::string Toc::make_rel_url_html (const AbsoluteId & ide) const
{
   if (ide [1].empty ())
   {
      return "index.html";
   }
   else if (ide [2].empty ())
   {
      return ide [1] + "/index.html";
   }
   else if (ide [3].empty ())
   {
      return ide [1] + "/" + ide [2] + ".html";
   }
   else
   {
      std::string ret = ide [1] + "/" + ide [2] + ".html";

      for (size_t i = 3 ; i < DEEPNESS ; ++i)
      {
         if (ide [i].empty ()) break;

         ret += (i == 3) ? "#" : "-";

         ret += ide [i];
      }

      return ret;
   }
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

