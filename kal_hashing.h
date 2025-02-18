#pragma once
#include "kal_types.h"
#include "kal_defines.h"

KAL_INLINE
usize
kal_hashing_fnv1a(
    const char* str
) {
    usize hash = 0xcbf29ce484222325; // fnv offset basis
    const u64 fnv_prime = 0x100000001b3;

    for (; *str; ++str) {
        hash ^= *str;
        hash *= fnv_prime;
    }

    return hash;
}
