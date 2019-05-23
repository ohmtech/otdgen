#!/usr/bin/env python
#
#     install.py
#     Copyright (c) 2018 Raphael DINGE
#
#Tab=3########################################################################

import logging
import os
import platform
import shutil
import sys



PATH_THIS = os.path.abspath (os.path.dirname (__file__))
PATH_XCODE = os.path.join (os.path.expanduser ('~'), 'Library', 'Developer', 'Xcode')
PATH_XCODE_PLUGINS = os.path.join (PATH_XCODE, 'Plug-ins')
PATH_XCODE_SPECS = os.path.join (PATH_XCODE, 'Specifications')


if __name__ == '__main__':

   logging.basicConfig (format = '%(message)s', level = logging.INFO, stream = sys.stdout)

   if platform.system () != 'Darwin':
      logging.error ('Unsupported platform')
      sys.exit (1)

   if not os.path.exists (PATH_XCODE_PLUGINS):
      os.makedirs (PATH_XCODE_PLUGINS)

   if not os.path.exists (PATH_XCODE_SPECS):
      os.makedirs (PATH_XCODE_SPECS)

   logging.info ('Copying otd.ideplugin')

   shutil.rmtree (os.path.join (PATH_XCODE_PLUGINS, 'otd.ideplugin'), ignore_errors = True)

   shutil.copytree (
      os.path.join (PATH_THIS, 'otd.ideplugin'),
      os.path.join (PATH_XCODE_PLUGINS, 'otd.ideplugin')
   )

   logging.info ('Copying otd.xclangspec')

   shutil.copyfile (
      os.path.join (PATH_THIS, 'otd.xclangspec'),
      os.path.join (PATH_XCODE_SPECS, 'otd.xclangspec')
   )
