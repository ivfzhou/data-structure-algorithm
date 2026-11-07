#ifndef CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_COMMON_H
#define CN_IVFZHOU_DATA_STRUCTURE_ALGORITHM_COMMON_H

#include <stddef.h>

void* PointerAdd(void* p, size_t delta);

void* PointerMinus(void* p, size_t delta);

unsigned long long PointerDiff(void* p1, void* p2);

#endif
