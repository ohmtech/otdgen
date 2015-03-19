/*****************************************************************************

      TestSyntaxicAnalyser.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "TestSyntaxicAnalyser.h"

#include "LexicalAnalyser.h"
#include "SyntaxicAnalyser.h"

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run
==============================================================================
*/

void  TestSyntaxicAnalyser::run ()
{
   run_001 ();
   run_002 ();
   run_003 ();
   run_004 ();
   run_005 ();
   run_006 ();
   run_007 ();
   run_008 ();
   run_009 ();
   run_010 ();
   run_011 ();
   run_012 ();
   run_013 ();
   run_014 ();
   run_015 ();
   run_016 ();
   run_017 ();
   run_018 ();
   run_019 ();
   run_020 ();
   run_021 ();
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : run_001
==============================================================================
*/

void  TestSyntaxicAnalyser::run_001 ()
{
   std::string source = "/********/";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();
   auto tokens2 = syntaxic.tokens ();

   Tokens tokens3;

   assert (tokens2 == tokens3);
}



/*
==============================================================================
Name : run_002
==============================================================================
*/

void  TestSyntaxicAnalyser::run_002 ()
{
   std::string source = "test // some comment\n";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();
   auto tokens2 = syntaxic.tokens ();

   Tokens tokens3;
   tokens3.emplace_back ("test ");

   assert (tokens2 == tokens3);
}



/*
==============================================================================
Name : run_003
==============================================================================
*/

void  TestSyntaxicAnalyser::run_003 ()
{
   std::string source = "/********";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();
   auto tokens2 = syntaxic.tokens ();

   Tokens tokens3;

   assert (tokens2 == tokens3);
}



/*
==============================================================================
Name : run_004
==============================================================================
*/

void  TestSyntaxicAnalyser::run_004 ()
{
   std::string source = "test // some comment";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();
   auto tokens2 = syntaxic.tokens ();

   Tokens tokens3;
   tokens3.emplace_back ("test ");

   assert (tokens2 == tokens3);
}



/*
==============================================================================
Name : run_005
==============================================================================
*/

void  TestSyntaxicAnalyser::run_005 ()
{
   std::string source = "Hello world !";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   root.add_paragraph ().add_text ("Hello world !");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_006
==============================================================================
*/

void  TestSyntaxicAnalyser::run_006 ()
{
   std::string source = "\\code {c}";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   root.add_paragraph ().add_command ("\\code").add_paragraph ().add_text ("c");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_007
==============================================================================
*/

void  TestSyntaxicAnalyser::run_007 ()
{
   std::string source = "A\\code {c}";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   Paragraph & p = root.add_paragraph ();
   p.add_text ("A");
   p.add_command ("\\code").add_paragraph ().add_text ("c");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_008
==============================================================================
*/

void  TestSyntaxicAnalyser::run_008 ()
{
   std::string source = "A \\code {c}B // AB";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   Paragraph & p = root.add_paragraph ();
   p.add_text ("A ");
   p.add_command ("\\code").add_paragraph ().add_text ("c");
   p.add_text ("B");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_009
==============================================================================
*/

void  TestSyntaxicAnalyser::run_009 ()
{
   std::string source = "Hello\nWorld";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   root.add_paragraph ().add_text ("Hello World");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_010
==============================================================================
*/

void  TestSyntaxicAnalyser::run_010 ()
{
   std::string source = "Hello\n\nWorld";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   root.add_paragraph ().add_text ("Hello");
   root.add_paragraph ().add_text ("World");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_011
==============================================================================
*/

void  TestSyntaxicAnalyser::run_011 ()
{
   std::string source = "\\chapter [id=opt] {Hello world !}";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   Command & command = root.add_command ("\\chapter");
   command.options ["id"] = "opt";
   command.add_paragraph ().add_text ("Hello world !");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_012
==============================================================================
*/

void  TestSyntaxicAnalyser::run_012 ()
{
   std::string source = "\\chapter [id=opt] { Hello \\code {world} ! }";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   Command & command = root.add_command ("\\chapter");
   command.options ["id"] = "opt";
   Paragraph & paragraph = command.add_paragraph ();
   paragraph.add_text ("Hello ");
   paragraph.add_command ("\\code").add_paragraph ().add_text ("world");
   paragraph.add_text (" !");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_013
==============================================================================
*/

void  TestSyntaxicAnalyser::run_013 ()
{
   std::string source = "1 \n\n 2 \n\n 3";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   root.add_paragraph ().add_text ("1");
   root.add_paragraph ().add_text ("2");
   root.add_paragraph ().add_text ("3");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_014
==============================================================================
*/

void  TestSyntaxicAnalyser::run_014 ()
{
   std::string source = "\\image {a.pdf} {caption}";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   Command & command = root.add_paragraph ().add_command ("\\image");
   command.add_paragraph ().add_text ("a.pdf");
   command.add_paragraph ().add_text ("caption");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_015
==============================================================================
*/

void  TestSyntaxicAnalyser::run_015 ()
{
   std::string source = "\\subsection [id=front, decoration=box] {front}";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   Command & command = root.add_command ("\\subsection");
   command.options ["id"] = "front";
   command.options ["decoration"] = "box";
   command.add_paragraph ().add_text ("front");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_016
==============================================================================
*/

void  TestSyntaxicAnalyser::run_016 ()
{
   std::string source;
   source += "\\codeblock [language=c++] ***\n";
   source += "#include \"blabla\" 	\\fade\n";
   source += "foo\n";
   source += "// some comment\n";
   source += "// some important comment\\emph\n";
   source += "*** { Example use of it }\n";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   CodeBlock & codeblock = root.add_codeblock ();
   codeblock.options ["language"] = "c++";
   codeblock.add_line ("#include \"blabla\"", CodeBlock::Style::Fade);
   codeblock.add_line ("foo", CodeBlock::Style::Normal);
   codeblock.add_line ("// some comment", CodeBlock::Style::Normal);
   codeblock.add_line ("// some important comment", CodeBlock::Style::Emph);
   codeblock.add_paragraph ().add_text ("Example use of it");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_017
==============================================================================
*/

void  TestSyntaxicAnalyser::run_017 ()
{
   std::string source = "#include \"something.otd\"";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   root.add_include ("something.otd");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_018
==============================================================================
*/

void  TestSyntaxicAnalyser::run_018 ()
{
   std::string source = "\\code {c}\\code {b}";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   Paragraph & paragraph = root.add_paragraph ();
   paragraph.add_command ("\\code").add_paragraph ().add_text ("c");
   paragraph.add_command ("\\code").add_paragraph ().add_text ("b");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_019
==============================================================================
*/

void  TestSyntaxicAnalyser::run_019 ()
{
   std::string source = "\n\nHello";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   root.add_paragraph ().add_text ("Hello");

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_020
==============================================================================
*/

void  TestSyntaxicAnalyser::run_020 ()
{
   std::string source;
   source += "\\code {B}\n\n";
   source += "\\codeblock ***\n";
   source += "***\n";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   root.add_paragraph ().add_command ("\\code").add_paragraph ().add_text ("B");
   root.add_codeblock ();

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



/*
==============================================================================
Name : run_021
==============================================================================
*/

void  TestSyntaxicAnalyser::run_021 ()
{
   std::string source;
   source += "\\codeblock ***\n";
   source += "test\n\n";
   source += "test\n";
   source += "***\n";

   LexicalAnalyser lexical;
   auto tokens = lexical.process (source);

   SyntaxicAnalyser syntaxic (tokens, source, "<context>");
   syntaxic.process ();

   Root root;
   CodeBlock & codeblock = root.add_codeblock ();
   codeblock.add_line ("test", CodeBlock::Style::Normal);
   codeblock.add_line ("", CodeBlock::Style::Normal);
   codeblock.add_line ("test", CodeBlock::Style::Normal);

   //syntaxic.root ().trace ();

   assert (root == syntaxic.root ());
}



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

