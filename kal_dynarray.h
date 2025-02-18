#pragma once

#include "kal_defines.h"
#include "kal_types.h"
#include "kal_allocator.h"

typedef struct kal_dynarray_s {
    void* items;
    usize element_size,
          size,
          capacity;
    const kal_allocator_s* allocator;
} kal_dynarray_s;

kal_dynarray_s 
kal_dynarray_init(
    usize element_size,
    usize init_capacity,
    const kal_allocator_s* allocator
);
void 
kal_dynarray_deinit(
    kal_dynarray_s* d
);
void
kal_dynarray_ensure_cap(
    kal_dynarray_s* d
);
void 
kal_dynarray_add(
    kal_dynarray_s* d,
    void* element
);
void 
kal_dynarray_swap_remove(
    kal_dynarray_s* d,
    usize index
);
void 
kal_dynarray_pop(
    kal_dynarray_s* d
);
void 
kal_dynarray_remove_at(
    kal_dynarray_s* d,
    usize index
);



#ifdef KAL_DYNARRAY_IMPL
#include <string.h>

kal_dynarray_s 
kal_dynarray_init(
    usize element_size,
    usize init_capacity,
    const kal_allocator_s* allocator
) {
    return (kal_dynarray_s) {
        .items = allocator->alloc(element_size * init_capacity),
        .element_size = element_size,
        .size = 0,
        .capacity = init_capacity,
        .allocator = allocator,
    };
}

void 
kal_dynarray_deinit(
    kal_dynarray_s* d
) {
    d->allocator->dealloc(d->items);
    d->items = NULL;
    d->allocator = NULL;
}

void
kal_dynarray_ensure_cap(
    kal_dynarray_s* d
) {
    if (d->size >= d->capacity) {
        void* temp;
        usize new_cap;

        new_cap = d->capacity << 1;
        temp = d->allocator->alloc(d->size * new_cap);
        memcpy(
            temp,
            d->items,
            d->capacity * d->element_size
        );
        d->allocator->dealloc(d->items);
        d->items = temp;
        d->capacity = new_cap;
    }
}

void 
kal_dynarray_add(
    kal_dynarray_s* d,
    void* element
) {
    kal_dynarray_ensure_cap(d);
    memcpy(
        ((u8*)d->items) + d->element_size * d->size,
        element,
        d->element_size
    );
    ++d->size;
}

void 
kal_dynarray_swap_remove(
    kal_dynarray_s* d,
    usize index
) {
    memcpy(
        ((u8*)d->items) + d->element_size * index,
        ((u8*)d->items) + d->element_size * (d->size - 1),
        d->element_size
    );
    kal_dynarray_pop(d);
}
void 
kal_dynarray_pop(
    kal_dynarray_s* d
) {
    --d->size;
}

#endif
