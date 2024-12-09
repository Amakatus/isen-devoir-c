#ifndef FILTERS_H
#define FILTERS_H

int exactMatch(void* data, void* type);
int caseInsensitiveMatch(void* data, void* type);
int wildcardMatch(void* data, void* type);

#endif
