#include "filters.h"
#include "include/linkedlist.h"
#include "include/search.h"
#include "include/word.h"
#include "include/linenumbers.h"
#include <stdio.h>


void print_search_match(struct LinkedList* linkedList){
    struct Word* wordList = (struct Word*) linkedList;
    printf("Mot trouve : %s \nDans le fichier : %s\n", wordList->word,wordList->fileName);
    printf("Occurence %d\n", wordList->count);
    printf("Lignes : \n");
    struct LinkedList* lineNumbers = wordList->lineNumbers;
    while (lineNumbers != NULL) {
        struct LineNumbers* currentLine = (struct LineNumbers*) lineNumbers->data;
        printf("L%d (%d fois)\n", currentLine->index, currentLine->countPerLign);
        lineNumbers = lineNumbers->next;
    }
}

void search_exact_word(struct LinkedList* wordList, const char* word){
    struct Word* result = (struct Word*)linked_list_search(wordList, exact_match, (void *)word);
    if (result != NULL){
            print_search_match((struct LinkedList*) result); // Peut etre juste retourner une linkedList de word
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

