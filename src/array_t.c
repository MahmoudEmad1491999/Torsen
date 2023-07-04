#include "array_t.h"
#include "common_macros.h"
#include "xmem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Purpose: this strucutre represent fixed length array structure.
 * @arr     fixed length array of pointer to objects.
 * @len     the length of the array.
 * @free_ele the function used to free the elements of the array when the array
 *is freed, or an element is removed.
 **/
struct array_t {
    void **arr;
    int32_t len;
    void (*free_ele)(void *ele);
};

struct array_t *make_array_t(int32_t len, void (*free_ele)(void *ele)) {
    // cannot create an array with a negative length.
    FAIL_IF_NEGATIVE(len);

    struct array_t *array = xmalloc(sizeof(struct array_t));
    array->len = len;
    array->arr = xcalloc((size_t)len, sizeof(void *));
    array->free_ele = free_ele ? free_ele : free;
    return array;
}

void free_array_t(struct array_t *array) {
    if (array) {
        for (int32_t index = 0; index < array->len; index++) {
            array->free_ele(array->arr[index]);
        }
        free(array->arr);
        free(array);
    }
}

void *array_t_at_get(struct array_t *array, int32_t index) {
    FAIL_IF_NULL(array);
    FAIL_IF_NEGATIVE(index);
    if (index < array->len) {
        return array->arr[index];
    } else {
        FAIL("Index Out Of Range.\n");
    }
}

void array_t_at_set(struct array_t *array, int32_t index, void *obj) {
    FAIL_IF_NULL(array);
    FAIL_IF_NEGATIVE(index);
    if (index < array->len) {
        array->free_ele(array->arr[index]);
        array->arr[index] = obj;
    } else {
        FAIL("Index Out Of Range.\n");
    }
}

void array_t_at_set_by_copy(struct array_t *array, int32_t index, void *obj,
                            size_t len) {
    FAIL_IF_NULL(array);
    FAIL_IF_NEGATIVE(index);
    if (index < array->len) {
        array->free_ele(array->arr[index]);
        if (obj) {
            array->arr[index] = xmalloc(len);
            memcpy(array->arr[index], obj, len);
        } else {
            array->arr[index] = calloc(1, len);
        }
    } else {
        FAIL("Index Out Of Range.\n");
    }
}

void *array_t_at_remove(struct array_t *array, int32_t index,
                        int32_t rmode) {
    FAIL_IF_NULL(array);
    FAIL_IF_NEGATIVE(index);

    if (index < array->len) {
        if (rmode == 0) {
            array->arr[index] = NULL;
            array->free_ele(array->arr[index]);
            return NULL;
        } else if( rmode == 1) {
            array->arr[index] = NULL;
            return array->arr[index];
        }
        else {
            FAIL("Un implemented type of removal.\n");
        }
    } else {
        FAIL("Index Out Of Range.\n");
    }
}
