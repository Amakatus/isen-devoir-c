#ifndef CREATELINKEDLIST_H
#define CREATELINKEDLIST_H

struct LinkedList{
    struct LinkedList *next;
    void* data;
};

struct LinkedList* new_linked_list(void* data);
void* linked_list_search(struct LinkedList* data, int (*filter)(void* data, void* type), void* type);
void free_structs(struct LinkedList* linkedList);

#endif
