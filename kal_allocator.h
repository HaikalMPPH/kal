#pragma once
#include "kal_types.h"

typedef struct kal_allocator_s {
    void* (*alloc)(usize);
    void (*dealloc)(void*);
} kal_allocator_s;

extern const kal_allocator_s kal_std_allocator;


#ifdef KAL_ALLOCATOR_IMPL
#include <stdlib.h>
#include <string.h>
#include "kal_defines.h"

KAL_INLINE
void* 
std_alloc(usize size) {
    void* ptr = malloc(size);
    memset(ptr, 0, size);
    return ptr;
}

KAL_INLINE
void 
std_dealloc(void* ptr) {
    free(ptr);
}

const kal_allocator_s kal_std_allocator = {
    .alloc = std_alloc,
    .dealloc = std_dealloc,
};
#endif // kAL_ALLOCATOR_IMPL

