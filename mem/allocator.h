#pragma once
#include <stdlib.h>
#include <string.h>
#include "../types.h"

// Allocator function: void* (*)(size_t)
#ifndef KAL_ALLOC
# define KAL_ALLOC malloc
#endif

// De-allocator function: void (*)(void*)
#ifndef KAL_DEALLOC
# define KAL_DEALLOC free
#endif

typedef struct kal_allocator_s {
    void* (*alloc)(usize);
    void (*dealloc)(void*);
} kal_allocator_s;

extern const kal_allocator_s kal_std_allocator;

#ifdef KAL_MEM_ALLOCATOR_IMPL
static
void* 
std_alloc(usize size) {
    void* ptr = malloc(size);
    return ptr;
}

static
void 
std_dealloc(void* ptr) {
    free(ptr);
}

const kal_allocator_s kal_std_allocator = {
    .alloc   = std_alloc,
    .dealloc = std_dealloc,
};
#endif // kAL_MEMORY_ALLOCATOR_IMPL

