#ifndef TRADUCTION_H
#define TRADUCTION_H


#include "hashtable.h"


char * translate(HashTable_t dictionary, char const * original);

HashTable_t dict_from_file(char const * path);


#endif
