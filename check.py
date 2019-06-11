#!/usr/bin/env python
#
#     check.py
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
import time
import uuid



##############################################################################

if sys.version_info < (2, 7):
   print >>sys.stderr, 'This script requires python 2.7 or greater.'
   sys.exit (1)

if platform.system () != 'Darwin':
   print >>sys.stderr, 'Unsupported platform. Otdgen is macOS only for now.'
   sys.exit (1)


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
Name : task_start
==============================================================================
"""

def task_start (name, id):
   if 'TRAVIS' in os.environ:
      logging.info ('travis_fold:start:%s' % id)
   timer = timer_start ()
   logging.info (name)
   return (name, id, timer)



"""
==============================================================================
Name : task_end
==============================================================================
"""

def task_end (t):
   name = t[0]
   id = t [1]
   timer = t [2]

   elapsed = timer_end (timer)

   if 'TRAVIS' in os.environ:
      logging.info ('travis_fold:end:%s' % id)
   else:
      logging.info ('%s in %ds' % (name, elapsed))



"""
==============================================================================
Name : timer_start
==============================================================================
"""

def timer_start ():
   id = uuid.uuid1().hex[0:10]

   if 'TRAVIS' in os.environ:
      logging.info ('travis_time:start:%s' % id)

   return (time.time (), id)



"""
==============================================================================
Name : timer_end
==============================================================================
"""

def timer_end (p):
   start = p[0]
   id = p[1]

   end = time.time ()
   elapsed = end - start

   start_d = int (round (start * 1000 * 1000 * 1000))
   end_d = int (round (end * 1000 * 1000 * 1000))
   elapsed_d = int (round (elapsed * 1000 * 1000 * 1000))

   if 'TRAVIS' in os.environ:
      logging.info ('travis_time:end:%s:start=%d,finish=%d,duration=%d' % (id, start_d, end_d, elapsed_d))

   return elapsed



"""
==============================================================================
Name : configure
==============================================================================
"""

def configure (args):
   task = task_start ('Configuring', 'configure')

   cmd = ['python', 'configure.py']

   if 'ARCHS' in os.environ:
      cmd += ['--archs', '%s' % os.environ ['ARCHS']]

   logging.info ('   %s' % ' '.join (cmd))

   subprocess.check_call (cmd)

   task_end (task)



"""
==============================================================================
Name : build
==============================================================================
"""

def build (args):
   task = task_start ('Building', 'build')

   cmd = ['python', 'build.py']

   cmd += ['--configuration', '%s' % os.environ ['CONFIGURATION']]

   if 'TARGET' in os.environ:
      cmd += ['--target', '%s' % os.environ ['TARGET']]

   logging.info ('   %s' % ' '.join (cmd))

   subprocess.check_call (cmd)

   task_end (task)



"""
==============================================================================
Name : run_target
==============================================================================
"""

def run_target (args, configuration, target):
   timer = timer_start ()

   logging.info ('Running %s' % target)

   cmd = ['python', 'run.py']

   cmd += ['--configuration', '%s' % configuration]
   cmd += ['--target', '%s' % target]

   subprocess.check_call (cmd)

   timer_end (timer)



"""
==============================================================================
Name : run
==============================================================================
"""

def run (args):
   task = task_start ('Running', 'run')

   configuration = os.environ ['CONFIGURATION']

   if 'TARGET' in os.environ:
      run_target (args, configuration, os.environ ['TARGET'])

   else:
      run_target (args, configuration, 'test_otdgen')

   task_end (task)




"""
==============================================================================
Name : check
==============================================================================
"""

def check (args):
   configure (args)
   build (args)
   run (args)



##############################################################################

if __name__ == '__main__':
   logging.basicConfig(format='%(message)s', level=logging.INFO, stream=sys.stdout)

   try:
      sys.exit (check (parse_args ()))
   except subprocess.CalledProcessError as error:
      print >>sys.stderr, 'Build command exited with %d' % error.returncode
      sys.exit(1)
