#include <stdio.h>
#include "include/linenumbers.h"
#include <stdlib.h>
#include "include/word.h"
#include <include/linkedlist.h>

struct LinkedList* createNewLineNumbers(int line_number){
    if(line_number <= 0){
        perror("ligne inferieure a 0.");
    }
    struct LineNumbers* new_line_numbers = (struct LineNumbers*)malloc(sizeof(struct LineNumbers));
    new_line_numbers -> index = line_number;
    new_line_numbers -> count_per_lign = 1;
    struct LinkedList* new_ll = newLinkedList(new_line_numbers);
    return new_ll;
}

void printWords(struct LinkedList* linkedList) {
    while (linkedList != NULL) {
        struct Word* wordList = (struct Word*) linkedList->data;
        printf("Mot : %s\n", wordList->word);
        printf("Occurrence : %d\n", wordList->count);
        printf("Lignes : ");
        struct LinkedList* line = wordList->line_numbers;
        while (line != NULL) {
            struct LineNumbers* current_line = (struct LineNumbers*) line->data;
            printf("L%d (%d fois) ", current_line->index, current_line->count_per_lign);
            line = line->next;
        }
        printf("\n");
        linkedList = linkedList->next;
    }
}
