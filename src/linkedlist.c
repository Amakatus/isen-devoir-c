#include <stdio.h>
#include <stdlib.h>
#include "include/linkedlist.h"

struct LinkedList* newLinkedList(void* data){
    struct LinkedList* new_ll = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    new_ll -> next = NULL;
    new_ll -> data = data;
    return new_ll;
}
