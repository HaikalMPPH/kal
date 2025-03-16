#ifndef KAL_ALLOCATOR_H
#define KAL_ALLOCATOR_H

#include "../types.h"

typedef struct kal_allocator_s {
    void* (*alloc)(usize);
    void (*dealloc)(void*);
} kal_allocator_s;

kal_allocator_s
kal_allocator_default();


#ifdef KAL_MEM_ALLOCATOR_IMPL
#include <stdlib.h>
#include "../defines.h"
#include "memutil.h"

static KAL_INLINE
void* 
default_alloc(usize size) {
    void* ptr = malloc(size);
    kal_byte_set(ptr, 0, size);
    return ptr;
}

static KAL_INLINE
void 
default_dealloc(void* ptr) {
    free(ptr);
}

kal_allocator_s
kal_allocator_default() {
    return (kal_allocator_s) {
        .alloc = default_alloc,
        .dealloc = default_dealloc,
    };
}
#endif // KAL_MEM_ALLOCATOR_IMPL

#endif // KAL_ALLOCATOR_H
