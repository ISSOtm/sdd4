#ifndef HASHTABLE_H
#define HASHTABLE_H


#define HASH_MAX 29

typedef struct HashSubTableCell {
    char * key;
    char * value;
    struct HashSubTableCell * next;
} HashSubTableCell_t;

typedef struct {
    HashSubTableCell_t * table;
    unsigned nb_entries;
} HashSubTable_t;

/* The size of a has table is known, but declaring it as an array
 * creates a whole slew of problems when trying to allocate dynamically */
typedef HashSubTable_t* HashTable_t;


HashTable_t create_hashtable();

void destroy_hashtable(HashTable_t table);


HashSubTableCell_t * insert_hashtable_entry(HashTable_t table, char const * word, char const * translation);

HashSubTableCell_t ** search_entry(const HashTable_t table, char const * word);


void print_hashtable(const HashTable_t table);

float average_entry_count(const HashTable_t table);

#endif
