#ifndef CREATELINENUMBERS_H
#define CREATELINENUMBERS_H
struct LineNumbers {
    int index;
    int count_per_lign;
};

struct LinkedList* create_new_linenumbers(int line_number);

#endif
