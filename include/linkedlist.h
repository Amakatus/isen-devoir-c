#ifndef CREATELINKEDLIST_H
#define CREATELINKEDLIST_H

struct LinkedList{
    struct LinkedList *next;
    void* data;
};

struct LinkedList* newLinkedList(void* data);
void* LinkedListSearch(struct LinkedList* data, int (*filter)(void* data, void* type), void* type);
void freeStructs(struct LinkedList* linkedList);

#endif
