
#include <stdio.h>
#include "translation.h"


int main() {
    HashTable_t dictionary = dict_from_file("anglais.txt");
    
    printf("hello -> %s\n", translate(dictionary, "hello"));

    destroy_hashtable(dictionary);

    return 0;
}
