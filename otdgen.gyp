##############################################################################
#
#     otdgen.gyp
#     Copyright (c) 2014 Raphael DINGE
#
#Tab=3########################################################################



{
   'variables': {
      'XCODE_ARCHS%': 'i386+x86_64',
   },

   'target_defaults': {

      'configurations': {
         'Debug': {
            'xcode_settings': {
               'GCC_OPTIMIZATION_LEVEL': '0', # -O0
            },
         },

         'Release': {
            'xcode_settings': {
               'GCC_OPTIMIZATION_LEVEL': 's', # -Os
            },
         },
      },

      'xcode_settings': {
         'conditions': [
            ["XCODE_ARCHS == 'x86_64'", {
               'ARCHS': ['x86_64'],
            }],
            ["XCODE_ARCHS == 'i386+x86_64'", {
               'ARCHS': ['i386', 'x86_64'],
            }],
         ],

         'CLANG_CXX_LANGUAGE_STANDARD': 'c++0x',
         'CLANG_CXX_LIBRARY': 'libc++',

         'ALWAYS_SEARCH_USER_PATHS': 'NO',
         'USE_HEADERMAP': 'NO',

         'CLANG_WARN__EXIT_TIME_DESTRUCTORS': 'NO',

         'CLANG_WARN__ARC_BRIDGE_CAST_NONARC': 'YES',
         'CLANG_WARN__DUPLICATE_METHOD_MATCH': 'YES',
         'CLANG_WARN_ASSIGN_ENUM': 'YES',
         'CLANG_WARN_BOOL_CONVERSION': 'YES',
         'CLANG_WARN_CONSTANT_CONVERSION': 'YES',
         'CLANG_WARN_CXX0X_EXTENSIONS': 'YES',
         'CLANG_WARN_DEPRECATED_OBJC_IMPLEMENTATIONS': 'YES',
         'CLANG_WARN_DIRECT_OBJC_ISA_USAGE': 'YES',
         'CLANG_WARN_DOCUMENTATION_COMMENTS': 'YES',
         'CLANG_WARN_EMPTY_BODY': 'YES',
         'CLANG_WARN_ENUM_CONVERSION': 'YES',
         'CLANG_WARN_IMPLICIT_SIGN_CONVERSION': 'YES',
         'CLANG_WARN_INT_CONVERSION': 'YES',
         'CLANG_WARN_OBJC_EXPLICIT_OWNERSHIP_TYPE': 'YES',
         'CLANG_WARN_OBJC_IMPLICIT_ATOMIC_PROPERTIES': 'YES',
         'CLANG_WARN_OBJC_IMPLICIT_RETAIN_SELF': 'YES',
         'CLANG_WARN_OBJC_MISSING_PROPERTY_SYNTHESIS': 'YES',
         'CLANG_WARN_OBJC_RECEIVER_WEAK': 'YES',
         'CLANG_WARN_OBJC_REPEATED_USE_OF_WEAK': 'YES',
         'CLANG_WARN_OBJC_ROOT_CLASS': 'YES',
         'CLANG_WARN_SUSPICIOUS_IMPLICIT_CONVERSION': 'YES',
         'CLANG_WARN_UNREACHABLE_CODE': 'YES',
         'GCC_TREAT_IMPLICIT_FUNCTION_DECLARATIONS_AS_ERRORS': 'YES',
         'GCC_TREAT_INCOMPATIBLE_POINTER_TYPE_WARNINGS_AS_ERRORS': 'YES',
         'GCC_WARN_64_TO_32_BIT_CONVERSION': 'YES',
         'GCC_WARN_ABOUT_DEPRECATED_FUNCTIONS': 'YES',
         'GCC_WARN_ABOUT_INVALID_OFFSETOF_MACRO': 'YES',
         'GCC_WARN_ABOUT_MISSING_FIELD_INITIALIZERS': 'YES',
         'GCC_WARN_ABOUT_MISSING_NEWLINE': 'YES',
         'GCC_WARN_ABOUT_MISSING_PROTOTYPES': 'YES',
         'GCC_WARN_ABOUT_POINTER_SIGNEDNESS': 'YES',
         'GCC_WARN_ABOUT_RETURN_TYPE': 'YES',
         'GCC_WARN_ALLOW_INCOMPLETE_PROTOCOL': 'YES',
         'GCC_WARN_CHECK_SWITCH_STATEMENTS': 'YES',
         'GCC_WARN_FOUR_CHARACTER_CONSTANTS': 'YES',
         'GCC_WARN_HIDDEN_VIRTUAL_FUNCTIONS': 'YES',
         'GCC_WARN_INITIALIZER_NOT_FULLY_BRACKETED': 'YES',
         'GCC_WARN_MISSING_PARENTHESES': 'YES',
         'GCC_WARN_MULTIPLE_DEFINITION_TYPES_FOR_SELECTOR': 'YES',
         'GCC_WARN_NON_VIRTUAL_DESTRUCTOR': 'YES',
         'GCC_WARN_PEDANTIC': 'YES',
         'GCC_WARN_SHADOW': 'YES',
         'GCC_WARN_SIGN_COMPARE': 'YES',
         'GCC_WARN_STRICT_SELECTOR_MATCH': 'YES',
         'GCC_WARN_TYPECHECK_CALLS_TO_PRINTF': 'YES',
         'GCC_WARN_UNDECLARED_SELECTOR': 'YES',
         'GCC_WARN_UNINITIALIZED_AUTOS': 'YES_AGGRESSIVE',
         'GCC_WARN_UNKNOWN_PRAGMAS': 'YES',
         'GCC_WARN_UNUSED_FUNCTION': 'YES',
         'GCC_WARN_UNUSED_LABEL': 'YES',
         'GCC_WARN_UNUSED_PARAMETER': 'YES',
         'GCC_WARN_UNUSED_VALUE': 'YES',
         'GCC_WARN_UNUSED_VARIABLE': 'YES',
      },

      'link_settings': {
         'libraries': [
            '$(SDKROOT)/System/Library/Frameworks/CoreFoundation.framework',
            '$(SDKROOT)/System/Library/Frameworks/CoreGraphics.framework',
            '$(SDKROOT)/System/Library/Frameworks/CoreServices.framework',
            '$(SDKROOT)/System/Library/Frameworks/ImageIO.framework',
         ],
      },
   },

   'targets' : [
      {
         'target_name': 'otdgen',
         'type': 'executable',

         'includes': [
            'otdgen_src.gypi',
         ],

         'sources': [
            'src/main.cpp',
         ],
      },
   ]
}
