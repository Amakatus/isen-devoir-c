#ifndef FILTERS_H
#define FILTERS_H

int exact_match(void* data, void* type);
int case_insensitive_match(void* data, void* type);
int wildcard_match(void* data, void* type);

#endif
