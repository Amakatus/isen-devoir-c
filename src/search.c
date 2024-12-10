#include "filters.h"
#include "include/linkedlist.h"
#include "include/search.h"
#include "include/word.h"
#include "include/linenumbers.h"
#include <stdio.h>


void searchExactWord(struct LinkedList* wordList, const char* word){
    struct Word* result = (struct Word*)LinkedListSearch(wordList, exactMatch, (void *)word);
    if (result != NULL){
        printf("Mot trouve : %s \nDans le fichier : %s\n", result->word,result->fileName);
        printf("Occurence %d\n", result->count);
        printf("Lignes : \n");
        struct LinkedList* line = result->line_numbers;
        while (line != NULL) {
            struct LineNumbers* current_line = (struct LineNumbers*) line->data;
            printf("L%d (%d fois)\n", current_line->index, current_line->count_per_lign);
            printf("Fichier : %s",result->fileName);
            line = line->next;
        }
    } else {
        printf("Mot non trouve: %s\n", word);
    }
}

void searchCaseInsensitive(struct LinkedList* wordList, const char* word){
    struct Word* result = (struct Word*)LinkedListSearch(wordList, caseInsensitiveMatch,(void*) word);
        if (result != NULL){
        printf("Mot trouve : %s \nDans le fichier : %s\n", result->word,result->fileName);
        printf("Occurence %d\n", result->count);
        printf("Lignes : \n");
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
