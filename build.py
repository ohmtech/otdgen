#!/usr/bin/env python
#
#     build.py
#     Copyright (c) 2014 Raphael DINGE
#
#Tab=3########################################################################


##### IMPORT #################################################################

import argparse
import fileinput
import logging
import multiprocessing
import os
import platform
import subprocess
import sys



##############################################################################

if sys.version_info < (2, 7):
   print >>sys.stderr, 'This script requires python 2.7 or greater.'
   sys.exit (1)

if platform.system () != 'Darwin':
   print >>sys.stderr, 'Unsupported platform. Otdgen is macOS only for now.'
   sys.exit (1)

PATH_OTDGEN = os.path.abspath (os.path.dirname (__file__))



"""
==============================================================================
Name : parse_args
==============================================================================
"""

def parse_args ():
   arg_parser = argparse.ArgumentParser ()

   arg_parser.add_argument (
      '-q', '--quiet',
      dest = 'logging_level', default = logging.INFO,
      action = 'store_const', const = logging.ERROR,
      help = 'Provides less output.'
   )

   arg_parser.add_argument (
      '-v', '--verbose',
      dest = 'logging_level', default = logging.INFO,
      action = 'store_const', const = logging.DEBUG,
      help = 'Provides more output.'
   )

   arg_parser.add_argument(
      '-c', '--configuration',
      default = 'Release',
      choices = ['Debug', 'Release'],
      help = 'The build configuration to use. Defaults to Release'
   )

   arg_parser.add_argument(
      '-t', '--target',
      default = '',
      help = 'The build target to use.'
   )

   arg_parser.add_argument (
      '--output-path',
      default = 'projects',
      help = 'The relative path from this folder to output the project. Defaults to projects'
   )

   return arg_parser.parse_args (sys.argv[1:])



"""
==============================================================================
Name : get_path_otdgen_projects
==============================================================================
"""

def get_path_otdgen_projects (args):
   return os.path.join (PATH_OTDGEN, args.output_path)



"""
==============================================================================
Name : build_osx
==============================================================================
"""

def build_osx (args):
   conf_dir = os.path.join (get_path_otdgen_projects (args), 'build', args.configuration)

   if not os.path.exists (conf_dir):
      os.makedirs (conf_dir)

   cmd = '/Applications/Xcode.app/Contents/Developer/usr/bin/xcodebuild '
   cmd += '-project %s ' % os.path.join (get_path_otdgen_projects (args), 'otdgen.xcodeproj')
   cmd += '-configuration %s ' % args.configuration

   if args.target:
      cmd += '-target %s ' % args.target
      cmd += '-parallelizeTargets '

   cmd += 'SYMROOT=%s ' % os.path.join (get_path_otdgen_projects (args), 'build')
   cmd += '| xcpretty -c && exit ${PIPESTATUS[0]}'

   return subprocess.check_call (cmd, shell = True)



"""
==============================================================================
Name : build
==============================================================================
"""

def build (args):
   if platform.system () == 'Darwin':
      return build_osx (args)



##############################################################################

if __name__ == '__main__':
   try:
      sys.exit (build (parse_args ()))
   except subprocess.CalledProcessError as error:
      print >>sys.stderr, 'Build command exited with %d' % error.returncode
      sys.exit (1)
