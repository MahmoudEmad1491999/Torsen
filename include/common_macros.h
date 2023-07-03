#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

#include <stdio.h>
#define FAIL_IF_NEGATIVE(arg) \
    if((arg) <= 0) \
    { \
        fprintf( stderr ,#arg " CANNOT BE NEGATIVE!\n"); \
        exit(-1); \
    }

#define FAIL_IF_NULL(ptr) \
    if(!ptr) { \
        fprintf(stderr, #ptr " is Null.\n");\
        exit(EXIT_FAILURE); \
    }

#define FAIL(msg) \
{ \
    fprintf(stderr, msg); \
    exit(EXIT_FAILURE); \
}

#endif
