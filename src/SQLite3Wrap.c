/*****************************************************************************

      SQLite3Wrap.c
      Copyright (c) 2014 Raphael DINGE

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



#if defined (__clang__)
   #pragma clang diagnostic push
   #pragma clang diagnostic ignored "-Wsign-conversion"
   #pragma clang diagnostic ignored "-Wconversion"
   #pragma clang diagnostic ignored "-Wundef"
   #pragma clang diagnostic ignored "-Wmissing-variable-declarations"
   #pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
   #pragma clang diagnostic ignored "-Wcast-align"
   #pragma clang diagnostic ignored "-Wambiguous-macro"
   #pragma clang diagnostic ignored "-Wparentheses-equality"
   #pragma clang diagnostic ignored "-Wunused-value"

   #if __has_warning ("-Wreserved-id-macro")
      #pragma clang diagnostic ignored "-Wreserved-id-macro"
   #endif

   #if __has_warning ("-Wcast-qual")
      #pragma clang diagnostic ignored "-Wcast-qual"
   #endif

   #if __has_warning ("-Wdouble-promotion")
      #pragma clang diagnostic ignored "-Wdouble-promotion"
   #endif

   #if __has_warning ("-Wcomma")
      #pragma clang diagnostic ignored "-Wcomma"
   #endif

   #define SQLITE_API __attribute__ ((visibility ("hidden")))

#elif defined (__GNUC__)
   #pragma GCC diagnostic push
   #pragma GCC diagnostic ignored "-Wlong-long"
   #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

#elif defined (_MSC_VER)
   #pragma warning (push)
   #pragma warning (disable: 4242)
   #pragma warning (disable: 4255)
   #pragma warning (disable: 4456)
   #pragma warning (disable: 4668)

#endif

#include "sqlite3.c"

#if defined (__clang__)
   #pragma clang diagnostic pop

#elif defined (__GNUC__)
   #pragma GCC diagnostic pop

#elif defined (_MSC_VER)
   #pragma warning (pop)

#endif



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

