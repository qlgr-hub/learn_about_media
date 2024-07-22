#pragma once


#if defined _WIN32 || defined __CYGWIN__
    #ifdef EXPORT_LAM_API
        #ifdef __GNUC__
            #define LAM_API __attribute__ ((dllexport))
        #else
             #define LAM_API __declspec(dllexport)
        #endif
    #else
        #ifdef __GNUC__
            #define LAM_API __attribute__ ((dllimport))
        #else
            #define LAM_API __declspec(dllimport)
        #endif
    #endif
#else
    #define LAM_API __attribute__ ((visibility ("default")))
#endif


