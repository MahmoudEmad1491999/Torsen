#ifndef SL_LIST_T_H
#define SL_LIST_T_H
#include "common_macros.h"
#include "xmem.h"

/*
 * abbreviations: ul : underlaying list.
 * u generally means underlaying.
 * */

struct sl_list_node {
    struct sl_list_node *next;
    void *data;
};

struct sl_list_t {
    struct sl_list_node *head;
    struct sl_list_node *tail;
    void (*free_ele)(void *);
    int32_t (*compare_ele)(void *, void *);
};

struct sl_list_t *make_sl_list_t(void (*free_ele)(void *),
                                 int32_t (*compare_ele)(void *data1,
                                                        void *data2));
void free_sl_list_t(struct sl_list_t *sl_list);
void sl_list_t_append(struct sl_list_t *sl_list, void *data);
void sl_list_t_append_by_copy(struct sl_list_t *sl_list, void *data,
                              size_t data_size);
void sl_list_t_prepend(struct sl_list_t *sl_list, void *data);
void sl_list_t_prepend_by_copy(struct sl_list_t *sl_list, void *data,
                               size_t data_size);
void *sl_list_t_delete(struct sl_list_t *sl_list, void *data, int rmode);
#endif
