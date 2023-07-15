#include "list_t.h"
#include "common_macros.h"
#include "xmem.h"

struct list_t *make_list_t(int32_t len, void (*free_ele)(void *ele)) {
    FAIL_IF_NEGATIVE(len);

    struct list_t *list = xmalloc(sizeof(struct list_t));
    list->len = len;
    list->last_index = -1;
    list->free_ele = free_ele ? free_ele : free;
    list->elements = xcalloc(len, sizeof(void *));
    return list;
}

void free_list_t(struct list_t *list) {
    if (list) {
        for (int index = 0; index < list->len; index++) {
            if (list->elements[index])
                list->free_ele(list->elements[index]);
        }
        free(list->elements);
        free(list);
    }
}
void list_t_push_back(struct list_t *list, void *obj) {
    FAIL_IF_NULL(list);
    // check if the list is empty or not.
    // becuase if last_index == -1
    if (list->last_index != -1) {
        // test if there is need to resize.
        // there is going to be a need to resize if @last_index == @len -1
        if (list->last_index != list->len - 1) {
            // set the obj at the last_index + 1 position and increment
            // last_index.
            list->elements[list->last_index + 1] = obj;
            list->last_index++;
        } else {
            // list is full so double the size.
            list_t_double_size(list);
            // recall
            list_t_push_back(list, obj);
        }
    }
    // the list is empty.
    else {
        list->elements[0] = obj;
        list->last_index = 0;
    }
}

void list_t_push_back_by_copy(struct list_t *list, void *obj, size_t obj_size) {
    FAIL_IF_NULL(list);
    // check if the list is empty or not.
    // becuase if last_index == -1
    if (list->last_index != -1) {
        // test if there is need to resize.
        // there is going to be a need to resize if @last_index == @len -1
        if (list->last_index != list->len - 1) {
            // check if obj is null
            if (obj) {
                // get a copy of obj.
                void *clone = copy(obj, obj_size);
                // set the clone at the last_index + 1 position and increment
                // last_index.
                list->elements[list->last_index + 1] = clone;
                list->last_index++;
            } else {
                list->elements[list->last_index + 1] = NULL;
                list->last_index++;
            }
        } else {
            // list is full so double the size.
            list_t_double_size(list);
            // recall
            list_t_push_back(list, obj);
        }
    }
    // the list is empty.
    else {
        // check if obj is null
        if (obj) {
            // get a copy of obj.
            void *clone = copy(obj, obj_size);
            // set the clone at the last_index + 1 position and increment
            // last_index.
            list->elements[list->last_index++] = clone;
        } else {
            list->elements[list->last_index++] = NULL;
        }
    }
}

void list_t_insert_at(struct list_t *list, int32_t index, void *obj) {
    FAIL_IF_NULL(list);
    CHECK_INDEX(index, 0, list->len);

    // check if the list is full, if so double it's size.
    if (list->last_index == (list->len - 1)) {
        list_t_double_size(list);
    }

    // here we test if the insertion is done in the region where exist actual
    // elements [0, last_index]
    // if so there is going to be shifting of elements and last index is
    // incremented.
    if (index < list->last_index) {
        // shift all the element from last_index to the specified index to the
        // right.
        for (int32_t last_index = list->last_index + 1; last_index > index;
             last_index--) {
            list->elements[last_index] = list->elements[last_index - 1];
        }

        // set the element at the specified index to obj.
        list->elements[index] = obj;

        // increment last_index, as the insertion is going to increment it.
        list->last_index++;
    } else { // if not this means the index is far from the last_index,
        // so after the insertion last_index = index, and no need for shifting.
        // set the element at the specified index to obj.
        list->elements[index] = obj;

        // increment last_index, as the insertion is going to increment it.
        list->last_index = index;
    }
}

void list_t_insert_at_by_copy(struct list_t *list, int32_t index, void *obj,
                              size_t obj_size) {
    FAIL_IF_NULL(list);
    CHECK_INDEX(index, 0, list->len);

    // check if the list is full, if so double it's size.
    if (list->last_index == (list->len - 1)) {
        list_t_double_size(list);
    }

    // here we test if the insertion is done in the region where exist actual
    // elements [0, last_index]
    // if so there is going to be shifting of elements and last index is
    // incremented.
    if (index < list->last_index) {
        // shift all the element from last_index to the specified index to the
        // right.
        for (int32_t last_index = list->last_index + 1; last_index > index;
             last_index--) {
            list->elements[last_index] = list->elements[last_index - 1];
        }

        // set the element at the specified index to obj.
        if (obj) {
            list->elements[index] = copy(obj, obj_size);
        } else {
            list->elements[index] = NULL;
        }

        // increment last_index, as the insertion is going to increment it.
        list->last_index++;
    } else { // if not this means the index is far from the last_index,
        // so after the insertion last_index = index, and no need for shifting.
        // set the element at the specified index to obj.
        if (obj) {
            list->elements[index] = copy(obj, obj_size);
        } else {
            list->elements[index] = NULL;
        }

        // increment last_index, as the insertion is going to increment it.
        list->last_index = index;
    }
}

void list_t_double_size(struct list_t *list) {
    FAIL_IF_NULL(list);
    list->elements = xrealloc(list->elements, sizeof(void *) * list->len * 2);
    // update the length of the list.
    list->len *= 2;
}

void *list_t_remove(struct list_t *list, int32_t index, int32_t rmode) {
    FAIL_IF_NULL(list);
    CHECK_INDEX(index, 0, list->last_index);
    // if rmode == 0, free the element.
    if (rmode == 0) {
        if (list->elements[index] != NULL) {
            list->free_ele(list->elements[index]);
            list->elements[index] = NULL;
            return NULL;
        }
        return NULL;
    } else if (rmode == 1){
        // record the "to be removed element address".
        void *temp = list->elements[index];
        // set the pointer at that index to NULL.
        list->elements[index] = NULL;
        // return the recorded element pointer.
        return temp;
    }
    else 
    {
        FAIL("Unsupported removal mode.\n");
    }
}

void *list_t_at_get(struct list_t *list, int32_t index) {
    FAIL_IF_NULL(list);
    CHECK_INDEX(index, 0, list->len);

    return list->elements[index];
}

void list_t_at_set(struct list_t *list, int32_t index, void *obj) {
    FAIL_IF_NULL(list);
    CHECK_INDEX(index, 0, list->len);
    // first check if that index is empty if not free the "inplace elements"
    if (list->elements[index])
        list->free_ele(list->elements[index]);
    // now set the new object at that index.
    list->elements[index] = obj;
    //  if index is after list->last_index, set last_index to it.
    if (index > list->last_index)
        list->last_index = index;
}

void list_t_at_set_by_copy(struct list_t *list, int32_t index, void *obj,
                           size_t obj_size) {
    FAIL_IF_NULL(list);
    CHECK_INDEX(index, 0, list->len);
    // first check if that index is empty if not free the "inplace elements"
    if (list->elements[index])
        list->free_ele(list->elements[index]);
    // now set the new object at that index. by copying it.
    list->elements[index] = copy(obj, obj_size);
    //  if index is after list->last_index, set last_index to it.
    if (index > list->last_index)
        list->last_index = index;
}

