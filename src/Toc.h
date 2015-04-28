/*****************************************************************************

      Toc.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>



namespace otdgen
{



class Expression;
class ExpressionCommand;
class ExpressionRoot;

class Toc
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  Toc () = default;
   virtual        ~Toc () = default;

   void           process (const ExpressionRoot & root);

   std::vector <std::string>
                  find (std::vector <std::string> cur, const std::string & ide) const;
   std::string    get_name (std::vector <std::string> cur) const;
   std::list <std::pair <std::vector <std::string>, std::string>>
                  get_toc (std::vector <std::string> cur) const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           process (std::vector <std::string> & cur_id, const Expression & expression);
   bool           process (std::vector <std::string> & cur_id, const ExpressionCommand & command);

   std::string    make_undecorated_name (const ExpressionCommand & command);

   std::vector <std::string>
                  split (const std::string & ide) const;

   std::set <std::vector <std::string>>
                  _id_set;

   std::map <std::vector <std::string>, std::string>
                  _id_name_map;
   std::list <std::pair <std::vector <std::string>, std::string>>
                  _id_name_list;




/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Toc (const Toc & rhs) = delete;
                  Toc (Toc && rhs) = delete;
   Toc &          operator = (const Toc & rhs) = delete;
   Toc &          operator = (Toc && rhs) = delete;
   bool           operator == (const Toc & rhs);
   bool           operator != (const Toc & rhs);



}; // class Toc



}  // namespace otdgen



// #include "Toc.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

