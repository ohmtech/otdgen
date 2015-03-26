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

class ExpressionCommand;
class ExpressionCodeBlock;
class ExpressionInclude;
class ExpressionList;
class ExpressionParagraph;
class ExpressionRow;
class ExpressionTable;
class ExpressionText;

class ExpressionRoot : public Expression
{
public:
   ExpressionCommand &
                  add_command (std::string name);
   ExpressionCodeBlock &
                  add_codeblock ();
   ExpressionInclude &
                  add_include (std::string path);
   ExpressionParagraph &
                  add_paragraph ();
   ExpressionList &
                  add_list_itemize ();
   ExpressionList &
                  add_list_enumerate ();
   ExpressionTable &
                  add_table ();

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt = 0) const override;

   Expressions    expressions;

}; // class Root

class ExpressionCommand : public Expression
{
public:
   ExpressionCommand &
                  add_command (std::string name);
   ExpressionParagraph &
                  add_paragraph ();

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   std::string    name;
   std::map <std::string, std::string>
                  options;
   Expressions    bodies;

}; // class Command

class ExpressionList : public Expression
{
public:
   enum class Type
   {
                  Itemize,
                  Enumerate,
   };

   ExpressionParagraph &
                  add_item ();

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   Type           type;
   Expressions    items;

}; // class List

class ExpressionTable : public Expression
{
public:
   ExpressionRow &
                  add_row ();

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   Expressions    rows;

}; // class Table

class ExpressionRow : public Expression
{
public:
   ExpressionParagraph &
                  add_cell ();

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   Expressions    cells;

}; // class Row

class ExpressionCodeBlock : public Expression
{
public:
   enum class Style
   {
                  Normal,
                  Fade,
                  Emph,
   };
   void           add_line (std::string line, Style style);
   ExpressionParagraph &
                  add_paragraph ();

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   std::map <std::string, std::string>
                  options;
   std::list <std::pair <std::string, Style>>
                  lines;
   Expressions    captions;


}; // class CodeBlock

class ExpressionInclude : public Expression
{
public:
   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   std::string    path;


}; // class Include

class ExpressionParagraph : public Expression
{
public:
   ExpressionText &
                  add_text (std::string text);
   ExpressionCommand &
                  add_command (std::string name);

   // Expression
   virtual bool   operator == (const Expression & rhs) const override;
   virtual void   trace (size_t icnt) const override;

   Expressions    expressions;

}; // class Paragraph

class ExpressionText : public Expression
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

