
#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "hashtable.h"


HashTable_t create_hashtable() {
    HashTable_t table = calloc(HASH_MAX, sizeof(HashSubTable_t));

    return table;
}

void destroy_hashtable(HashTable_t table) {
    unsigned i;
    HashSubTableCell_t * free_ptr, * next;

    for(i = 0; i < HASH_MAX; i++) {
        free_ptr = table[i].table;
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


static unsigned hash_string(char const * string) {
    unsigned hash = 5381;

    while(*string != '\0') {
        hash = ((hash << 5) + hash) + tolower(*string);
        string++;
    }

    return (hash & 0x7FFFFFFF) % HASH_MAX;
}

HashSubTableCell_t * insert_hashtable_entry(HashTable_t table, char const * word, char const * translation) {
    unsigned hash = hash_string(word);
    HashSubTableCell_t * new_cell = malloc(sizeof(HashSubTableCell_t));
    char * word_copy = strdup(word);
    char * translation_copy = strdup(translation);

    if(new_cell != NULL && word != NULL && translation != NULL) {
        new_cell->word = word_copy;
        new_cell->translation = translation_copy;
        /* Insert new cell at the beginning of the list */
        new_cell->next = table[hash].table;
        table[hash].table = new_cell;
        table[hash].nb_entries++;
    } else {
        /* Any allocation failure is fine because `free(NULL)` does nothing */
        free(new_cell);
        free(word_copy);
        free(translation_copy);
        /* Make sure to return failure */
        new_cell = NULL;
    }

    return new_cell;
}

HashSubTableCell_t ** search_entry(const HashTable_t table, char const * word) {
	HashSubTableCell_t ** search_ptr = &table[hash_string(word)].table;
	
	while (*search_ptr != NULL && strcmp((*search_ptr)->word, word) != 0) {
		search_ptr = &(*search_ptr)->next;
	}
	
	return search_ptr;
}


void print_hashtable(const HashTable_t table) {
    unsigned i = 0;
    
    for(; i < HASH_MAX; i++) {
        HashSubTableCell_t * read_ptr = table[i].table;
        printf("[%02u]->", i);
        while(read_ptr != NULL) {
            printf("{\"%s\">\"%s\"}->", read_ptr->word, read_ptr->translation);
            read_ptr = read_ptr->next;
        }
        puts("NULL");
    }
}

float average_entry_count(const HashTable_t table) {
    float sum = 0.0f;
    unsigned i = 0;
    
    for(; i < HASH_MAX; i++) {
        sum += table[i].nb_entries;
    }
    
    return sum / HASH_MAX;
}

