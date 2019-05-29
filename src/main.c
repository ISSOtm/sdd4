
#include <stdio.h>
#include "hashtable.h"
#include "translation.h"


int main(int argc, char * argv[]) {
    HashTable_t dictionary;

    if(argc < 3) {
        printf("Usage:  %s path/to/language.file word_to_translate\n", argv[0]);

    } else {
        dictionary = dict_from_file(argv[1]);
        if(dictionary == NULL) {
            perror("Failed to open language file");

        } else {
            printf("Average entry count: %f\n", average_entry_count(dictionary));

            print_hashtable(dictionary);

            printf("\"%s\" gets translated to: \"%s\"\n", argv[2], translate(dictionary, argv[2]));

            destroy_hashtable(dictionary);
        }
    }

    return 0;
}
