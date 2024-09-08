#ifndef KAL_ALLOCATOR_H
#define KAL_ALLOCATOR_H

#include <stdlib.h>
#include <string.h>
#include "types.h"

void zero_dealloc(void* ptr) {
    free(ptr);
    ptr = NULL;
}
void* zero_malloc(size_t size) {
    void* ptr = malloc(size);
    memset(ptr, 0, size);
    return ptr;
}

typedef struct Allocator {
    void* (*alloc)(size_t);
    void  (*dealloc)(void*);
} Allocator;

const Allocator default_allocator = {
    .alloc   = zero_malloc,
    .dealloc = zero_dealloc
};

#endif // KAL_ALLOCATOR_H
