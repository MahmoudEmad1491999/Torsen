#ifndef SL_LIST_T_H
#define SL_LIST_T_H
#include "common_macros.h"
#include "xmem.h"

/**
 * Purpose: this structure represent a node in the single list.
 * @next    is a pointer to the next node in line.
 * @data    actually is pointer to the data element.
 **/
struct sl_list_node {
    struct sl_list_node *next;
    void *data;
};

/**
 * Purpose: this structure is used to represent the singly linked list object.
 * @head    is a pointer to the head node of the list, NULL when list is empty.
 * @tail    is a pointer to the tail/last node of the list, NULL when is empty.
 * free_ele     is a freeing function used to free elements/nodes->data when
 *removed, or the list is freed.
 * @compare_ele     is a pointer to function that can be used to compare
 *elements/nodes data for equality, greaterness, and lessness.
 **/
struct sl_list_t {
    struct sl_list_node *head;
    struct sl_list_node *tail;
    void (*free_ele)(void *);
    int32_t (*compare_ele)(void *, void *);
};

/**
 * Purpose: this function is used to make a new sl_list_t object dynamically and
 *return pointer to it.
 * @free_ele    is a pointer to function to be used to free elements.
 * @compare_ele     is a pointer to function to be used to compare data elements
 *of nodes.
 **/
struct sl_list_t *make_sl_list_t(void (*free_ele)(void *),
                                 int32_t (*compare_ele)(void *data1,
                                                        void *data2));
/**
 * Purpose: this function is used to free the sl_list_t object and free
 *indivdual nodes.
 * @sl_list     pointer to the list to be freed.
 **/
void free_sl_list_t(struct sl_list_t *sl_list);
/**
 * Purpose: this function is used to append an element to the end of the
 *sl_list_t object.
 * @sl_list     pointer to the list, to which we append.
 * @data        pointer to the data elements to be appended to the list.
 **/
void sl_list_t_append(struct sl_list_t *sl_list, void *data);
/**
 * Purpose: this function is used to append an element to the end of the
 * sl_list_t object. by copying the given data.
 * @sl_list     pointer to the sl_list_t object to append to.
 * @data        is a pointer to the data object.
 * @data_size   the size of the data object pointed by @data.
 */
void sl_list_t_append_by_copy(struct sl_list_t *sl_list, void *data,
                              size_t data_size);
/**
 * Purpose: this function is used to preprend an element to the sl_list object.
 * @sl_list     the sl_list object to which we append.
 * @data        pointer to the data element that we want to prepend.
 * NOTE:        The data object given is going to be completly owned by the list
 *object, and the freeing responsiblity is on the list.
 **/
void sl_list_t_prepend(struct sl_list_t *sl_list, void *data);

/**
 * Purpose: this function is used to preprend an element to the sl_list object,
 *          by copying it.
 * @sl_list     the sl_list object to which we append.
 * @data        pointer to the data element that we want to prepend.
 * NOTE:        The data object given is going to be copied, so the freeing
 * responsiblity is still on the client.
 */
void sl_list_t_prepend_by_copy(struct sl_list_t *sl_list, void *data,
                               size_t data_size);
/**
 * Purpose: this function is used to delete an element from the list,
 *          by comparing the given data elements through the whole list,
 *          and this delete the first element find.
 * @sl_list     the list to work on.
 * @data        the data we want to delete.
 * @rmode       this determine whehter to free the data in the found node,
 *              or to return it.
 **/
void *sl_list_t_delete(struct sl_list_t *sl_list, void *data, int rmode);
#endif
