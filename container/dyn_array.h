#pragma once

#include <assert.h>
#include <stdlib.h>
#include "../types.h"
#include "../memory/allocator.h"

// optional for cleaner element access syntax.
#define DYNARRAY_AT(type, dynarray, index) ((type*)(dynarray.items))[(index)]

typedef struct dynarray_s dynarray;

struct dynarray_s {
    void* items;
    usize element_size;
    usize size;
    usize capacity;
    const allocator_s* allocator;
};

dynarray_s dynarray_init(usize element_size, const allocator_s* allocator);
void dynarray_deinit(dynarray_s* dynarray);
void dynarray_add(dynarray_s* dynarray, void* element);
void dynarray_resize(dynarray_s* dynarray, usize new_capacity);
void dynarray_pop(dynarray_s* dynarray);
void dynarray_clear(dynarray_s* dynarray);
void dynarray_swap_remove_at(dynarray_s* dynarray, usize index);





#ifdef KAL_CONTAINER_DYNARRAY_IMPL
constexpr usize DYNARRAY_INIT_CAP = 4;

dynarray_s dynarray_init(usize element_size, const allocator_s* allocator) {
    return (dynarray) {
        .items = allocator->alloc(element_size * DYNARRAY_INIT_CAP),
        .element_size = element_size,
        .size = 0,
        .capacity = DYNARRAY_INIT_CAP,
        .allocator = allocator,
    };
}

void dynarray_deinit(dynarray_s* dynarray) {
    dynarray->allocator->dealloc(dynarray->items);
}

void dynarray_add(dynarray_s* dynarray, void* element) {
    if (dynarray->size >= dynarray->capacity) {
        dynarray_resize(dynarray, dynarray->capacity << 1);
    }

    // copy Byte-per-byte data of element to items at index (size * element_size)
    memcpy(
        (U8*)dynarray->items + (dynarray->size * dynarray->element_size),
        element,
        dynarray->element_size
    );

    ++dynarray->size;
}

void dynarray_resize(dynarray_s* dynarray, usize new_capacity) {
    void* new_array = 
        dynarray->allocator->alloc(dynarray->element_size * new_capacity);

    memcpy(new_array, dynarray->items, dynarray->size * dynarray->element_size);

    dynarray->allocator->dealloc(dynarray->items);
    dynarray->items = new_array;
    dynarray->capacity = new_capacity;
}

void dynarray_pop(dynarray_s* dynarray) {
    --dynarray->size;
}

void dynarray_clear(dynarray_s* dynarray) {
    dynarray->size = 0;
}

void dynarray_swap_remove_at(dynarray_s* dynarray, usize index) {
    assert(index < dynarray->size - 1);
    memcpy(
        (U8*)dynarray->items + (index * dynarray->element_size),
        (U8*)dynarray->items + ((dynarray->size - 1)  * dynarray->element_size),
        dynarray->element_size
    );
    --dynarray->size;
}
#endif // KAL_CONTAINER_DYNARRAY_IMPL
