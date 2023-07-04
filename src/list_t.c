#include "list_t.h"
#include "common_macros.h"
#include "xmem.h"

/**
 * Purpose: this structure is used to represent a dynamic array.
 *
 * @list            is the actuall array of pointers to elements.
 * @len             the current lenth and max capacity of the vector.
 * @free_ele        the freeing function used to free indivdual elements.
 * @last_index      the index representing the last element on the list, -1 if empty,
 *                  used by push_back and push back copy
 *
 **/
struct list_t
{
    void** list;
    int32_t len;
    void (*free_ele)(void*);
    int32_t last_index;
};


struct list_t* make_list_t(int32_t len, void (*free_ele)(void* ele))
{
    FAIL_IF_NEGATIVE(len);

    struct list_t* list = xmalloc( sizeof(struct list_t) );
    list->len = len;
    list->last_index = -1;
    list->free_ele = free_ele ? free_ele: free;
    list->list = xcalloc(len, sizeof(void*));
    return list;
}


void free_list_t(struct list_t *list)
{
    if(list)
    {
        for(int index = 0; index < list-> len; index++)
        {
            list->free_ele(list->list[index]);
        }
        free(list->list);
        free(list);
    }
}
void list_t_push_back(struct list_t *list, void *obj)
{
    FAIL_IF_NULL(list);
    // check if the list is empty or not.
    if(list->last_index >= 0){
        // test if there is need to resize.
        if(list->last_index < (list->len - 1))
        {
            // set the obj at the last_index + 1 position and increment last_index.
            list->list[list->last_index++] = obj;
        }
        else
        {
            // list is full so double the size.
            list_t_double_size(list);
            // recall 
            list_t_push_back(list, obj);
        }
    }
    // the list is empty.
    else {
        list->list[0] = obj;
        list->last_index = 0;
    }
}

void list_t_push_back_by_copy(struct list_t *list, void *obj, size_t obj_size)
{
    FAIL_IF_NULL(list);
    // check if the list is empty or not.
    if(list->last_index >= 0){
        // test if there is need to resize.
        if(list->last_index < (list->len - 1))
        {
            // check if obj is null
            if(obj)
            {
                // get a copy of obj.
                void* clone = copy(obj, obj_size);
                // set the clone at the last_index + 1 position and increment last_index.
                list->list[list->last_index++] = clone;
            }
            else {
                list->list[list->last_index++] = NULL;
            }
        }
        else
        {
            // list is full so double the size.
            list_t_double_size(list);
            // recall 
            list_t_push_back(list, obj);
        }
    }
    // the list is empty.
    else {
            // check if obj is null
            if(obj)
            {
                // get a copy of obj.
                void* clone = copy(obj, obj_size);
                // set the clone at the last_index + 1 position and increment last_index.
                list->list[list->last_index++] = clone;
            }
            else {
                list->list[list->last_index++] = NULL;
            }
    }
}


void list_t_insert_at(struct list_t *list, int32_t index, void *obj)
{
    FAIL_IF_NULL(list);
    CHECK_INDEX(index, 0, list->len);
    // check if the list is full, if so double it's size.
    if(list->last_index >= (list->len - 1))
    {
        list_t_double_size(list);
    }
    // shift all the element from last_index to the specified index to the right.
    for(int32_t rev_index = list->last_index + 1; rev_index > index; rev_index--)
    {
        list->list[rev_index] = list->list[rev_index-1];
    }
    // increment last_index;
    list->last_index++;
    // set the element at the specified index to obj.
    list->list[index] = obj;
}

void list_t_insert_at_by_copy(struct list_t *list, int32_t index, void *obj, size_t obj_size)
{
    FAIL_IF_NULL(list);
    CHECK_INDEX(index, 0, list->len);
    // check if the list is full, if so double it's size.
    if(list->last_index >= (list->len - 1))
    {
        list_t_double_size(list);
    }
    // shift all the element from last_index to the specified index to the right.
    for(int32_t rev_index = list->last_index + 1; rev_index > index; rev_index--)
    {
        list->list[rev_index] = list->list[rev_index-1];
    }
    // increment last_index;
    list->last_index++;
    // set the element at the specified index to obj.
    if(obj) {
        list->list[index] = copy(obj, obj_size);
    }
    else {
        list->list[index] = NULL;
    }
}

void list_t_double_size(struct list_t *list)
{
    FAIL_IF_NULL(list);
    list->list = xrealloc(list->list, sizeof(void*) * list->len * 2);
    // update the length of the list.
    list->len *= 2;
}

void* list_t_remove(struct list_t *list, int32_t index, int32_t rmode)
{
    FAIL_IF_NULL(list);
    CHECK_INDEX(index, 0, list->len);
    if(rmode == 0)
    {
        if(list->list[index] != NULL)
        {
            list->free_ele(list->list[index]);
            list->list[index] = NULL;
        }
        return NULL;
    }else
    {
        void* temp = list->list[index];
        list->list[index] = NULL;
        return temp;
    }
}


void* list_t_at_get(struct list_t* list, int32_t index)
{
    FAIL_IF_NULL(list);
    CHECK_INDEX(index, 0, list->len);


    return list->list[index];
}


void list_t_at_set(struct list_t* list, int32_t index, void* obj)
{
    FAIL_IF_NULL(list);
    CHECK_INDEX(index, 0, list->len);

    if(list->list[index]) list->free_ele(list->list[index]);

    list->list[index] = obj;

    if(index > list->last_index) list->last_index = index;
}


void list_t_at_set_by_copy(struct list_t *list, int32_t index, void *obj, size_t obj_size)
{
    FAIL_IF_NULL(list);
    CHECK_INDEX(index, 0, list->len);

    if(list->list[index]) list->free_ele(list->list[index]);

    if(obj) list->list[index] = copy(obj, obj_size);
    else list->list[index] = NULL;

    if(index > list->last_index) list->last_index = index;
}

