/*****************************************************************************

      Toc.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <array>
#include <set>
#include <string>
#include <vector>



namespace otdgen
{



class Command;
class Conf;
class Expression;
class Root;

class Toc
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

                  Toc (const Conf & conf);
   virtual        ~Toc () = default;

   void           process (const Root & root);
   void           set_current (const Command & command);
   std::string    make_url (const std::string & ide) const;



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   enum {         DEEPNESS = 6 };

   using AbsoluteId = std::array <std::string, DEEPNESS>;
   using RelativeId = std::vector <std::string>;

   void           process (AbsoluteId & cur_id, const Expression & expression);
   void           process (AbsoluteId & cur_id, const Command & command);

   RelativeId     make (const std::string & ide) const;
   std::string    make_url (const AbsoluteId & ide) const;
   std::string    make_base_url (const AbsoluteId & ide) const;
   std::string    make_rel_url_github_markdown (const AbsoluteId & ide) const;

   const Conf &   _conf;

   AbsoluteId     _cur_id;
   std::set <AbsoluteId>
                  _id_set;



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

