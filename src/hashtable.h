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

/* The size of a hash table is known, but declaring it as an array
 * creates a whole slew of problems when trying to allocate dynamically */
typedef HashSubTable_t* HashTable_t;


/**
 * Creates a hash table and initializes it
 * @return A pointer to the created hash table, or NULL in case of error
 */
HashTable_t create_hashtable();

/**
 * Destroys a hash table, properly freeing it and all pointers it contains
 * @param table The table to be destroyed
 */
void destroy_hashtable(HashTable_t table);


/**
 * Inserts a new entry into a hash table
 * The strings passed to thins function are duplicated for internal use, so it's safe to `free` the arguments after this returns
 * @param table The table to insert a new entry into
 * @param The key where to insert the value to
 * @param The value to insert
 * @return A pointer to the inserted cell or NULL if an error occurred
 */
HashSubTableCell_t * insert_hashtable_entry(HashTable_t table, char const * key, char const * value);

/**
 * Search for a value in a table by its key
 * @param table The table to search into
 * @param key The key to search for
 * @return A pointer to the pointer to the cell holding the demanded key (useful for example for insertion or removal)
 */
HashSubTableCell_t ** search_entry(const HashTable_t table, char const * key);


/**
 * Prints a hashtable's contents in a "raw" way to stdout
 * @param table The table to print
 */
void print_hashtable(const HashTable_t table);

/**
 * Returns the average number of entries per "hash key"
 * @param table The table to compute the mean over
 */
float average_entry_count(const HashTable_t table);


#endif
