#include <stdio.h>
#include <stdint.h>

void test(void* x, void* y)
{
    printf("%d, %d\n", *((int32_t*)(x)), *((int32_t*)(y)));
}


int main(int argc, char* argv[])
{
    int32_t x = 200, y = 300; 
    void (*test_shadow)(int32_t*, int32_t*);
    test_shadow = (void (*)(int32_t*, int32_t*))test;
    test_shadow(&x, &y);
    return 0;
}

