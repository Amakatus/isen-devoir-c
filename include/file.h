#ifndef READFILE_H
#define READFILE_H
#include "linkedlist.h"


int read_file(char* fileName, struct LinkedList** wordList);
void send_safe_file(const char *argv[], char* safeFiles[], int* safeFileCount);
#endif
