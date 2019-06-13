
#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "translation.h"


int main(int argc, char * argv[]) {
    HashTable_t dictionary;
    HashTable_t test_dictionary;
    HashTable_t empty_dictionary;
    
    char const * empty_text = "";
    char const * words[] = {"student","book","Peter","bye","please wait"};
    char const * unknown_word = "car";
    
    char ** translated_words;
    
    /*##########################*/
    /*### LOADING FILE TESTS ###*/
    /*##########################*/
    
    test_dictionary = dict_from_file("anglais.txt");
    printf("\n=== English dictionary ===\n");
    print_hashtable(test_dictionary);
    printf("\n Average entry count for the English dictionary: %f\n",average_entry_count(test_dictionary));
    
    empty_dictionary = dict_from_file("empty.txt");
    printf("\n=== Empty dictionary ===\n");
    print_hashtable(empty_dictionary); 
    printf("\n Average entry count for the empty dictionary: %f\n",average_entry_count(empty_dictionary));
   
    
    /*#########################*/
    /*### TRANSLATION TESTS ###*/
    /*#########################*/
    
    printf("\n=== Translate list of words ===\n");
    printf("text: \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n", words[0], words[1], words[2], words[3], words[4]);
    translated_words = translate_multiple(test_dictionary, words, 5);
    printf("translation: \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n", translated_words[0], translated_words[1], translated_words[2], translated_words[3], translated_words[4]);
    free(translated_words);

    printf("\n=== Translate empty text ===\n");
    printf("text: \"%s\"\n", empty_text);
    printf("translation: \"%s\"\n",translate(test_dictionary, empty_text));

    printf("\n=== Translate unknown word ===\n");
    printf("text: \"%s\"\n", unknown_word);
    printf("translation: \"%s\"\n",translate(test_dictionary, unknown_word));
    
    printf("\n=== Translate with empty dictionary ===\n");
    printf("text: \"%s\"\n", words[0]);
    printf("translation: \"%s\"\n",translate(empty_dictionary, words[0]));

   
    destroy_hashtable(test_dictionary);
    destroy_hashtable(empty_dictionary);
    
    
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
