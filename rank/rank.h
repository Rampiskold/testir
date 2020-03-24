#pragma once
#include <cstddef>
#if defined(rank_STATIC_DEFINE) || defined(rank_DLL_EXPORTALL)
#  define RANK_EXPORT
#  define RANK_NO_EXPORT
#else
# ifdef _WIN32
#  ifndef RANK_EXPORT
#    ifdef rank_EXPORTS
/* We are building this library */
#      define RANK_EXPORT __declspec(dllexport)
#    else
/* We are using this library */
#      define RANK_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef RANK_NO_EXPORT
#    define RANK_NO_EXPORT 
#  endif
# else //_WIN32 -> other
#  ifndef RANK_EXPORT
#    ifdef rank_EXPORTS
/* We are building this library */
#      define RANK_EXPORT __attribute__((visibility("default")))
#    else
/* We are using this library */
#      define RANK_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef RANK_NO_EXPORT
#    define RANK_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
# endif // _WIN32
#endif

RANK_EXPORT float  sumrank(size_t n, float rev=0.f);
RANK_EXPORT double sumrank(size_t n, double rev=0.);

RANK_EXPORT float  sumrank(float error, size_t* it, float* comperr, bool rev=false);
RANK_EXPORT double sumrank(double error, size_t* it, double* comperr, bool rev=false);
