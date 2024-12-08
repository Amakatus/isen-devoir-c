#ifndef READFILE_H
#define READFILE_H

#include "createlinkedlist.h"

int readFile(char* fileName, struct LinkedList** wordList);
void listSafeFile(const char *argv[]);

#endif
