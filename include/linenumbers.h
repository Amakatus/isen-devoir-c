#ifndef CREATELINENUMBERS_H
#define CREATELINENUMBERS_H
struct LineNumbers {
    int index;
    int countPerLign;
};

struct LinkedList* create_new_linenumbers(int lineNumber);

#endif
