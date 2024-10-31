#pragma once

#include <stdlib.h>

#include "../util/assert.h"
#include "../memory/allocator.h"
#include "../types.h"

// optional for cleaner element access syntax.
#define DYNARRAY_AT(type, dynarray, index) ((type*)(dynarray.items))[(index)]

//typedef struct struct kal_dynarray KalDynArray;

struct kal_dynarray {
    void* items;
    usize element_size;
    usize size;
    usize capacity;
};

struct kal_dynarray 
kal_dynarray_init(usize element_size);

void
kal_dynarray_deinit(struct kal_dynarray* dynarray);

void
kal_dynarray_push(
    struct kal_dynarray* dynarray,
    void* element
);

void
kal_dynarray_resize(
    struct kal_dynarray* dynarray,
    usize new_capacity
);

void
kal_dynarray_pop(struct kal_dynarray* dynarray);

void
kal_dynarray_clear(struct kal_dynarray* dynarray);

void
kal_dynarray_swap_remove_at(
    struct kal_dynarray* dynarray,
    usize index
);





#ifdef KAL_CONTAINER_DYNARRAY_IMPL
constexpr usize DYNARRAY_INIT_CAP = 4;

struct kal_dynarray 
kal_dynarray_init(usize element_size) {
    return (struct kal_dynarray) {
        .items       = KAL_ALLOC(element_size * DYNARRAY_INIT_CAP),
        .element_size = element_size,
        .size        = 0,
        .capacity    = DYNARRAY_INIT_CAP,
    };
}

void kal_dynarray_deinit(struct kal_dynarray* dynarray) {
    KAL_DEALLOC(dynarray->items);
}

void kal_dynarray_push(struct kal_dynarray* dynarray, void* element) {
    if (dynarray->size >= dynarray->capacity) {
        kal_dynarray_resize(dynarray, dynarray->capacity << 1);
    }

    // copy Byte-per-byte data of element to items at index (size * element_size)
    memcpy((u8*)dynarray->items + (dynarray->size * dynarray->element_size),
           element,
           dynarray->element_size);

    ++dynarray->size;
}

void kal_dynarray_resize(struct kal_dynarray* dynarray, usize new_capacity) {
    void* new_arr = 
        KAL_ALLOC(dynarray->element_size * new_capacity);

    memcpy(new_arr, dynarray->items, dynarray->size * dynarray->element_size);

    KAL_DEALLOC(dynarray->items);
    dynarray->items = new_arr;
    dynarray->capacity = new_capacity;
}

void kal_dynarray_pop(struct kal_dynarray* dynarray) {
    --dynarray->size;
}

void kal_dynarray_clear(struct kal_dynarray* dynarray) {
    dynarray->size = 0;
}

void kal_dynarray_swap_remove_at(struct kal_dynarray* dynarray, usize index) {
    KAL_ASSERT(index < dynarray->size);
    memcpy((u8*)dynarray->items + (index * dynarray->element_size),
           (u8*)dynarray->items + ((dynarray->size - 1)  * dynarray->element_size),
           dynarray->element_size);
    --dynarray->size;
}
#endif // KAL_CONTAINER_DYNARRAY_IMPL
