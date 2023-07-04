#ifndef LIST_T_H
#define LIST_T_H

#include <stddef.h>
#include <stdint.h>
struct list_t;


/*
 * Purpose: this function is used to create a new list object, a.k.a. dynamic array.
 * @len     the initial length of the list.
 * @free_ele the freeing functions used to free indivdual elements of the list.
 * */
struct list_t* make_list_t(int32_t len, void (*free_ele)(void* ele));

/**
 * Purpose: this function is used to free the list structure and the elements.
 * @list    the list to be freed.
 */
void free_list_t(struct list_t* list);

/**
 * PUrpose: this function is used to add an element at the end of the list.
 *
 * @list    the list to work on.
 * @obj     the element to add to the end of the list, note: after the call 
 *          this element is solely owned by the list after this call.
 */
void list_t_push_back(struct list_t* list, void* obj);
/**
 * Purpose: this function is used to add an element at the end of the list by 
 *          copying the object.
 * @list    the list to work on.
 * @obj     the object to copy at the end of the list.
 * @obj_size     the length of @obj in bytes.
 */
void list_t_push_back_by_copy(struct list_t* list, void* obj,size_t obj_size);

/**
 * Purpose: this function is used to insert and element at a specified index by shifting
 *          right the remaining elements.
 * @list    the list work on.
 * @index   the index at which the @obj will be after insertion.
 * @obj     pointer to the element to be inserted, Note: after the insertion the object is
 *          completely owned by the list.
 */

void list_t_insert_at(struct list_t* list, int32_t index, void* obj);
/**
 * Purpose: this function is used to insert and element at a specified index by shifting
 *          right the remaining elements.
 * @list    the list work on.
 * @index   the index at which the @obj will be after insertion.
 * @obj     pointer to the element to be inserted, Note: this object is copied using memcpy.
 * @obj_size     the size of @obj in bytes.
 * */
void list_t_insert_at_by_copy(struct list_t* list, int32_t index, void* obj, size_t obj_size);

/**
 * Purpose: this function is used to remove an element from a list at a specified index.
 * @list    the list to work on.
 * @index   the index at which we want to remove the element.
 * @rmode   removal mode: whether to free the element using list->free_ele or return it.
 *          0 means free 1 means return.
 * */
void* list_t_remove(struct list_t* list, int32_t index, int32_t rmode);
/**
 * Purpose: this function is used to get pointer to the object at index.
 * @list    the list to work on.
 * index    the index at which the object resides.
 */
void* list_t_at_get(struct list_t* list, int32_t index);
/**
 * Purpose: this function is used to set the index to the given object and free the old one
 *          if necessary.
 * @list    the list to work on.
 * @index   the index wanted to set the object at.
 * @obj     the object we want to set, note: this object now is completely owned by list.
 * */
void  list_t_at_set(struct list_t* list, int32_t index, void* obj);
/**
 * Purpose: this function is used to set the index to the given object and free the old one.
 * @list    the list to work on.
 * @index   the index wanted to set the object at.
 * @obj     the object we want to set.
 * @obj_size    is the size of the object to be set.
 */
void list_t_at_set_by_copy(struct list_t* list, int32_t index, void* obj, size_t obj_size);

/**
 * Purpose: this function is used to double the size/capacity of a given list.
 *  @list   the list to work on.
 */
void list_t_double_size(struct list_t* list);
#endif
