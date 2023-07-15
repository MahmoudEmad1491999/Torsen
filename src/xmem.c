#include "xmem.h"
#include <string.h>

void* xmalloc(size_t len)
{
    if(!len)
    {
        FAIL("Cannot Allocate Memeory region of zero size.\n");
    }

    void* ptr = malloc(len);
    
    if(!ptr)
    {
        perror("malloc\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* xcalloc(size_t num, size_t size)
{
    if(!size)
    {
        FAIL("Cannot Allocate Memeory region of zero size.\n");
    }
    void* ptr = calloc(num, size);
    if(!ptr)
    {
        perror("calloc\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}


void* xrealloc(void* oldptr, size_t new_size)
{
    if(!new_size)
    {
        FAIL("Cannot Allocate Memeory region of zero size.\n");
    }
    void* ptr = realloc(oldptr, new_size);
    if(!ptr)
    {
        perror("realloc\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* copy(void* obj, size_t obj_size)
{
    if(obj){
        void* result = xmalloc(obj_size);
        memcpy(result, obj, obj_size);
        return result;
    }
    return NULL;
}
