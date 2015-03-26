/*****************************************************************************

      Toc.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>



namespace otdgen
{



class Conf;
class Expression;
class ExpressionCommand;
class ExpressionRoot;

class Toc
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

   using NamePathMap = std::map <std::string, std::string>;

                  Toc (const Conf & conf);
   virtual        ~Toc () = default;

   void           process (const ExpressionRoot & root);
   void           set_current (const ExpressionCommand & command);
   std::string    make_url (const std::string & ide) const;
   std::string    make_url_previous_chapter () const;
   std::string    make_url_next_chapter () const;

   const NamePathMap &
                  guides () const;
   const NamePathMap &
                  classes () const;
   const NamePathMap &
                  methods () const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum {         DEEPNESS = 6 };

   using AbsoluteId = std::array <std::string, DEEPNESS>;
   using RelativeId = std::vector <std::string>;

   void           process (AbsoluteId & cur_id, const Expression & expression);
   void           process (AbsoluteId & cur_id, const ExpressionCommand & command);

   RelativeId     make (const std::string & ide) const;
   std::string    make_url (const AbsoluteId & ide) const;
   std::string    make_base_url (const AbsoluteId & ide) const;
   std::string    make_rel_url_github_markdown (const AbsoluteId & ide) const;
   std::string    make_rel_url_html (const AbsoluteId & ide) const;

   const Conf &   _conf;

   NamePathMap    _guides;
   NamePathMap    _classes;
   NamePathMap    _methods;

   AbsoluteId     _cur_id;
   std::set <AbsoluteId>
                  _id_set;
   std::list <AbsoluteId>
                  _chapter_id_list;




/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  Toc () = delete;
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

