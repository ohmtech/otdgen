/*****************************************************************************

      GeneratorBase.cpp
      Copyright (c) 2015 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "GeneratorBase.h"

#include "Conf.h"

#include <fstream>
#include <iostream>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreServices/CoreServices.h>
#include <ImageIO/ImageIO.h>

#include <cassert>



namespace otdgen
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : ctor
==============================================================================
*/

GeneratorBase::GeneratorBase (const Conf & conf, const Toc & toc)
:  _conf (conf)
,  _toc (toc)
{
}



/*\\\ INTERNAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*
==============================================================================
Name : write
==============================================================================
*/

void  GeneratorBase::write (const std::string & rel_path, const std::string & content)
{
   if (_conf.output_path.empty ())
   {
      std::cout << content;
      std::cout << "==========================\n\n";
   }
   else
   {
      // make the dirs

      make_dirs (rel_path);

      // fill content

      std::string path = _conf.output_path + "/" + rel_path;

      std::ofstream ofs (path, std::ifstream::binary);
      assert (ofs);

      ofs.write (&content [0], int (content.size ()));

      ofs.close ();
   }
}



/*
==============================================================================
Name : make_dirs
==============================================================================
*/

void  GeneratorBase::make_dirs (const std::string & rel_path)
{
   std::string path = _conf.output_path + "/" + rel_path;

   size_t pos = path.rfind ("/");
   assert (pos != std::string::npos);

   std::string basepath = path.substr (0, pos - 0);

   std::string cmd = "mkdir -p " + basepath;
   system (cmd.c_str ());
}



/*
==============================================================================
Name : conf
==============================================================================
*/

const Conf &   GeneratorBase::conf () const
{
   return _conf;
}



/*
==============================================================================
Name : toc
==============================================================================
*/

const Toc & GeneratorBase::toc () const
{
   return _toc;
}



/*
==============================================================================
Name : escape_xml
==============================================================================
*/

std::string GeneratorBase::escape_xml (const std::string & txt)
{
   std::string ret;

   for (auto && c : txt)
   {
      if (c == '"')
      {
         ret += "&quot;";
      }
      else if (c == '&')
      {
         ret += "&amp;";
      }
      else if (c == '\'')
      {
         ret += "&apos;";
      }
      else if (c == '<')
      {
         ret += "&lt;";
      }
      else if (c == '>')
      {
         ret += "&gt;";
      }
      else
      {
         ret.push_back (c);
      }
   }

   return ret;
}



/*
==============================================================================
Name : escape_pourcent
Reference :
   http://en.wikipedia.org/wiki/Percent-encoding
==============================================================================
*/

std::string GeneratorBase::escape_pourcent (const std::string & txt)
{
   std::string ret;

   for (auto && c : txt)
   {
      if (c == ' ')
      {
         ret += "%20";
      }
      else if (c == '!')
      {
         ret += "%21";
      }
      else if (c == '#')
      {
         ret += "%23";
      }
      else if (c == '$')
      {
         ret += "%24";
      }
      else if (c == '&')
      {
         ret += "%26";
      }
      else if (c == '\'')
      {
         ret += "%27";
      }
      else if (c == '(')
      {
         ret += "%28";
      }
      else if (c == ')')
      {
         ret += "%29";
      }
      else if (c == '*')
      {
         ret += "%2A";
      }
      else if (c == '+')
      {
         ret += "%2B";
      }
      else if (c == ',')
      {
         ret += "%2C";
      }
      else if (c == '/')
      {
         ret += "%2F";
      }
      else if (c == ':')
      {
         ret += "%3A";
      }
      else if (c == ';')
      {
         ret += "%3B";
      }
      else if (c == '<')
      {
         ret += "%3C";
      }
      else if (c == '=')
      {
         ret += "%3D";
      }
      else if (c == '>')
      {
         ret += "%3E";
      }
      else if (c == '?')
      {
         ret += "%3F";
      }
      else if (c == '@')
      {
         ret += "%40";
      }
      else if (c == '[')
      {
         ret += "%5B";
      }
      else if (c == ']')
      {
         ret += "%5D";
      }
      else
      {
         ret.push_back (c);
      }
   }

   return ret;
}



/*
==============================================================================
Name : convert_image
==============================================================================
*/

