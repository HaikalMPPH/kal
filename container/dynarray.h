#pragma once

#include <string.h>
#include "../types.h"

#define KAL_ALLOCATOR_H_IMPL
#include "../memory/allocator.h"


typedef struct kal_dynarray_header_s kal_dynarray_header_s;
struct kal_dynarray_header_s {
    usize            capacity;
    usize            size;
    const kal_allocator_s* allocator;
};



#define kal_dynarray_header_s(a) ((kal_dynarray_header_s*)(a) - 1)

#define kal_dynarray_append(arr, val)\
do {\
    (arr) = kal_dynarray_ensure_capacity((arr), sizeof((val)));\
    (arr)[kal_dynarray_header_s((arr))->size++] = (val);\
} while (0)

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

#define kal_dynarray_size(arr) kal_dynarray_header_s((arr))->size
#define kal_dynarray_capacity(arr) kal_dynarray_header_s((arr))->capacity

#define kal_dynarray_shrink_fit(array)\
do {\
    kal_dynarray_header_s* header = kal_dynarray_header_s((array));\
    void* new_arr = kal_dynarray_init_with_size(header->size, sizeof(*(array)), header->allocator);\
    memcpy(new_arr, (array), sizeof(*(array)) * kal_dynarray_header_s(new_arr)->capacity);\
    kal_dynarray_header_s(new_arr)->size = header->size;\
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




#ifdef KAL_DYNARRAY_H_IMPL
enum { 
    DYN_ARRAY_ALLOC_STEP = 4
};

void* 
kal_dynarray_init_with_size(usize initial_cap, usize type_size, const kal_allocator_s* allocator) {
    usize             alloc_size = sizeof(kal_dynarray_header_s) + initial_cap * type_size;
    kal_dynarray_header_s* ptr        = allocator->alloc(alloc_size);

    if (ptr) {
        ptr->capacity  = initial_cap;
        ptr->size      = 0;
        ptr->allocator = allocator;

        ptr += 1;
    }

    return (void*)ptr;
}
void*
kal_dynarray_init(usize type_size, const kal_allocator_s* allocator) {
    return kal_dynarray_init_with_size(DYN_ARRAY_ALLOC_STEP, type_size, allocator);
}

void 
kal_dynarray_deinit(void* array) {
    kal_dynarray_header_s* header = kal_dynarray_header_s(array);
    header->allocator->dealloc(header);
}

void*
kal_dynarray_ensure_capacity(void* array, usize value_size) {
    if (kal_dynarray_header_s(array)->size >= kal_dynarray_header_s(array)->capacity - 1) {
        usize           new_size   = sizeof(kal_dynarray_header_s) + value_size * ((kal_dynarray_header_s(array)->capacity + DYN_ARRAY_ALLOC_STEP));
        kal_dynarray_header_s* new_header = kal_dynarray_header_s(array)->allocator->alloc(new_size);

        if (new_header) {
            //new_header->capacity  = kal_dynarray_capacity(array) + DYN_ARRAY_ALLOC_STEP;
            new_header->capacity  = kal_dynarray_capacity(array) << 1;
            new_header->allocator = kal_dynarray_header_s(array)->allocator;
            new_header->size      = kal_dynarray_size(array);
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
    kal_dynarray_header_s(array)->size--;
}

void
kal_dynarray_clear(void* array) {
    kal_dynarray_header_s(array)->size = 0;
}

bool
kal_dynarray_is_empty(void* array) {
    return kal_dynarray_header_s(array)->size <= 0;
}
#endif // KAL_DYNARRAY_H_IMPL
