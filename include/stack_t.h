#ifndef STACK_T_H
#define STACK_T_H

#include "common_macros.h"
#include "xmem.h"
#include <stdint.h>

const int32_t DEFAULT_STACK_SIZE = 8;

/**
 * Purpose: this represent a stack object.
 * @elements    an array of pointers to the elements of the stack.
 * @top         is the index of the top element of the stack.
 * @size        is the current size of the stack, the maximum number
 *              of elements on the stack.
 * @free_ele    this is function is used to free elements when pop and
 *discarded.
 **/
struct stack_t {
    void **elements;
    int32_t top;
    int32_t size;
    void (*free_ele)(void *ele);
};

/**
 * Purpose: this function is used to make Stack Object.
 * @free_ele    this is function is used to free elements when pop and
 *discarded.
 **/
struct stack_t *make_stack_t(void (*free_ele)(void *data));

/**
 * Purpose: this function is used to free stack object and all the elements on
 * the stack.
 * @stack   is pointer to the stack object to be free.
 * */
void free_stack_t(struct stack_t *stack);

/**
 * Purpose: this function is used to push a new element on the stack.
 * @stack   pointer to the stack to push to.
 * @data    this is the data element.
 **/
void stack_t_push(struct stack_t *stack, void *data);

/**
 * Purpose: this function is used to pop the top of the stack and NULL if empty.
 * @stack   the stack pointer to which we want to pop front.
 * @rmode   0 means free the top element.
 *          1 means return the top element data object and don't free it.
 */
void *stack_t_pop(struct stack_t *stack, int32_t rmode);

/**
 * Purpose: this function is used to double the size of the given stack.
 * @stack the stack we want to double the size of.
 * */
void double_stack_size(struct stack_t* stack);
#endif
