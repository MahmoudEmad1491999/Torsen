#include "sl_list_t.h"


struct sl_list_t *make_sl_list_t(void (*free_ele)(void *),
                                 int32_t (*compare_ele)(void *data1,
                                                        void *data2)) {
    FAIL_IF_NULL(compare_ele);
    struct sl_list_t *sl_list = xmalloc(sizeof(struct sl_list_t));
    sl_list->head = NULL;
    sl_list->tail = NULL;
    sl_list->free_ele = free_ele ? free_ele : free;
    sl_list->compare_ele = compare_ele;
    return sl_list;
}

void free_sl_list_t(struct sl_list_t *sl_list) {
    // first check if the given sl_list is not null.
    if (sl_list) {
        // this variable is going to hold the head of the sl_list so to be
        // freed.
        void *temp_head;

        while (sl_list->head) {
            // set temp_head to the current head.
            temp_head = sl_list->head;
            // free the data payload of the current head.
            sl_list->free_ele(sl_list->head->data);
            // advance the head to the next node inline.
            sl_list->head = sl_list->head->next;
            // free the old head after advancing.
            free(temp_head);
        }
        // now free the head structure.
        free(sl_list);
    }
}

void sl_list_t_append(struct sl_list_t *sl_list, void *data) {
    FAIL_IF_NULL(sl_list);
    struct sl_list_node *node = xmalloc(sizeof(struct sl_list_node));
    node->data = data;
    node->next = NULL;
    sl_list->tail->next = node;
    sl_list->tail = node;
}

void sl_list_t_append_by_copy(struct sl_list_t *sl_list, void *data,
                              size_t data_size) {
    FAIL_IF_NULL(sl_list);
    struct sl_list_node *node = xmalloc(sizeof(struct sl_list_node));

    if(data)
    {
        node->data = copy(data, data_size);
    }else {
        node->data = NULL;
    }
    node->next = NULL;
    
    sl_list->tail->next = node;
    sl_list->tail = node;
}

void sl_list_t_prepend(struct sl_list_t *sl_list, void *data) {
    FAIL_IF_NULL(sl_list);
    struct sl_list_node *node = xmalloc(sizeof(struct sl_list_node));
    node->data = data;
    node->next = sl_list->head;
    sl_list->head = node;
}

void sl_list_t_prepend_by_copy(struct sl_list_t *sl_list, void *data,
                               size_t data_size) {
    FAIL_IF_NULL(sl_list);
    struct sl_list_node *node = xmalloc(sizeof(struct sl_list_node));
    if(data)
    {
        node->data = copy(data, data_size);
    }
    else {
        node->data = NULL;
    }
    node->next = sl_list->head;
    sl_list->head = node;
}

void *sl_list_t_delete(struct sl_list_t *sl_list, void *data, int rmode) {
    // we cananot delete from a null singly linked list.
    FAIL_IF_NULL(sl_list);
    // this is just a temp to place the comparison result.
    int32_t compare_result;
    // this is going to be used to return the deleted data when the rmode = 1;
    void* res;
    // this is pointer to the nodes of the list used to traverse it.
    struct sl_list_node *iterator = sl_list->head;
    // as we need to find the node with the data and the node previous to it so that 
    // it can point to the next one correctly
    // we test the first one that continue on the next one useding the same pointer.
    if(iterator!=NULL)
    {
        // compare head
        // 0 means equal
        // 1 means greater if applicable.
        // -1 means less if applicable.
        if (!(sl_list->compare_ele(sl_list->head->data, data))) {
            if (rmode == 0) { // free the data.
                sl_list->free_ele(sl_list->head->data);
                sl_list->head = sl_list->head->next;
                free(sl_list->head);
                return NULL;
            } else if (rmode == 1) { // return the data.
                void *res = sl_list->head->data;
                sl_list->head = sl_list->head->next;
                free(sl_list->head);
                return data;
            } else {
                FAIL("unrecognised removal mode.\n");
            }
        }
        // keep looping untill we reach the end of list.
        // now iterator is a pointer to every single node in the list.
        while (iterator && iterator != sl_list->tail) {
            // compare the data payload of iterator next node with the given data
            if (!(sl_list->compare_ele(iterator->next->data, data))) {
                if (rmode == 0) { // free the data payload if found.
                    struct sl_list_node *to_be_deleted = iterator->next;
                    iterator->next = iterator->next->next;
                    sl_list->free_ele(to_be_deleted->data);
                    free(to_be_deleted);
                    return NULL;
                } else if (rmode == 1) { // return the data payload if found.
                    struct sl_list_node *to_be_deleted = iterator->next;
                    // by pass the to_be_deleted node.
                    iterator->next = iterator->next->next;
                    // set res to be returned.
                    res = to_be_deleted->data;
                    // free the node.
                    free(to_be_deleted);
                    return res;
                } else {
                    FAIL("unrecognised removal mode.\n");
                }
            }
        }
        // if the list does not contain a node with data equal to the data payload, just
        // return null;
        return NULL;
    }
    // if the list is empty just return NULL;
    return NULL;
}

