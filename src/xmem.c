#include "xmem.h"

void* xmalloc(size_t len)
{
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
    void* ptr = realloc(oldptr, new_size);
    if(!ptr)
    {
        perror("realloc\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}
