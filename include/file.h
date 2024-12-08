#ifndef READFILE_H
#define READFILE_H
#include "include/linkedlist.h"

struct File {
    char* name;
};

struct LinkedList* createFile(char* fileName);
int readFile(char* fileName, struct LinkedList** wordList);
void sendSafeFile(const char *argv[], char* safe_file[], int* safe_file_count);
#endif
