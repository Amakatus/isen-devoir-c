#include "filters.h"
#include "include/linkedlist.h"
#include "include/search.h"
#include "include/word.h"
#include "include/linenumbers.h"
#include <stdio.h>


void search_exact_word(struct LinkedList* wordList, const char* word){
    struct Word* result = (struct Word*)linked_list_search(wordList, exact_match, (void *)word);
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

void search_case_insensitive(struct LinkedList* wordList, const char* word){
    struct Word* result = (struct Word*)linked_list_search(wordList, case_insensitive_match,(void*) word);
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
