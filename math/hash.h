#pragma once

#include "../types.h"
#include "../defines.h"

static KAL_INLINE
usize
kal_hash_fnv1a(
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
