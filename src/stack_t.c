#include "stack_t.h"

struct stack_t *make_stack_t(void (*free_ele)(void *data)) {
    // allocate memory for the stack_t object.
    struct stack_t *stack = xmalloc(sizeof(struct stack_t));
    // allocate memory for the array of pointer to elements on the stack.
    // the number of elements that can exist without resizing = DEFAULT_STACK_SIZE
    stack->elements = xcalloc(DEFAULT_STACK_SIZE, sizeof(void *));
    // set the current size to DEFAULT_STACK_SIZE.
    stack->size = DEFAULT_STACK_SIZE;
    // set the index of the top element to -1 as the stack is empty.
    stack->top = -1;
    // set the freeing function to free_ele if not null, if null set it to free.
    stack->free_ele = free_ele ? free_ele : free;
    // return the allocated stack pointer.
    return stack;
}

void free_stack_t(struct stack_t *stack) {
    if (stack) {
        while (stack->top != -1) {
            if(stack->elements[stack->top])
            {
                stack->free_ele(stack->elements[stack->top]);
            }
            stack->top--;
        }
        free(stack->elements);
        free(stack);
    }
}

void stack_t_push(struct stack_t *stack, void *data) {
    // cannot work with null stack pointers.
    FAIL_IF_NULL(stack);
    // check if the stack has free slot for a new element.
    if (stack->top != stack->size - 1) {
        // yes, there is enough space for a new element.
        // assign the data to the slot.
        stack->elements[stack->top + 1] = data;
        // increment the top index to point to the last stored elements.
        stack->top++;
    } else {
        // no, there is not enough space for a new element so resizing it is.
        double_stack_size(stack);
        // assign the data to the first free slot after resizing.
        stack->elements[stack->top + 1] = data;
        // update the top indicator index.
        stack->top++;
    }
}

void *stack_t_pop(struct stack_t *stack, int32_t rmode) {
    FAIL_IF_NULL(stack);

    if (rmode == 0) {
        if (stack->top != -1) {
            if(stack->elements[stack->top])
            {
                stack->free_ele(stack->elements[stack->top]);
                stack->elements[stack->top] = NULL;
            }
            stack->top--;
            return NULL;
        } else {
            return NULL;
        }
    } else if (rmode == 1) {
        stack->top--;
        void* temp = stack->elements[stack->top + 1];
        stack->elements[stack->top + 1] = NULL;
        return temp;
    } else {
        FAIL("unrecognised removal mode.\n");
    }

    return NULL;
}

void double_stack_size(struct stack_t* stack)
{
    FAIL_IF_NULL(stack);
    stack->elements =
        xrealloc(stack->elements, stack->size * 2 * sizeof(void *));
    // update the size indicator index.
    stack->size *= 2;
}
