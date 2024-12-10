#include <stdio.h>
#include "include/linenumbers.h"
#include <stdlib.h>
#include <include/linkedlist.h>

struct LinkedList* create_new_linenumbers(int lineNumber){
    if(lineNumber <= 0){
        perror("ligne inferieure a 0.");
    }
    struct LineNumbers* new_line_numbers = (struct LineNumbers*)malloc(sizeof(struct LineNumbers));
    new_line_numbers->index = lineNumber;
    new_line_numbers->countPerLign = 1;
    struct LinkedList* new_ll = new_linked_list(new_line_numbers);
    return new_ll;
}

