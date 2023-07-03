#ifndef XMEM_H
#define XMEM_H
#include "common_macros.h"
#include <stdio.h>
#include <stdlib.h>

void* xmalloc(size_t len);

void* xcalloc(size_t num, size_t size);

void* xrealloc(void* oldptr, size_t new_size);

#endif
