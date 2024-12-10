#ifndef READFILE_H
#define READFILE_H
#include "include/linkedlist.h"


int read_file(char* fileName, struct LinkedList** wordList);
void send_safe_file(const char *argv[], char* safe_file[], int* safe_file_count);
#endif
