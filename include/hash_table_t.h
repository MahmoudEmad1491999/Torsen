#ifndef HASH_TABLE_T_H
#define HASH_TABLE_T_H

#include "common_macros.h"
#include "xmem.h"
#include <stdint.h>

struct hash_table_entry_t {
    void *data;
    struct hash_table_entry_t *next;
};

struct hash_table_t {
    struct hash_table_entry_t **entries;
    int32_t table_size;
    int32_t (*hash_func)(void *ele);
    void (*free_ele)(void *ele);
    int32_t (*compare_entries)(void *data1, void *data2);
};

struct hash_table_t *make_hash_table_t(int32_t table_size,
                                       void (*free_ele)(void *ele),
                                       int32_t (*hash_func)(void *ele));

void free_hash_table_t(struct hast_table_t* hash_table);

void hash_table_t_add_ele(struct hash_table_t *hash_table, void *data);
void hash_table_t_add_ele_by_copy(struct hash_table_t *hash_table, void *data,
                                  size_t data_size);
void hash_table_t_remove(struct hash_table_t *hash_table, void *data);

#endif
