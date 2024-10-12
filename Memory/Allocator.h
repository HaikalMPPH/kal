#pragma once
#include <stdlib.h>
#include <string.h>
#include "../Types.h"

typedef struct KalAllocator KalAllocator;

struct KalAllocator {
    void* (*alloc)(size_t);
    void (*dealloc)(void*);
};

extern const KalAllocator kalStdAllocator;

#ifdef KAL_MEMORY_ALLOCATOR_IMPL
#include "../Logger.h"

static
void* ZeroAlloc(USize size) {
    void* ptr = malloc(size);
    return ptr;
}

static
void ZeroDealloc(void* ptr) {
    free(ptr);
    ptr = nullptr;
}

const KalAllocator kalStdAllocator = {
    .alloc = ZeroAlloc,
    .dealloc = ZeroDealloc,
};
#endif // kAL_MEMORY_ALLOCATOR_IMPL

