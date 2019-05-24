
#include <stdlib.h>
#include "hashtable.h"


HashTable_t create_hashtable() {
    HashTable_t table = calloc(HASH_MAX, sizeof(HashSubTable_t));

    return table;
}

void destroy_hashtable(HashTable_t table) {
    unsigned i;
    HashSubTableCell_t * free_ptr, * next;

    for(i = 0; i < HASH_MAX; i++) {
        free_ptr = table[i];
        while(free_ptr != NULL) {
            next = free_ptr->next;
            free(free_ptr->word);
            free(free_ptr->translation);
            free(free_ptr);
            free_ptr = next;
        }
    }

    free(table);
}
