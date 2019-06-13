#ifndef TRANSLATION_H
#define TRANSLATION_H


#include "hashtable.h"


/**
 * Translates a string from a given language into another
 * @param dictionary The dictionary corressponding to the desired language translation
 * @param original The string to be translated (in the source language)
 * @return A pointer to the translated string, or NULL if the source string isn't in the dictionary
 * @warning THE RETURN POINTER MUST NOT BE MODIFIED! Use `strdup`, `strcpy` or `sprintf` if you need a writable copy. Modifying this could corrupt further searches, amongst other problems.
 */
char * translate(HashTable_t dictionary, char const * original);

/**
 * Translates multiple strings from a given language into another
 * @param dictionary The dictionary corresponding to the desired language translation
 * @param original The array of strings to be translated (in the source language)
 * @param nb_strings The number of strings to translate
 * @return An array of pointers to translated strings (in the destination language). Some pointers may be NULL, which would correspond to strings that couldn't be translated. Note that this array must be freed afterwards!
 */
char ** translate_multiple(const HashTable_t dictionary, char const * const * original, size_t nb_strings);

/**
 * Reads a file and builds a dictionary from it
 * The expected format is this: `source language expression;target language expression`
 * Both expressions may contain spaces, tabs etc, just not semicolons
 * No spaces should appear around the semicolon, though (TODO: improve this?)
 * @param path The path to the file to be parsed
 * @return The created dictionary, or NULL if something went wrong
 */
HashTable_t dict_from_file(char const * path);


#endif
