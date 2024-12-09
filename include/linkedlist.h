#ifndef CREATELINKEDLIST_H
#define CREATELINKEDLIST_H

struct LinkedList{
    struct LinkedList *next;
    void* data;
};

struct LinkedList* newLinkedList(void* data);
void freeStructs(struct LinkedList* linkedList);

#endif
