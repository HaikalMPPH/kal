#ifndef KAL_ALLOCATOR_H
#define KAL_ALLOCATOR_H

#include <stdlib.h>
#include <string.h>
#include "../types.h"

void  zero_dealloc(void* ptr);
void* zero_alloc  (usize size);

typedef struct kal_allocator_s {
    void* (*alloc)(size_t);
    void  (*dealloc)(void*);
} kal_allocator_s;

extern const kal_allocator_s kal_default_allocator;

#ifdef KAL_ALLOCATOR_H_IMPL
#include "../logger.h"

const kal_allocator_s kal_default_allocator = {
    .alloc   = zero_alloc,
    .dealloc = zero_dealloc
};

void 
zero_dealloc(void* ptr) {
    if (ptr != NULL) {
        free(ptr);
        ptr = NULL;
    }
}
void* 
zero_alloc(usize size) {
    void* ptr = malloc(size);

    if (!ptr) {
        DEBUG_LOG_MSG(ERROR, "Failed to allocated memory!");
        exit(EXIT_FAILURE);
    }

    memset(ptr, 0, size);
    return ptr;
}
#endif // kAL_ALLOCATOR_H_IMPL
#endif // KAL_ALLOCATOR_H

