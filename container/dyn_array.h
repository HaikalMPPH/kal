#ifndef KAL_DYN_ARRAY_H
#define KAL_DYN_ARRAY_H

#include <string.h>
#include "../types.h"
#include "../memory/allocator.h"


enum { 
    DYN_ARRAY_ALLOC_STEP = 8
};
typedef struct Dyn_Array_Header Dyn_Array_Header;


#define dyn_array_header(a) ((Dyn_Array_Header*)(a) - 1)

#define dyn_array_append(array, val)\
do {\
    (array) = dyn_array_ensure_capacity((array), sizeof((val)));\
    (array)[dyn_array_header(array)->size++] = val;\
} while (0)

#define dyn_array_swap_remove_at(arr, index)\
do {\
    if (index == dyn_array_size(array)) {\
        dyn_array_pop(array);\
    }\
    else {\
        array[index] = array[dyn_array_size(array) - 1];\
        dyn_array_pop(array);\
    }\
} while (0)

void* dyn_array_init(usize type_size, const Allocator* allocator);
usize dyn_array_capacity(void* array);
usize dyn_array_size(void* array);
void  dyn_array_deinit(void* array);
void* dyn_array_ensure_capacity(void* array, usize value_size);
void  dyn_array_pop(void* array);




#ifdef DYN_ARRAY_H_IMPL
struct Dyn_Array_Header {
    usize            capacity;
    usize            size;
    const Allocator* allocator;
};

void*
dyn_array_init(usize type_size, const Allocator* allocator) {
    usize             alloc_size = sizeof(Dyn_Array_Header) + DYN_ARRAY_ALLOC_STEP * type_size;
    Dyn_Array_Header* ptr        = allocator->alloc(alloc_size);

    if (ptr) {
        ptr->capacity  = DYN_ARRAY_ALLOC_STEP;
        ptr->size      = 0;
        ptr->allocator = allocator;

        ptr += 1;
    }

    return (void*)ptr;
}

usize
dyn_array_size(void* array) {
    return dyn_array_header(array)->size;
}

usize
dyn_array_capacity(void* array) {
    return dyn_array_header(array)->capacity;
}

void 
dyn_array_deinit(void* array) {
    Dyn_Array_Header* header = dyn_array_header(array);
    header->allocator->dealloc(header);
}

void*
dyn_array_ensure_capacity(void* array, usize value_size) {
    if (dyn_array_header(array)->size >= dyn_array_header(array)->capacity - 1) {
        usize             new_size   = sizeof(Dyn_Array_Header) + value_size * ((dyn_array_header(array)->capacity + DYN_ARRAY_ALLOC_STEP));
        Dyn_Array_Header* new_header = dyn_array_header(array)->allocator->alloc(new_size);

        if (new_header) {
            new_header->capacity  = dyn_array_capacity(array) + DYN_ARRAY_ALLOC_STEP;
            new_header->allocator = dyn_array_header(array)->allocator;
            new_header->size      = dyn_array_size(array);
            new_header += 1;
        }

        void* new_array = new_header;
        memcpy(new_array, array, (dyn_array_size(array)) * value_size);
        dyn_array_deinit(array);

        array = new_array;

        return array;
    }

    return array;
}

void
dyn_array_pop(void* array) {
    dyn_array_header(array)->size--;
}

#endif // DYN_ARRAY_H_IMPL

#endif // KAL_DYN_ARRAY_H
