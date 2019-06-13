
#include <stdio.h>
#include "hashtable.h"
#include "translation.h"


int main(int argc, char * argv[]) {
    HashTable_t dictionary;
    HashTable_t test_dictionary;
    HashTable_t empty_dictionary;
    
    char empty_text[] = "";
    char words[] = {"student","book","Peter","bye","please wait"};
    char unknown_word[] = "car";
    
    /*##########################*/
    /*### LOADING FILE TESTS ###*/
    /*##########################*/
    
    test_dictionary = dict_from_file("anglais.txt");
    printf("\n=== English dictionary ===\n");
    print_hashtable(test_dictionary);
    printf("/n Average entry count for the English dictionary: %f/n",average_entry_count(test_dictionary));
    
    empty_dictionary = dict_from_file("empty.txt");
    printf("\n=== Empty dictionary ===\n");
    print_hashtable(empty_dictionary); 
    printf("/n Average entry count for the empty dictionary: %f/n",average_entry_count(empty_dictionary));
   
    
    /*#########################*/
    /*### TRANSLATION TESTS ###*/
    /*#########################*/
    
    printf("\n=== Translate list of words ===\n");
    printf("text: %s\n", words);
    printf("translation: %s\n",translate_multiple(test_dictionary, words, len(words)));

    printf("\n=== Translate empty text ===\n");
    printf("text: %s\n", empty_text);
    printf("translation: %s\n",translate_multiple(test_dictionary, empty_text, len(empty_text)));

    printf("\n=== Translate unknown word ===\n");
    printf("text: %s\n", unknown_word);
    printf("translation: %s\n",translate_multiple(test_dictionary, unknown_word, len(unknown_word)));
    
    printf("\n=== Translate with empty dictionary ===\n");
    printf("text: %s\n", words);
    printf("translation: %s\n",translate_multiple(empty_dictionary, words, len(words)));

   
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
