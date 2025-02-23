#ifndef KAL_MEMUTIL_H
#define KAL_MEMUTIL_H

#include "kal_types.h"
#include "kal_defines.h"

KAL_INLINE
void
kal_memutil_byte_copy(
    void* dst,
    const void* src,
    usize size
);

KAL_INLINE
void
kal_memutil_byte_set(
    void* dst,
    u8 byte,
    usize size
);

KAL_INLINE
bool
kal_memutil_byte_compare(
    const void* a,
    const void* b,
    usize size
);

// : IMPLEMENTATION ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
KAL_INLINE
void
kal_memutil_byte_copy(
    void* dst,
    const void* src,
    usize size
) {
    for (usize i = 0; i < size; ++i) {
        ((u8*)dst)[i] = ((const char*)src)[i];
    }
}

KAL_INLINE
void
kal_memutil_byte_set(
    void* dst,
    u8 byte,
    usize size
) {
    for (usize i = 0; i < size; ++i) {
        ((u8*)dst)[i] = byte;
    }
}

KAL_INLINE
bool
kal_memutil_byte_compare(
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
