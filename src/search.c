#include "filters.h"
#include "linkedlist.h"
#include "search.h"
#include "word.h"
#include "linenumbers.h"
#include <stdio.h>

/**
 * @brief 
 * 
 * @param linkedList 
 */
void print_search_match(struct Word* wordList) {
    if (wordList == NULL) {
        printf("Erreur : mot non trouvé ou invalid.\n");
        return;
    }

    printf("Mot trouvé : %s \nDans le fichier : %s\n", wordList->word, wordList->fileName);
    printf("Occurence %d\n", wordList->count);
    printf("Lignes : \n");

    struct LinkedList* lines = wordList->lineNumbers;
    while (lines != NULL) {
        struct LineNumbers* currentLine = (struct LineNumbers*) lines->data;
        printf("L%d (%d fois)\n", currentLine->index, currentLine->countPerLign);
        lines = lines->next;
    }
}


/**
 * @brief 
 * 
 * @param wordList 
 * @param word 
 */
void search_exact_word(struct LinkedList* wordList, char* word) {
    struct Word* result = (struct Word*)linked_list_search(wordList, exact_match, (void *)word);
    if (result != NULL) {
        print_search_match(result);
    } else {
        printf("Mot non trouvé: %s\n", word);
    }
}

void search_case_insensitive(struct LinkedList* wordList, char* word){
    struct Word* result = (struct Word*)linked_list_search(wordList, case_insensitive_match,(void*) word);
    if (result != NULL){
        print_search_match(result);
    } else {
        printf("Mot non trouve: %s\n", word);
    }
}


void search_wildcard(struct LinkedList* wordList, char* word) {
    struct LinkedList* resultNode = (struct LinkedList*) linked_list_search(wordList, wildcard_match, (void *)word);
    if (resultNode != NULL) {
        struct LinkedList* iterList = resultNode;
        while (iterList != NULL) {
            struct Word* wordData = (struct Word*) iterList->data;
            if (wordData != NULL) {
                printf("Mot trouvé : %s \nDans le fichier : %s\n", wordData->word, wordData->fileName);
                printf("Occurence %d\n", wordData->count);
                printf("Lignes : \n");
                struct LinkedList* lines = wordData->lineNumbers;
                while (lines != NULL) {
                    struct LineNumbers* currentLine = (struct LineNumbers*) lines->data;
                    printf("L%d (%d fois)\n", currentLine->index, currentLine->countPerLign);
                    lines = lines->next;
                }
            } else {
                printf("Erreur: mot invalide dans la liste liée.\n");
            }
            iterList = iterList->next;
        }
    } else {
        printf("Aucun mot trouvé pour le mot: %s\n", word);
    }
}






