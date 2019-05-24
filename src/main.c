
#include <stdio.h>
#include "hashtable.h"


int main() {
    HashTable_t dictionary = create_hashtable();
    char const string[] = "bonjour";
    char const str2[] = "ola";

    insert_hashtable_entry(dictionary, string, str2);

    destroy_hashtable(dictionary);

    return 0;
}
