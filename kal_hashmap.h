// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Name: kal_hashmap.h
// Desc: Open addressing hashmap/hashtable
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#pragma once

#include "kal_allocator.h"
#include "kal_types.h"
#include <string.h>

typedef struct kal_hashmap_s kal_hashmap_s;
typedef struct kal_hashmap_kv_s kal_hashmap_kv_s;

struct kal_hashmap_kv_s {
    const char* key;
    u8 item[];
};

struct kal_hashmap_s {
    usize size;
    usize capacity;
    usize element_size;
    const kal_allocator_s* allocator;
    usize (*hash_function)(const char*);
    kal_hashmap_kv_s* kvs;
};

kal_hashmap_s
kal_hashmap_init(
    usize element_size,
    usize init_capacity,
    usize (*hash_function)(const char*),
    const kal_allocator_s* allocator
);

void
kal_hashmap_deinit(
    kal_hashmap_s* h
);

// Distance (in bytes) of each kv in the hashmap
// Basically sizeof(kv) + element_size
usize
kal_hashmap_kv_stride(
    const kal_hashmap_s* h
);

void
kal_hashmap_remove_at(
    kal_hashmap_s* h,
    const char* key
);

void
kal_hashmap_add(
    kal_hashmap_s* h,
    const char* key,
    void* val
);

void
kal_hashmap_set(
    kal_hashmap_s* h,
    const char* key,
    void* val
);

void*
kal_hashmap_get(
    const kal_hashmap_s* h,
    const char* key
);

#ifdef KAL_HASHMAP_IMPL
#include "kal_defines.h"

KAL_INLINE
void
ensure_cap(
    kal_hashmap_s* h
);

kal_hashmap_s
kal_hashmap_init(
    usize element_size,
    usize init_capacity,
    usize (*hash_function)(const char*),
    const kal_allocator_s* allocator
) {
    return (kal_hashmap_s) {
        .size = 0,
        .capacity = init_capacity,
        .element_size = element_size,
        .allocator = allocator,
        .hash_function = hash_function,

        // Look for "C flexible array member"
        .kvs = allocator->alloc(
            (sizeof(kal_hashmap_kv_s) + sizeof(u8[element_size]))
            * init_capacity
        ),
    };
}

// Removal might not be used for personal use.
void
kal_hashmap_remove_at(
    kal_hashmap_s* h,
    const char* key
) {
    memset(
        kal_hashmap_get(h, key),
        0,
        h->element_size
    );
    --h->size;
}

void
kal_hashmap_deinit(
    kal_hashmap_s* h
) {
    h->allocator->dealloc(h->kvs);
}

usize
kal_hashmap_kv_stride(
    const kal_hashmap_s* h
) {
    return (sizeof(kal_hashmap_kv_s) + (h->element_size));
}

void
kal_hashmap_add(
    kal_hashmap_s* h,
    const char* key,
    void* val
) {
    usize index = {};

    ensure_cap(h);
    index = h->hash_function(key) % h->capacity;

    // Some pointer voodoo.
    kal_hashmap_kv_s* kv_ptr = (kal_hashmap_kv_s*)(
        ((char*)h->kvs) + (kal_hashmap_kv_stride(h) * index)
    );

    for (usize i = 0; i < h->capacity; ++i) {
        // if the byte/string that resides in this ptr is not null.
        // kal_std_allocator always initialized the memory to zero when allocating.
        if (kv_ptr->key != NULL && *kv_ptr->key != 0) {
            // Linear probing
            index = (index + 1) % h->capacity;
            kv_ptr = (kal_hashmap_kv_s*)(
                ((char*)h->kvs) + (kal_hashmap_kv_stride(h) * index)
            );

            continue;
        }
        
        break;
    }
    kv_ptr->key = key;
    memcpy(
        //((char*)kv_ptr) + sizeof(h->kvs->key),
        kv_ptr->item,
        val,
        h->element_size
    );
    ++h->size;

    return;
}

void
kal_hashmap_set(
    kal_hashmap_s* h,
    const char* key,
    void* val
) {
    memcpy(
        kal_hashmap_get(h, key),
        val,
        h->element_size
    );
}

void*
kal_hashmap_get(
    const kal_hashmap_s* h,
    const char* key
) {
    usize index = h->hash_function(key) % h->capacity;

    kal_hashmap_kv_s* kv_ptr = (kal_hashmap_kv_s*)(
        ((char*)h->kvs) + (kal_hashmap_kv_stride(h) * index)
    );
    for (usize i = 0; i < h->capacity; ++i) {
        if (kv_ptr->key != NULL && strcmp(kv_ptr->key, key) == 0) {
            return kv_ptr->item;
        }

        // Linear probing
        index = (index + 1) % h->capacity;
        kv_ptr = (kal_hashmap_kv_s*)(
            ((char*)h->kvs) + (kal_hashmap_kv_stride(h) * index)
        );
    }

    return NULL;
}

KAL_INLINE
void
ensure_cap(
    kal_hashmap_s* h
) {
    usize new_cap = {};
    kal_hashmap_s temp_h = {};

    if (h->size < h->capacity) {
        return;
    }

    new_cap = h->capacity << 1;
    temp_h = (kal_hashmap_s) {
        .size = 0,
        .capacity = new_cap,
        .hash_function = h->hash_function,
        .element_size = h->element_size,
        .allocator = h->allocator,
        .kvs = h->allocator->alloc(
            (sizeof(kal_hashmap_kv_s) + sizeof(u8[h->element_size])) * new_cap
        ),
    };

    // Remap all elements
    for (usize i = 0; i < h->size; ++i) {
        // An even more voodoo shit.
        // The original kv of hashmap
        kal_hashmap_kv_s* kv_ptr = (kal_hashmap_kv_s*)(
            ((char*)h->kvs) + (kal_hashmap_kv_stride(h) * i)
        );

        if (kv_ptr->key != NULL) {
            kal_hashmap_add(
                &temp_h,
                kv_ptr->key,
                kv_ptr->item
            );
        }

    }

    kal_hashmap_deinit(h);
    *h = temp_h;
}
#endif
