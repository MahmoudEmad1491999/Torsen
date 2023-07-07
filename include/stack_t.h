#ifndef STACK_T_H
#define STACK_T_H

#include "common_macros.h"
#include "xmem.h"
#include <stdint.h>
const int32_t DEFAULT_STACK_SIZE = 8;
struct stack_t {
    void **elements;
    int32_t top;
    int32_t size;
    void (*free_ele)(void *ele);
};

struct stack_t *make_stack_t(void (*free_ele)(void *data));

void stack_t_push(struct stack_t *stack, void *data);
void *stack_t_pop(struct stack_t *stack, int32_t rmode);
void free_stack_t(struct stack_t *stack);

#endif
