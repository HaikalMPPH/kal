#ifndef KAL_ADT_DYNARRAY_HH
#define KAL_ADT_DYNARRAY_HH

#include "../defines.h"
#include "../types.h"
#include "../mem/allocator.h"

typedef struct kal_dynarray_header_s {
    usize element_size;
    usize size;
    usize cap;
    kal_allocator_s allocator;
} kal_dynarray_header_s;

void*
kal_dynarray_init(
    usize element_size,
    usize init_cap,
    kal_allocator_s allocator
);

void
kal_dynarray_deinit(void* arr);

void
kal_dynarray_add(
    void* arr,
    void* item
);

void
kal_dynarray_swap_remove(
    void* arr,
    usize index
);

usize
kal_dynarray_size(void* arr);

usize
kal_dynarray_cap(void* arr);

#ifdef KAL_ADT_DYNARRAY_IMPL

#include <assert.h>
#include "../mem/memutil.h"

static KAL_INLINE
struct kal_dynarray_header_s*
get_header(void* arr);

void*
kal_dynarray_init(
    usize element_size,
    usize init_cap,
    struct kal_allocator_s allocator
) {
    struct kal_dynarray_header_s* head = allocator.alloc(
        sizeof(kal_dynarray_header_s) + element_size * init_cap
    );
    head->element_size = element_size;
    head->cap = init_cap;
    head->allocator = allocator;

    void* arr = head + 1;
    return arr;
}

void
kal_dynarray_deinit(void* arr) {
    kal_dynarray_header_s* head = get_header(arr);
    kal_allocator_s allocator = head->allocator;
    allocator.dealloc(head);
}

void
kal_dynarray_add(
    void* arr,
    void* item
) {
    struct kal_dynarray_header_s* head = get_header(arr);
    char* byte_arr = arr;

    if (head->size >= head->cap) {
        usize new_cap = head->cap << 1;
        usize old_head_size = sizeof(kal_dynarray_header_s) + head->element_size * new_cap;
        kal_dynarray_header_s* new_head = head->allocator.alloc(
            old_head_size
        );

        kal_byte_copy(
            new_head,
            head,
            old_head_size
        );

        new_head->allocator.dealloc(head);
        head = new_head;
    }

    kal_byte_copy(
        byte_arr + (head->size * head->element_size),
        item,
        head->element_size
    );
    head->size += 1;
}

void
kal_dynarray_swap_remove(
    void* arr,
    usize index
) {
    kal_dynarray_header_s* head = get_header(arr);
    char* byte_arr = arr;

    assert(head->size > 0);

    if (index == head->size) {
        head->size -= 1;
        return;
    }

    // Swop the element at index 'index' with the last one.
    kal_byte_copy(
        byte_arr + index * head->element_size,
        byte_arr + (head->size - 1) * head->element_size,
        head->element_size
    );
    head->size -= 1;
}

usize
kal_dynarray_size(void* arr) {
    return get_header(arr)->size;
}

usize
kal_dynarray_cap(void* arr) {
    return get_header(arr)->cap;
}

static KAL_INLINE
kal_dynarray_header_s*
get_header(void* arr) {
    return (kal_dynarray_header_s*)arr - 1;
}

#endif // KAL_ADT_DYNARRAY_IMPL

#endif // KAL_ADT_DYNARRAY_HH
