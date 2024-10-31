#pragma once

#include "../types.h"
#include "bst.h"

// Cleaner syntax for accessing elements
#define KAL_MAP_AT(type, map, key) *(type*)(kal_map_at((map), (key)))

// :: DECL ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
struct kal_map {
    struct kal_bst bst;
};

struct kal_map
kal_map_init(usize value_size);

void
kal_map_deinit(struct kal_map* map);

// Hashing strings to usize using the FNV-1 hashing algorithm.
usize
kal_map_hash_str(const char* key);

void*
kal_map_at(const struct kal_map* map,
            const char* key);

void
kal_map_add(struct kal_map* map,
            const char* key, 
            void* value);

void
kal_map_remove(struct kal_map* map,
               const char* key);




// :: IMPL ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#ifdef KAL_CONTAINER_MAP_IMPL

constexpr usize FNV_OFFSET_BASIS = 0xcbf29ce484222325;
constexpr usize FNV_PRIME = 0x100000001b3;


struct kal_map
kal_map_init(usize value_size) {
    return (struct kal_map) {
        .bst = kal_bst_init(value_size),
    };
}

void
kal_map_deinit(struct kal_map* map) {
    kal_bst_deinit(&map->bst);
}

usize
kal_map_hash_str(const char* key) {
    usize hash = FNV_OFFSET_BASIS;

    while ('\0' != *key) {
        hash *= FNV_PRIME;
        hash ^= (u8)*key;
        ++key;
    }

    return hash;
}

void*
kal_map_at(const struct kal_map* map,
            const char* key)
{
    void* ret = kal_bst_get(&map->bst,
                            kal_map_hash_str(key));

    if (nullptr != ret) {
        return ret;
    }

    printf("Failed to get elements of key: %s\n", key);
    return nullptr;
}

void
kal_map_add(struct kal_map* map,
            const char* key, 
            void* value) 
{
    kal_bst_add(&map->bst,
                kal_map_hash_str(key),
                value);
}

#endif
