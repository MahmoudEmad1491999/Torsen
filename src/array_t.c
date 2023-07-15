#include "array_t.h"
#include "common_macros.h"
#include "xmem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct array_t *make_array_t(int32_t len, void (*free_ele)(void *ele)) {
    // cannot create an array with a negative length.
    FAIL_IF_NEGATIVE(len);

    struct array_t *array = xmalloc(sizeof(struct array_t));
    array->len = len;
    array->elements = xcalloc((size_t)len, sizeof(void *));
    array->free_ele = free_ele ? free_ele : free;
    return array;
}

void free_array_t(struct array_t *array) {
    if (array) {
        for (int32_t index = 0; index < array->len; index++) {
            if(array->elements[index])
            {
                array->free_ele(array->elements[index]);
            }
        }
        free(array->elements);
        free(array);
    }
}

void *array_t_at_get(struct array_t *array, int32_t index) {
    FAIL_IF_NULL(array);
    CHECK_INDEX(index, 0, array->len);
    return array->elements[index];
}

void array_t_at_set(struct array_t *array, int32_t index, void *obj) {
    FAIL_IF_NULL(array);
    CHECK_INDEX(index, 0, array->len);
    if (array->elements[index])
        array->free_ele(array->elements[index]);
    array->elements[index] = obj;
}

void array_t_at_set_by_copy(struct array_t *array, int32_t index, void *obj,
                            size_t obj_size) {
    FAIL_IF_NULL(array);
    CHECK_INDEX(index, 0, array->len);

    if (array->elements[index])
        array->free_ele(array->elements[index]);
    if (obj) {
        array->elements[index] = xmalloc(obj_size);
        memcpy(array->elements[index], obj, obj_size);
    } else {
        array->elements[index] = xcalloc(1, obj_size);
    }
}

void *array_t_at_remove(struct array_t *array, int32_t index,
                        int32_t rmode) {
    FAIL_IF_NULL(array);
    FAIL_IF_NEGATIVE(index);
    CHECK_INDEX(index, 0, array->len);
    if (rmode == 0) {
        // check if the element is acutally not NULL.
        if (array->elements[index])
            array->free_ele(array->elements[index]);
        // after freeing the element set the pointer at index to NULL and return
        // NULL.
        array->elements[index] = NULL;
        return NULL;
    } else if (rmode == 1) {
        // if removal mode is to return not remove record it first and set
        // the pointer at index to NULL then return the recorded value.
        void *temp = array->elements[index];
        array->elements[index] = NULL;
        return temp;
    } else {
        FAIL("Un implemented type of removal.\n");
    }
}
