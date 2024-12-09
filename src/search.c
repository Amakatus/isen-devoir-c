#include "filters.h"
#include "include/linkedlist.h"
#include "include/search.h"
#include "include/word.h"
#include "include/linenumbers.h"
#include <stdio.h>


void searchExactWord(struct LinkedList* wordList, const char* word){
    struct Word* result = (struct Word*)LinkedListSearch(wordList, exactMatch, (void *)word);
    if (result != NULL){
        printf("Mot trouve dans le fichier : %s\n", result->word);
        printf("Occurence %d\n", result->count);
        printf("Lignes : \n");

        // Now print the line numbers where the word occurred
        struct LinkedList* line = result->line_numbers;
        while (line != NULL) {
            struct LineNumbers* current_line = (struct LineNumbers*) line->data;
            printf("L%d (%d fois)\n", current_line->index, current_line->count_per_lign);
            line = line->next;
        }
    } else {
        printf("Mot non trouve: %s\n", word);
    }
}

//void searchCaseInsensitive(struct LinkedList* wordlist, const char* word){

//}