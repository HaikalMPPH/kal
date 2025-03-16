// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Name: kal_hashmap.h
// Desc: Open addressing hashmap/hashtable
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#pragma once

#include "../mem/allocator.h"
#include "../types.h"

typedef struct kal_hashmap_s kal_hashmap_s;
typedef struct kal_hashmap_kv_s kal_hashmap_kv_s;

struct kal_hashmap_kv_s {
    const char* key;
    u8 item[];
};

struct kal_hashmap_s {
    const kal_allocator_s allocator;
    usize size;
    usize cap;
    usize elements_size;

    // Example hash functions are available on the kal/math/hash.h file
    usize (*hash_fn)(const char*);
    kal_hashmap_kv_s* kvs;
};

kal_hashmap_s
kal_hashmap_init(
    usize elements_size,
    usize init_cap,
    usize (*hash_fn)(const char*),
    const kal_allocator_s allocator
);

void
kal_hashmap_deinit(
    kal_hashmap_s* h
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

#ifdef KAL_ADT_HASHMAP_IMPL
#include "../defines.h"
#include <string.h>

// Distance (in bytes) of each kv in the hashmap
// Basically sizeof(kv) + element_size
KAL_INLINE
usize
kv_stride(
    const kal_hashmap_s* h
);

//KAL_INLINE
//void
//ensure_cap(
//    kal_hashmap_s* h
//);

kal_hashmap_s
kal_hashmap_init(
    usize elements_size,
    usize init_cap,
    usize (*hash_fn)(const char*),
    const kal_allocator_s allocator
) {
    return (kal_hashmap_s) {
        .size = 0,
        .cap = init_cap,
        .elements_size = elements_size,
        .allocator = allocator,
        .hash_fn = hash_fn,

        // Look for "C flexible array member"
        .kvs = allocator.alloc(
            (sizeof(kal_hashmap_kv_s) + sizeof(u8[elements_size]))
            * init_cap
        ),
    };
}

void
kal_hashmap_remove_at(
    kal_hashmap_s* h,
    const char* key
) {
    kal_byte_set(
        kal_hashmap_get(h, key),
        0,
        h->elements_size
    );
    --h->size;
}

void
kal_hashmap_deinit(
    kal_hashmap_s* h
) {
    h->allocator.dealloc(h->kvs);
}

void
kal_hashmap_add(
    kal_hashmap_s* h,
    const char* key,
    void* val
) {
    // Ensure the cap of the hashmap
    if (h->size >= h->cap) {
        usize new_cap = {};
        //kal_hashmap_s temp = {};

        new_cap = h->cap << 1;
        kal_hashmap_s temp = (kal_hashmap_s) {
            .size = 0,
            .cap = new_cap,
            .hash_fn = h->hash_fn,
            .elements_size = h->elements_size,
            .allocator = h->allocator,
            .kvs = h->allocator.alloc(
                (sizeof(kal_hashmap_kv_s) + sizeof(u8[h->elements_size])) * new_cap
            ),
        };

        // Remap all elements
        for (usize i = 0; i < h->size; ++i) {
            // An even more voodoo shit.
            // The original kv of hashmap
            kal_hashmap_kv_s* kv_ptr = (kal_hashmap_kv_s*)(
                ((char*)h->kvs) + (kv_stride(h) * i)
            );

            if (kv_ptr->key != NULL) {
                kal_hashmap_add(
                    &temp,
                    kv_ptr->key,
                    kv_ptr->item
                );
            }
        }

        kal_hashmap_deinit(h);
        //*h = temp;
        kal_byte_copy(h, &temp, sizeof(temp));
    }

    //ensure_cap(h);
    usize index = {};
    index = h->hash_fn(key) % h->cap;

    // Some pointer voodoo.
    kal_hashmap_kv_s* kv_ptr = (kal_hashmap_kv_s*)(
        ((char*)h->kvs) + (kv_stride(h) * index)
    );

    for (usize i = 0; i < h->cap; ++i) {
        // if the byte/string that resides in this ptr is not null.
        // kal_std_allocator always initialized the memory to zero when allocating.
        if (kv_ptr->key != NULL && *kv_ptr->key != 0) {
            // Linear probing
            index = (index + 1) % h->cap;
            kv_ptr = (kal_hashmap_kv_s*)(
                ((char*)h->kvs) + (kv_stride(h) * index)
            );

            continue;
        }
        
        break;
    }
    kv_ptr->key = key;
    kal_byte_copy(
        kv_ptr->item,
        val,
        h->elements_size
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
    kal_byte_copy(
        kal_hashmap_get(h, key),
        val,
        h->elements_size
    );
}

void*
kal_hashmap_get(
    const kal_hashmap_s* h,
    const char* key
) {
    usize index = h->hash_fn(key) % h->cap;

    kal_hashmap_kv_s* kv_ptr = (kal_hashmap_kv_s*)(
        ((char*)h->kvs) + (kv_stride(h) * index)
    );
    for (usize i = 0; i < h->cap; ++i) {
        if (kv_ptr->key != NULL && strcmp(kv_ptr->key, key) == 0) {
            return kv_ptr->item;
        }

        // Linear probing
        index = (index + 1) % h->cap;
        kv_ptr = (kal_hashmap_kv_s*)(
            ((char*)h->kvs) + (kv_stride(h) * index)
        );
    }

    return NULL;
}

KAL_INLINE
usize
kv_stride(
    const kal_hashmap_s* h
) {
    return (sizeof(kal_hashmap_kv_s) + (h->elements_size));
}

//KAL_INLINE
//void
//ensure_cap(
//    kal_hashmap_s* h
//) {
//    usize new_cap = {};
//    kal_hashmap_s temp = {};
//
//    if (h->size < h->cap) {
//        return;
//    }
//
//    new_cap = h->cap << 1;
//    temp = (kal_hashmap_s) {
//        .size = 0,
//        .cap = new_cap,
//        .hash_fn = h->hash_fn,
//        .elements_size = h->elements_size,
//        .allocator = h->allocator,
//        .kvs = h->allocator.alloc(
//            (sizeof(kal_hashmap_kv_s) + sizeof(u8[h->elements_size])) * new_cap
//        ),
//    };
//
//    // Remap all elements
//    for (usize i = 0; i < h->size; ++i) {
//        // An even more voodoo shit.
//        // The original kv of hashmap
//        kal_hashmap_kv_s* kv_ptr = (kal_hashmap_kv_s*)(
//            ((char*)h->kvs) + (kv_stride(h) * i)
//        );
//
//        if (kv_ptr->key != NULL) {
//            kal_hashmap_add(
//                &temp,
//                kv_ptr->key,
//                kv_ptr->item
//            );
//        }
//
//    }
//
//    kal_hashmap_deinit(h);
//    *h = temp;
//}
#endif // KAL_ADT_HASHMAP_IMPL
