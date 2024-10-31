#pragma once
#include <stdlib.h>
#include <string.h>
#include "../types.h"

#ifndef KAL_ALLOC
# define KAL_ALLOC malloc
#endif

#ifndef KAL_DEALLOC
# define KAL_DEALLOC free
#endif


struct kal_allocator {
    void* (*alloc)(usize);
    void (*dealloc)(void*);
};

extern const struct kal_allocator kal_std_allocator;

#ifdef KAL_MEMORY_ALLOCATOR_IMPL
#include "../logger.h"

static
void* 
stdAlloc(usize size) {
    void* ptr = malloc(size);
    return ptr;
}

static
void 
stdDealloc(void* ptr) {
    free(ptr);
    ptr = nullptr;
}

const struct kal_allocator kal_std_allocator = {
    .alloc   = stdAlloc,
    .dealloc = stdDealloc,
};
#endif // kAL_MEMORY_ALLOCATOR_IMPL

