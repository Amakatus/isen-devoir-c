#include <stdio.h>
#include <stdlib.h>
#include "include/linkedlist.h"
#include "include/word.h"

struct LinkedList* newLinkedList(void* data){
    struct LinkedList* new_ll = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    new_ll->next = NULL;
    new_ll->data = data;
    return new_ll;
}

void freeStructs(struct LinkedList* linkedList){
    while(linkedList != NULL){
        struct Word* wordList = (struct Word*) linkedList->data;
        struct LinkedList* lines = wordList->line_numbers;
        while(lines != NULL){
            struct LineNumbers* current_line = (struct LineNumbers*) lines->data;
            free(current_line);
            lines = lines->next;
        }
        free(wordList->word);
        free(wordList);
        struct LinkedList* temp = linkedList;
        linkedList = linkedList->next;
        free(temp);
    }
}
