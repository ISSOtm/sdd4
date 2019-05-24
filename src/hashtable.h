#ifndef HASHTABLE_H
#define HASHTABLE_H


#define HASH_MAX 29

typedef struct HashSubTableCell {
    char * word;
    char * translation;
    struct HashSubTableCell * next;
} HashSubTableCell_t;

typedef HashSubTableCell_t* HashSubTable_t;

/* The size of a has table is known, but declaring it as an array
 * creates a whole slew of problems when trying to allocate dynamically */
typedef HashSubTable_t* HashTable_t;


HashSubTable_t * create_hashtable();

void destroy_hashtable(HashTable_t table);


#endif