##############################################################################
#
#     test.gypi
#     Copyright (c) 2015 Raphael DINGE
#
#Tab=3########################################################################



{
   'targets' : [
      {
         'target_name': 'test_otdgen',
         'type': 'executable',

         'includes': [
            '../otdgen_src.gypi',
            'src.gypi',
         ],
      },
   ],
}
