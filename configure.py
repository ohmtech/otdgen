#!/usr/bin/env python
#
#     configure.py
#     Copyright (c) 2014 Raphael DINGE
#
#Tab=3########################################################################


##### IMPORT #################################################################

import argparse
import fileinput
import gyp
import logging
import os
import platform
import sys



##############################################################################

if sys.version_info < (2, 7):
   print >>sys.stderr, 'This script requires python 2.7 or greater.'
   sys.exit (1)

PATH_OTDGEN = os.path.dirname (__file__)
PATH_OTDGEN_PROJECTS = os.path.join (PATH_OTDGEN, 'projects')



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

   return arg_parser.parse_args (sys.argv[1:])



"""
==============================================================================
Name : process
==============================================================================
"""

def process (args):
   gyp_args = [
      '--depth=.',
      '--generator-output=%s' % PATH_OTDGEN_PROJECTS
   ]

   gyp.main (gyp_args + ['otdgen.gyp'])

   if platform.system () == 'Darwin':
      post_process_xcode (args)



"""
==============================================================================
Name : post_process_xcode
==============================================================================
"""

def post_process_xcode (args):
   file = os.path.join (PATH_OTDGEN_PROJECTS, 'otdgen.xcodeproj', 'project.pbxproj')

   for line in fileinput.input (file, inplace = 1):
      print line,

      if 'BuildIndependentTargetsInParallel' in line:
         print '\t\t\t\tLastUpgradeCheck = 2000;'


"""
==============================================================================
Name : configure
==============================================================================
"""

def configure (args):
   process (args)



##############################################################################

if __name__ == '__main__':
   sys.exit (configure (parse_args ()))
