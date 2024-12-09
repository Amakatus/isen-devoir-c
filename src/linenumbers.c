#include <stdio.h>
#include "include/linenumbers.h"
#include <stdlib.h>
#include <include/linkedlist.h>

struct LinkedList* createNewLineNumbers(int line_number){
    if(line_number <= 0){
        perror("ligne inferieure a 0.");
    }
    struct LineNumbers* new_line_numbers = (struct LineNumbers*)malloc(sizeof(struct LineNumbers));
    new_line_numbers->index = line_number;
    new_line_numbers->count_per_lign = 1;
    struct LinkedList* new_ll = newLinkedList(new_line_numbers);
    return new_ll;
}

