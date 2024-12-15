#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "word.h"

struct LinkedList* new_linked_list(void* data){
    struct LinkedList* newLinkedList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    newLinkedList->next = NULL;
    newLinkedList->data = data;
    return newLinkedList;
}


/**
 * @brief 
 * 
 * @param linkedList 
 */
void free_structs(struct LinkedList* linkedList){
    while(linkedList != NULL){
        struct Word* wordList = (struct Word*) linkedList->data;
        struct LinkedList* lines = wordList->lineNumbers;
        while(lines != NULL){
            struct LineNumbers* currentLine = (struct LineNumbers*) lines->data;
            free(currentLine);
            lines = lines->next;
        }
        free(wordList->word);
        free(wordList);
        struct LinkedList* temp = linkedList;
        linkedList = linkedList->next;
        free(temp);
    }
}

void* linked_list_search(struct LinkedList* data, int (*filter)(void* data, void* type), void* type){
    if (data == NULL || filter == NULL) {
        return NULL;
    }
    struct LinkedList* current = data;
    while (current != NULL){
        if(filter(current->data, type)){
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}
