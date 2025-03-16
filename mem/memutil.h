#ifndef KAL_MEMUTIL_H
#define KAL_MEMUTIL_H

#include "../types.h"
#include "../defines.h"

static KAL_INLINE
void
kal_byte_copy(
    void* dst,
    const void* src,
    usize size
);

static KAL_INLINE
void
kal_byte_set(
    void* dst,
    u8 byte,
    usize size
);

static KAL_INLINE
bool
kal_byte_compare(
    const void* a,
    const void* b,
    usize size
);

// : IMPLEMENTATION ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
static KAL_INLINE
void
kal_byte_copy(
    void* dst,
    const void* src,
    usize size
) {
    for (usize i = 0; i < size; ++i) {
        ((char*)dst)[i] = ((const char*)src)[i];
    }
}

static KAL_INLINE
void
kal_byte_set(
    void* dst,
    u8 byte,
    usize size
) {
    for (usize i = 0; i < size; ++i) {
        ((u8*)dst)[i] = byte;
    }
}

static KAL_INLINE
bool
kal_byte_compare(
    const void* a,
    const void* b,
    usize size
) {
    bool result = false;

    for (usize i = 0; i < size; ++i) {
        result = ((u8*)a)[i] == ((u8*)b)[i];
    }

    return result;
}

#endif // KAL_MEMUTIL_H
