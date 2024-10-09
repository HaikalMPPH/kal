#pragma once

#include <string.h>
#include "../types.h"

#include "../memory/allocator.h"


typedef struct kal_dynarray_header_s kal_dynarray_header_s;
struct kal_dynarray_header_s {
    usize capacity;
    usize size;
    const kal_allocator_s* allocator;
};

// get the header of the array
#define kal_dynarray_header(a) ((kal_dynarray_header_s*)(a) - 1)

#define kal_dynarray_append(arr, val)\
do {\
    (arr) = kal_dynarray_ensure_capacity((arr), sizeof((val)));\
    (arr)[kal_dynarray_header((arr))->size++] = (val);\
} while (0)

// remove and swap the element at index i with the last element.
#define kal_dynarray_swap_remove_at(arr, index)\
do {\
    if (index == kal_dynarray_size((arr)) - 1) {\
        kal_dynarray_pop((arr));\
    }\
    else {\
        (arr)[index] = (arr)[kal_dynarray_size((arr)) - 1];\
        kal_dynarray_pop((arr));\
    }\
} while (0)

#define kal_dynarray_size(arr) kal_dynarray_header((arr))->size
#define kal_dynarray_capacity(arr) kal_dynarray_header((arr))->capacity

#define kal_dynarray_shrink_fit(array)\
do {\
    kal_dynarray_header_s* header = kal_dynarray_header((array));\
    void* new_arr = kal_dynarray_init_with_size(header->size, sizeof(*(array)), header->allocator);\
    memcpy(new_arr, (array), sizeof(*(array)) * kal_dynarray_header(new_arr)->capacity);\
    kal_dynarray_header(new_arr)->size = header->size;\
    kal_dynarray_deinit(array);\
    array = new_arr;\
} while (0)

void* kal_dynarray_init(usize type_size, const kal_allocator_s* allocator);
void* kal_dynarray_init_with_size(usize initial_cap, usize type_size, const kal_allocator_s* allocator);
void  kal_dynarray_deinit(void* array);
void* kal_dynarray_ensure_capacity(void* array, usize value_size);
void  kal_dynarray_pop(void* array);
void  kal_dynarray_clear(void* array);
bool  kal_dynarray_is_empty(void* array);




#ifdef KAL_CONTAINER_DYNARRAY_H_IMPL
enum { 
    DYN_ARRAY_ALLOC_STEP = 4
};

// init dynarray with initial capacity for the header
void* 
kal_dynarray_init_with_size(usize initial_cap, usize type_size, const kal_allocator_s* allocator) {
    usize alloc_size = sizeof(kal_dynarray_header_s) + initial_cap * type_size;
    kal_dynarray_header_s* ptr = allocator->alloc(alloc_size);

    if (ptr) {
        ptr->capacity  = initial_cap;
        ptr->size      = 0;
        ptr->allocator = allocator;

        ptr += 1;
    }

    return (void*)ptr;
}

// initialize dynarray with the default alloc step
void*
kal_dynarray_init(usize type_size, const kal_allocator_s* allocator) {
    return kal_dynarray_init_with_size(DYN_ARRAY_ALLOC_STEP, type_size, allocator);
}

void 
kal_dynarray_deinit(void* array) {
    kal_dynarray_header_s* header = kal_dynarray_header(array);
    header->allocator->dealloc(header);
}

void*
kal_dynarray_ensure_capacity(void* array, usize value_size) {
    if (
        kal_dynarray_header(array)->size >= kal_dynarray_header(array)->capacity - 1
    ) {
        usize new_size = 
            sizeof(kal_dynarray_header_s) 
            + value_size 
            * ((kal_dynarray_header(array)->capacity + DYN_ARRAY_ALLOC_STEP));
        kal_dynarray_header_s* new_header = 
            kal_dynarray_header(array)->allocator->alloc(new_size);

        if (new_header) {
            new_header->capacity = kal_dynarray_capacity(array) << 1;
            new_header->allocator = kal_dynarray_header(array)->allocator;
            new_header->size = kal_dynarray_size(array);

            // set the pointer to the next address available for the array elements.
            new_header += 1;
        }

        void* newArray = new_header;
        memcpy(newArray, array, (kal_dynarray_size(array)) * value_size);
        kal_dynarray_deinit(array);

        array = newArray;

        return array;
    }

    return array;
}

void
kal_dynarray_pop(void* array) {
    kal_dynarray_header(array)->size--;
}

void
kal_dynarray_clear(void* array) {
    kal_dynarray_header(array)->size = 0;
}

bool
kal_dynarray_is_empty(void* array) {
    return kal_dynarray_header(array)->size <= 0;
}
#endif // KAL_CONTAINER_DYNARRAY_H_IMPL
