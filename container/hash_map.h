#ifndef KAL_HASH_MAP_H
#define KAL_HASH_MAP_H

#include <string.h>
#include "../types.h"
#include "../container/dynarray.h"
#include "../memory/allocator.h"

// TODO: NOT DONE.

// :::::::::::::::::::::::::::::: DECLARATION ::::::::::::::::::::::::::::::::::::::
#define hash_map_get(map, key)\
do {\
\
} while (0)

// Hashing function based on FNV-1a algorithm
usize hash_map_hash  (const char* key, usize num_of_elements);
void* hash_map_init  (usize type_size, const kal_allocator_s* allocator);
void  hash_map_deinit(void* hash_map);


// :::::::::::::::::::::::::::::: IMPLEMENTATION :::::::::::::::::::::::::::::::::::
#ifdef HASH_MAP_H_IMPL
enum : usize {
    FNV_OFFSET_BASIS = 0xcbf29ce484222325,
    FNV_PRIME        = 0x00000100000001b3,
};

usize 
hash_map_hash(const char* key, usize num_of_elements) {
    usize hashed_index = FNV_OFFSET_BASIS;

    for (usize i = 0; i < strlen(key); ++i) {
        hashed_index ^= key[i];
        hashed_index *= FNV_PRIME;
    }

    return hashed_index % num_of_elements;
}

void* 
hash_map_init(usize type_size, const kal_allocator_s* allocator) {
    return kal_dynarray_init(type_size, allocator);
}

void 
hash_map_deinit(void* hash_map) {
    kal_dynarray_deinit(hash_map);
}
#endif // HASH_MAP_H_IMPL

#endif // KAL_HASH_MAP_H
