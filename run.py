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

   arg_parser.add_argument(
      '-c', '--configuration',
      default = 'Release',
      choices = ['Debug', 'Release'],
      help = 'The build configuration to use. Defaults to Release'
   )

   arg_parser.add_argument(
      '-t', '--target',
      help = 'The build target to use'
   )

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
Name : get_executables_path
==============================================================================
"""

def get_executables_path (args):
   if platform.system () == 'Darwin':
      return os.path.join (get_path_otdgen_projects (args), 'build', args.configuration)



"""
==============================================================================
Name : get_executable_filename
==============================================================================
"""

def get_executable_filename (args):
   return args.target



"""
==============================================================================
Name : run
==============================================================================
"""

def run (args):
   subprocess.check_call (
      [os.path.join (get_executables_path (args), get_executable_filename (args))],
      cwd = get_executables_path (args)
   )



##############################################################################

if __name__ == '__main__':
   logging.basicConfig (format='%(message)s', level=logging.INFO, stream=sys.stdout)

   try:
      sys.exit (run (parse_args ()))
   except subprocess.CalledProcessError as error:
      print >>sys.stderr, 'Run command exited with %d' % error.returncode
      sys.exit(1)
