
#include <stdio.h>
#include "hashtable.h"


int main() {
    HashTable_t dictionary = create_hashtable();

    destroy_hashtable(dictionary);

    return 0;
}
