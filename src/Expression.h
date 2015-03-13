/*****************************************************************************

      Expression.h
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <list>
#include <map>
#include <memory>
#include <string>



namespace otdgen
{



class Expression
{
public:
   virtual        ~Expression () {}
   virtual bool   operator == (const Expression & rhs) const = 0;
   virtual void   trace (size_t icnt) const = 0;

protected:
   void           indent (size_t cnt) const;
};

using Expressions = std::list <std::shared_ptr <Expression>>;

class Command;
class CodeBlock;
class Include;
class List;
class Paragraph;
class Row;
class Table;
class Text;

class Root : public Expression
{
public:
   Command &      add_command (std::string name);
   CodeBlock &    add_codeblock ();
   Include &      add_include (std::string path);
   Paragraph &    add_paragraph ();
   List &         add_list_itemize ();
   List &         add_list_enumerate ();
   Table &        add_table ();

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt = 0) const override;

   Expressions    expressions;

}; // class Root

class Command : public Expression
{
public:
   Command &      add_command (std::string name);
   Paragraph &    add_paragraph ();

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   std::string    name;
   std::map <std::string, std::string>
                  options;
   Expressions    bodies;

}; // class Command

class List : public Expression
{
public:
   enum class Type
   {
                  Itemize,
                  Enumerate,
   };

   Paragraph &    add_item ();

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   Type           type;
   Expressions    items;

}; // class List

class Table : public Expression
{
public:
   Row &          add_row ();

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   Expressions    rows;

}; // class Table

class Row : public Expression
{
public:
   Paragraph &   add_cell ();

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   Expressions    cells;

}; // class Row

class CodeBlock : public Expression
{
public:
   enum class Style
   {
                  Normal,
                  Fade,
                  Emph,
   };
   void           add_line (std::string line, Style style);
   Paragraph &    add_paragraph ();

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   std::map <std::string, std::string>
                  options;
   std::list <std::pair <std::string, Style>>
                  lines;
   Expressions    captions;


}; // class CodeBlock

class Include : public Expression
{
public:
   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   std::string    path;


}; // class Include

class Paragraph : public Expression
{
public:
   Text &         add_text (std::string text);
   Command &      add_command (std::string name);

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   Expressions    expressions;

}; // class Paragraph

class Text : public Expression
{
public:
   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   std::string    body;

}; // class Text



}  // namespace otdgen



// #include "Expression.hpp"



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

