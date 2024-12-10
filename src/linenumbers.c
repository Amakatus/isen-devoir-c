#include <stdio.h>
#include "include/linenumbers.h"
#include <stdlib.h>
#include <include/linkedlist.h>

struct LinkedList* create_new_linenumbers(int lineNumber){
    if(lineNumber <= 0){
        perror("ligne inferieure a 0.");
    }
    struct LineNumbers* newLineNumbers = (struct LineNumbers*)malloc(sizeof(struct LineNumbers));
    newLineNumbers->index = lineNumber;
    newLineNumbers->countPerLign = 1;
    struct LinkedList* newLinkedList = new_linked_list(newLineNumbers);
    return newLinkedList;
}