std::string GeneratorBase::convert_image (const std::vector <std::string> & cur, const std::string & src_path)
{
   size_t pos = src_path.rfind ("/");
   if (pos == std::string::npos)
   {
      pos = 0;
   }
   else
   {
      pos += 1;
   }

   size_t pos_pdf = src_path.rfind (".pdf");
   size_t pos_svg = src_path.rfind (".svg");

   std::string filename;

   if (pos_pdf != std::string::npos)
   {
      filename = src_path.substr (pos, pos_pdf - pos);
   }
   else if (pos_svg != std::string::npos)
   {
      filename = src_path.substr (pos, pos_svg - pos);
   }
   else
   {
      return "";
   }


   assert (cur.size () >= 2);

   std::string dst_base_path;

   if (conf ().format == Conf::Format::DocSet)
   {
      dst_base_path = _conf.output_path + "/" + cur [0] + ".docset/Contents/Resources/Documents/" + cur [1] + "/";
   }
   else
   {
      dst_base_path = _conf.output_path + "/" + cur [1] + "/";
   }

   if (_conf.output_path.empty ()) return "";   // abort

   //
   std::string rel_path;

   if (pos_pdf != std::string::npos)
   {
      rel_path = filename + ".png";
      make_dirs (rel_path);

      convert_pdf_to_png (dst_base_path + rel_path, src_path);
   }
   else if (pos_svg != std::string::npos)
   {
      if (conf ().format == Conf::Format::GitHubMarkDown)
      {
         // GitHub bug: https://github.com/isaacs/github/issues/316

         rel_path = filename + ".png";
         make_dirs (rel_path);

         convert_svg_to_png (dst_base_path + rel_path, src_path);
      }
      else
      {
         rel_path = filename + ".svg";
         make_dirs (rel_path);

         std::string cmd = "cp " + src_path + " " + dst_base_path + rel_path;
         system (cmd.c_str ());
      }
   }

   return rel_path;
}



/*
==============================================================================
Name : convert_pdf_to_png
==============================================================================
*/

void  GeneratorBase::convert_pdf_to_png (const std::string & dst_path, const std::string & src_path)
{
   /*
   --output=/Users/raf/Desktop/dev/otdgen/test
   --format=html
   /Users/raf/Desktop/dev/otdgen/test/test.otd
   */

   auto path_ref = CFStringCreateWithCString (0, src_path.c_str (), kCFStringEncodingUTF8);
   auto url_ref = CFURLCreateWithFileSystemPath (0, path_ref, kCFURLPOSIXPathStyle, 0);
   CFRelease (path_ref);
   path_ref = 0;

   auto document_ref = CGPDFDocumentCreateWithURL (url_ref);
   CFRelease (url_ref);
   url_ref = 0;

   assert (CGPDFDocumentGetNumberOfPages (document_ref) == 1);

   auto page_ref = CGPDFDocumentGetPage (document_ref, 1);
   auto rect = CGPDFPageGetBoxRect (page_ref, kCGPDFMediaBox);

   size_t width = size_t (ceil (rect.size.width));
   size_t height = size_t (ceil (rect.size.height));

   // draw

   auto color_space_ref = CGColorSpaceCreateWithName (kCGColorSpaceSRGB);

   std::vector <uint8_t> data;
   data.resize (size_t (width * height * 4));

   auto context_ref = CGBitmapContextCreate (
      &data [0], width, height, 8, width * 4, color_space_ref, kCGImageAlphaPremultipliedLast
   );

   CGColorSpaceRelease (color_space_ref);

   CGContextDrawPDFPage (context_ref, page_ref);

   CGPDFDocumentRelease (document_ref);
   document_ref = 0;

   // save

   auto image_ref = CGBitmapContextCreateImage (context_ref);

   CGContextRelease (context_ref);

   path_ref = CFStringCreateWithCString (0, dst_path.c_str (), kCFStringEncodingUTF8);
   url_ref = CFURLCreateWithFileSystemPath (0, path_ref, kCFURLPOSIXPathStyle, 0);
   CFRelease (path_ref);
   path_ref = 0;

   auto destination_ref = CGImageDestinationCreateWithURL (url_ref, kUTTypePNG, 1, 0);
   CFRelease (url_ref);
   url_ref = 0;

   CGImageDestinationAddImage (destination_ref, image_ref, 0);

   CGImageDestinationFinalize (destination_ref);

   CFRelease (destination_ref);
}



/*
==============================================================================
Name : convert_svg_to_png
==============================================================================
*/

void  GeneratorBase::convert_svg_to_png (const std::string & dst_path, const std::string & src_path)
{
   // requires librsvg:
   // brew install librsvg

   std::string cmd = "/usr/local/bin/rsvg-convert " + src_path + " > " + dst_path;
   system (cmd.c_str ());
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace otdgen



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

