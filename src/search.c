#include "filters.h"
#include "linkedlist.h"
#include "search.h"
#include "word.h"
#include "linenumbers.h"
#include <stdio.h>


void print_search_match(struct LinkedList* linkedList) {
    struct Word* wordList = (struct Word*) linkedList->data;
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


void search_exact_word(struct LinkedList* wordList, const char* word){
    struct Word* result = (struct Word*)linked_list_search(wordList, exact_match, (void *)word);
    if (result != NULL){
            print_search_match((struct LinkedList*) result);
    } else {
        printf("Mot non trouve: %s\n", word);
    }
}

void search_case_insensitive(struct LinkedList* wordList, const char* word){
    struct Word* result = (struct Word*)linked_list_search(wordList, case_insensitive_match,(void*) word);
    if (result != NULL){
        print_search_match((struct LinkedList*)result);
    } else {
        printf("Mot non trouve: %s\n", word);
    }
}

void search_wildcard(struct LinkedList* wordList, const char* word) {
    struct LinkedList* results = NULL;
    struct LinkedList* currentNode = wordList;

    while (currentNode != NULL) {
        struct Word* wordItem = (struct Word*) currentNode->data;
        if (wildcard_match(wordItem, word)) {
            struct LinkedList* newNode = new_linked_list(wordItem);
            if (results == NULL) {
                results = newNode;
            } else {
                struct LinkedList* temp = results;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
        currentNode = currentNode->next;
    }
    if (results != NULL) {
        struct LinkedList* resultNode = results;
        while (resultNode != NULL) {
            print_search_match(resultNode);
            resultNode = resultNode->next;
        }
    } else {
        printf("Aucun mot trouvé pour le mot: %s\n", word);
    }

}

