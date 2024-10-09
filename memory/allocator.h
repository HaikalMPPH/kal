#pragma once
#include <stdlib.h>
#include <string.h>
#include "../types.h"

typedef struct kal_allocator_s kal_allocator_s;

struct kal_allocator_s {
    void* (*alloc)(size_t);
    void (*dealloc)(void*);
};

extern const kal_allocator_s kal_stdlib_allocator;

#ifdef KAL_MEMORY_ALLOCATOR_H_IMPL
#include "../logger.h"

const kal_allocator_s kal_stdlib_allocator = {
    .alloc   = malloc,
    .dealloc = free
};
#endif // kAL_MEMORY_ALLOCATOR_H_IMPL

