
#define _GNU_SOURCE /* For `getline` */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include "translation.h"


char * translate(const HashTable_t dictionary, char const * original) {
    HashSubTableCell_t * cell = *search_entry(dictionary, original);

    return cell != NULL ? cell->value : NULL;
}

char ** translate_multiple(const HashTable_t dictionary, char const * const * original, size_t nb_strings) {
    char ** translations = calloc(nb_strings, sizeof(char*));
    size_t i;
    for(i = 0; i < nb_strings; i++) {
        translations[i] = translate(dictionary, original[i]);
    }
    return translations;
}


HashTable_t dict_from_file(char const * path) {
    static char const * delimiters = ";\r\n";

    HashTable_t dictionary = create_hashtable();
    FILE * dict_file;

    if(dictionary != NULL) {
        dict_file = fopen(path, "rt");
        if(dict_file != NULL) {
            char * line_buf = NULL; /* Buffer for `getline` */
            size_t line_buf_size = 0; /* Also for `getline` */
            unsigned line_num = 1;

            while(getline(&line_buf, &line_buf_size, dict_file) != -1) {
                /* Process the line being read: attempt to delimit two tokens */
                char * strtok_arg = line_buf; /* Pointer passed to `strtok`, which must be non-NULL on first call only */
                char * token; /* Pointer to the token being returned by `strtok` */
                /* These two hold the last two tokens scanned */
                char * first_token, * second_token; /* Only if there were two tokens, will their names make sense */
                unsigned nb_tokens = 0;
                while((token = strtok(strtok_arg, delimiters)) != NULL) {
                    strtok_arg = NULL; /* Only the first call to strtok must pass a non-null pointer */
                    first_token = second_token;
                    second_token = token;
                    nb_tokens++;
                }

                if(nb_tokens == 2) {
                    insert_hashtable_entry(dictionary, first_token, second_token);
                } else if(nb_tokens != 0) {
                    fprintf(stderr, "Malformed line %u: expected 2 expressions, got %u. Ignoring.\n", line_num, nb_tokens);
                }

                line_num++;
            }

            fclose(dict_file);

        } else {
            free(dictionary);
            dictionary = NULL;
        }
    }

    return dictionary;
}

