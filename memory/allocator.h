#pragma once
#include <stdlib.h>
#include <string.h>
#include "../types.h"

typedef struct allocator_s allocator_s;

struct allocator_s {
    void* (*alloc)(usize);
    void (*dealloc)(void*);
};

extern const allocator_s std_allocator;

#ifdef KAL_MEMORY_ALLOCATOR_IMPL
#include "../logger.h"

static
void* std_alloc(usize size) {
    void* ptr = malloc(size);
    return ptr;
}

static
void std_dealloc(void* ptr) {
    free(ptr);
    ptr = nullptr;
}

const allocator_s std_allocator = {
    .alloc = std_alloc,
    .dealloc = std_dealloc,
};
#endif // kAL_MEMORY_ALLOCATOR_IMPL

