#ifndef CREATELINENUMBERS_H
#define CREATELINENUMBERS_H
struct LineNumbers {
    int index;
    int count_per_lign;
};

struct LinkedList* createNewLineNumbers(int line_number);

#endif
