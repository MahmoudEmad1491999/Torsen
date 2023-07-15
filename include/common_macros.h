#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

#include <stdio.h>
#define FAIL_IF_NEGATIVE(arg) \
    if((arg) < 0) \
    { \
        fprintf( stderr ,#arg " CANNOT BE NEGATIVE!\n"); \
        exit(-1); \
    }

#define FAIL_IF_NULL(ptr) \
    if(!(ptr)) { \
        fprintf(stderr, #ptr " is Null.\n");\
        exit(EXIT_FAILURE); \
    }

#define FAIL(msg) \
{ \
    fprintf(stderr, msg); \
    exit(EXIT_FAILURE); \
}

#define FAIL_IF_GT(x, y, msg)\
    if ((x) > (y))\
    {\
        fprintf(stderr, msg); \
        exit(EXIT_FAILURE); \
    }
#define FAIL_IF_LT(x, y, msg)\
    if ((x) < (y))\
    {\
        fprintf(stderr, msg); \
        exit(EXIT_FAILURE); \
    }
#define FAIL_IF_GE(x, y, msg)\
    if ((x) >= (y))\
    {\
        fprintf(stderr, msg); \
        exit(EXIT_FAILURE); \
    }
#define FAIL_IF_LE(x, y, msg)\
    if ((x) <= (y))\
    {\
        fprintf(stderr, msg); \
        exit(EXIT_FAILURE); \
    }
//** index must belong to the set [ll, ul)
//ll inclusive, ul exclusive.
#define CHECK_INDEX(index, ll, ul) \
    if(((index) < (ll)) || ((index) > (ul)) ) \
{\
    fprintf(stderr, "Index Out of Range.\n");\
    exit(EXIT_FAILURE);\
}


#endif
