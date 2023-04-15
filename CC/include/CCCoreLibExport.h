
#ifndef CC_CORE_LIB_API_H
#define CC_CORE_LIB_API_H

#ifdef CC_CORE_LIB_STATIC_DEFINE
#  define CC_CORE_LIB_API
#  define CC_CORE_LIB_NO_EXPORT
#else
#  ifndef CC_CORE_LIB_API
#    ifdef CC_CORE_LIB_EXPORTS
        /* We are building this library */
#      define CC_CORE_LIB_API 
#    else
        /* We are using this library */
#      define CC_CORE_LIB_API 
#    endif
#  endif

#  ifndef CC_CORE_LIB_NO_EXPORT
#    define CC_CORE_LIB_NO_EXPORT 
#  endif
#endif

#ifndef CC_CORE_LIB_DEPRECATED
#  define CC_CORE_LIB_DEPRECATED __declspec(deprecated)
#endif

#ifndef CC_CORE_LIB_DEPRECATED_EXPORT
#  define CC_CORE_LIB_DEPRECATED_EXPORT CC_CORE_LIB_API CC_CORE_LIB_DEPRECATED
#endif

#ifndef CC_CORE_LIB_DEPRECATED_NO_EXPORT
#  define CC_CORE_LIB_DEPRECATED_NO_EXPORT CC_CORE_LIB_NO_EXPORT CC_CORE_LIB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CC_CORE_LIB_NO_DEPRECATED
#    define CC_CORE_LIB_NO_DEPRECATED
#  endif
#endif

#endif /* CC_CORE_LIB_API_H */
