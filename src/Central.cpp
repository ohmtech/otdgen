/*****************************************************************************

      Central.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "Central.h"

#include "LexicalAnalyser.h"
#include "SyntaxicAnalyser.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : process
==============================================================================
*/

ExpressionRoot  Central::process (const std::string & path)
{
   std::string source;
   bool ok_flag = read (source, path);

   if (!ok_flag)
   {
      std::cout << "Cannot open file '" << path << "'\n";
      throw std::runtime_error ("");
   }

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, path);
   syntaxic.process ();

   auto root = syntaxic.root ();

   auto it = root.expressions.begin ();
   const auto it_end = root.expressions.end ();

   for (; it != it_end ;)
   {
      auto it_next = it;
      ++it_next;

      auto & expression = **it;

      auto include_ptr = dynamic_cast <ExpressionInclude *> (&expression);

      if (include_ptr != nullptr)
      {
         std::string sub_path = resolve (include_ptr->path, path);

         ExpressionRoot sub_root = process (sub_path);

         root.expressions.erase (it);

         root.expressions.splice (it_next, std::move (sub_root.expressions));
      }

      it = it_next;
   }

   return root;
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : read
==============================================================================
*/

bool  Central::read (std::string & content, const std::string & path)
{
   // read file

   std::ifstream ifs (path, std::ifstream::binary);

   if (!ifs) return false;

   ifs.seekg (0, std::ios::end);
   auto file_size = ifs.tellg ();
   ifs.seekg (0, std::ios::beg);

   content.resize (size_t (file_size));
   ifs.read (&content [0], int (file_size));

   ifs.close ();

   return true;
}



/*
==============================================================================
Name : resolve
==============================================================================
*/

std::string  Central::resolve (const std::string & rel_path, const std::string & path)
{
   size_t pos = path.rfind ("/");
   assert (pos != std::string::npos);

   return path.substr (0, pos - 0) + "/" + rel_path;
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

