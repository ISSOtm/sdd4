
#include <stdio.h>
#include "hashtable.h"
#include "translation.h"


int main(int argc, char * argv[]) {
    HashTable_t dictionary;
    
    if(argc < 2) {
        printf("Usage:  %s path/to/language.file\n", argv[0]);
    
    } else {
        dictionary = dict_from_file(argv[1]);
        if(dictionary == NULL) {
            perror("Failed to open language file");
        
        } else {
            printf("Average entry count: %f\n", average_entry_count(dictionary));

            printf("\"hello\" gets translated to: %s\n", translate(dictionary, "hello"));

            destroy_hashtable(dictionary);
        }
    }

    return 0;
}
