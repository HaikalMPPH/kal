#ifndef KAL_ALLOCATOR_H
#define KAL_ALLOCATOR_H

#include <stdlib.h>
#include <string.h>
#include "types.h"

void zero_dealloc(void* ptr);
void* zero_malloc(size_t size);

typedef struct Allocator {
    void* (*alloc)(size_t);
    void  (*dealloc)(void*);
} Allocator;

extern const Allocator default_allocator;

#ifdef KAL_ALLOCATOR_IMPL
const Allocator default_allocator = {
    .alloc   = zero_malloc,
    .dealloc = zero_dealloc
};

void zero_dealloc(void* ptr) {
    free(ptr);
    ptr = NULL;
}
void* zero_malloc(size_t size) {
    void* ptr = malloc(size);
    memset(ptr, 0, size);
    return ptr;
}
#endif // KAL_ALLOCATOR_IMPL
#endif // KAL_ALLOCATOR_H

