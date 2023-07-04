#ifndef T_ARRAY_H
#define T_ARRAY_H
#include <stdint.h>
#include <stdlib.h>


struct array_t;


/**
 * Purpose: this function is used to create An Array Object.
 * @len     the length of the array.
 *
 * Note:    arrays are static data structures, they have fixed length.
 **/
struct array_t* make_array_t(int32_t len, void (*free_ele)(void* ele));



/**
 * Purpose: this function is used to free the array structure and every object in it.
 * @array   pointer to the array to be freed.
 **/
void free_array_t(struct array_t* array);

/**
 * Purpose: this function is used to work as the subscript operator on c-arrays.
 * @index   the requested index.
 * 
 * Note:    if index >= @len the program abort with error message index out of range.
 **/
void* array_t_at_get(struct array_t* arr, int32_t index);

/**
 * Purpose: this function is used to set the array element at index @index directly without copying.
 * @index   is the index in question.
 * @obj     pointer to the object to be set.
 *
 * Note:    if index >= @len the program abort with error message index out of range.
 * Note:    @obj must be unique as the responsiblity of freeing it has moved to the array ds.
 **/
void array_t_at_set(struct array_t* arr, int32_t index, void* obj);

/**
 * Purpose: this function is used to set the array element at index @index by coping the given
 *          object.
 * @index   the index in question.
 * @obj     the object to be set at index.
 * @len     the object length in bytes.
 *
 * Note:    this method is used to work with object by copying their values.
 **/
void array_t_at_set_by_copy(struct array_t* arr, int32_t index, void* obj, size_t len);
/**
 * Purpose: this function is used to remove an element from the array or return it.
 * @index   the index in question.
 * @rmode   removal mode: whether to remove the element or to return it.
 *          0 means free it 1 means return.
 **/
void* array_t_at_remove(struct array_t* arr, int32_t index, int32_t rmode);
#endif
