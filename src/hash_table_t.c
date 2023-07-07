#include "hash_table_t.h"

struct hash_table_t *make_hash_table_t(int32_t table_size,
                                       void (*free_ele)(void *ele),
                                       int32_t (*hash_func)(void *ele)) {
    FAIL_IF_NULL(hash_func);
    FAIL_IF_NEGATIVE(table_size);

    struct hash_table_t *hash_table = xmalloc(sizeof(struct hash_table_t));
    hash_table->entries = xcalloc(table_size, sizeof(void *));

    return NULL;
}

void hash_table_t_add_ele(struct hash_table_t *hash_table, void *data) {
    // we cannot add and element to null hash table.
    FAIL_IF_NULL(hash_table);
    // hash tables cannot work with null data.
    FAIL_IF_NULL(data);
    // create a new hash table entry object.
    struct hash_table_entry_t *new_entry =
        xmalloc(sizeof(struct hash_table_entry_t));
    new_entry->data = data;
    new_entry->next = NULL;
    // get the hash value of the given data.
    int32_t hashing_result = hash_table->hash_func(data);

    // test if hash_table has a chain that might have the entry already there.
    if (hash_table->entries[hashing_result]) {
        // yes there is a chain,
        // now see wheather their is an entry in the chain with the same data.
        // this is an iterator for the chain.
        struct hash_table_entry_t *it = hash_table->entries[hashing_result];
        do {
            // compare the given data with the current entry data.
            int32_t compare_result =
                hash_table->compare_entries(data, it->data);

            if (!compare_result) {
                // if they are equal.
                // free the created entry above and free the given data payload
                // using the free function from the hash function.
                hash_table->free_ele(data);
                free(new_entry);
                // then return.
                return;
            } else {
                // if they are not equal.
                // just advance the iterator.
                it = it->next;
            }
        } while (it->next);
        // if aftet iterating over the chain of entries at that index just
        // append the new entry to it.
        it->next = new_entry;
    } else {
        // if there is not chain at all, then make new_entry the first one.
        hash_table->entries[hashing_result] = new_entry;
    }
}

void hash_table_t_add_ele_by_copy(struct hash_table_t *hash_table, void *data,
                                  size_t data_size) {
    // we cannot add and element to null hash table.
    FAIL_IF_NULL(hash_table);
    // hash tables cannot work with null data.
    FAIL_IF_NULL(data);
    // create a new hash table entry object.
    struct hash_table_entry_t *new_entry =
        xmalloc(sizeof(struct hash_table_entry_t));
    new_entry->data = copy(data, data_size);
    new_entry->next = NULL;
    // get the hash value of the given data.
    int32_t hashing_result = hash_table->hash_func(data);

    // test if hash_table has a chain that might have the entry already there.
    if (hash_table->entries[hashing_result]) {
        // yes there is a chain,
        // now see wheather their is an entry in the chain with the same data.
        // this is an iterator for the chain.
        struct hash_table_entry_t *it = hash_table->entries[hashing_result];
        do {
            // compare the given data with the current entry data.
            int32_t compare_result =
                hash_table->compare_entries(data, it->data);

            if (!compare_result) {
                // if they are equal.
                // free the created entry above and free the given data payload
                // using the free function from the hash function.
                hash_table->free_ele(new_entry->data);
                free(new_entry);
                // then return.
                return;
            } else {
                // if they are not equal.
                // just advance the iterator.
                it = it->next;
            }
        } while (it->next);
        // if aftet iterating over the chain of entries at that index just
        // append the new entry to it.
        it->next = new_entry;
    } else {
        // if there is not chain at all, then make new_entry the first one.
        hash_table->entries[hashing_result] = new_entry;
    }
}

void hash_table_t_remove(struct hash_table_t *hash_table, void *data) {
    // we cannot add and element to null hash table.
    FAIL_IF_NULL(hash_table);
    // hash tables cannot work with null data.
    FAIL_IF_NULL(data);

    int32_t hashing_result = hash_table->hash_func(data);
    struct hash_table_entry_t *it;
    void *temp_data;
    if ((it = hash_table->entries[hashing_result])) {
        do {
            int32_t compare_result =
                hash_table->compare_entries(data, it->data);

            if (!compare_result) {
                hash_table->free_ele(it->data);
                hash_table->entries[hashing_result] = it->next;
            }
        } while (it->next);
        return;
    }
    return;
}
