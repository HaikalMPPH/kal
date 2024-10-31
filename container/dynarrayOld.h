#pragma once

#include <string.h>
#include "../Logger.h"
#include "../Types.h"
#include "../Memory/Allocator.h"


typedef struct KalDynArrayHeader KalDynArrayHeader;
struct KalDynArrayHeader {
    USize capacity;
    USize size;
    const KalAllocator* allocator;
};

// get the header of the array
#define KAL_DYNARRAY_HEADER(a) ((KalDynArrayHeader*)(a) - 1)

#define KalDynArrayAppend(arr, val)\
do {\
    (arr) = KalDynArrayEnsureCapacity((arr), sizeof((val)));\
    (arr)[KAL_DYNARRAY_HEADER((arr))->size++] = (val);\
} while (0)

// remove and swap the element at index i with the last element.
#define KalDynArraySwapRemoveAt(arr, index)\
do {\
    if (index == KalDynArraySize((arr)) - 1) {\
        KalDynArrayPop((arr));\
    }\
    else {\
        (arr)[index] = (arr)[KalDynArraySize((arr)) - 1];\
        KalDynArrayPop((arr));\
    }\
} while (0)

#define KalDynArraySize(arr) KAL_DYNARRAY_HEADER((arr))->size
#define KalDynArrayCapacity(arr) KAL_DYNARRAY_HEADER((arr))->capacity

#define KalDynArrayShrinkFit(array)\
do {\
    KalDynArrayHeader* header = KAL_DYNARRAY_HEADER((array));\
    void* new_arr = KalDynArrayInitWithSize(header->size, sizeof(*(array)), header->allocator);\
    memcpy(new_arr, (array), sizeof(*(array)) * KAL_DYNARRAY_HEADER(new_arr)->capacity);\
    KAL_DYNARRAY_HEADER(new_arr)->size = header->size;\
    KalDynArrayDeinit(array);\
    array = new_arr;\
} while (0)

void* KalDynArrayInit(USize typeSize, const KalAllocator* allocator);
void* KalDynArrayInitWithSize(USize initialCap, USize typeSize, const KalAllocator* allocator);
void  KalDynArrayDeinit(void* array);
void* KalDynArrayEnsureCapacity(void* array, USize valueSize);
void  KalDynArrayPop(void* array);
void  KalDynArrayClear(void* array);
bool  KalDynArrayIsEmpty(void* array);




#ifdef KAL_CONTAINER_DYNARRAY_IMPL
enum { 
    DYNARRAY_INIT_CAP = 4
};

// init dynarray with initial capacity for the header
void* 
KalDynArrayInitWithSize(USize initialCap, USize typeSize, const KalAllocator* allocator) {
    USize alloc_size = sizeof(KalDynArrayHeader) + initialCap * typeSize;
    KalDynArrayHeader* ptr = allocator->alloc(alloc_size);

    if (ptr) {
        ptr->capacity  = initialCap;
        ptr->size      = 0;
        ptr->allocator = allocator;

        ptr += 1;
    }

    return (void*)ptr;
}

// initialize dynarray with the default alloc step
void*
KalDynArrayInit(USize typeSize, const KalAllocator* allocator) {
    return KalDynArrayInitWithSize(DYNARRAY_INIT_CAP, typeSize, allocator);
}

void 
KalDynArrayDeinit(void* array) {
    KalDynArrayHeader* header = KAL_DYNARRAY_HEADER(array);
    header->allocator->dealloc(&header);
}

void*
KalDynArrayEnsureCapacity(void* array, USize valueSize) {
    KalDynArrayHeader* header = KAL_DYNARRAY_HEADER(array);
    USize newCap = header->capacity << 1;
    if (
        //header->size >= header->capacity - 1
        header->size >= header->capacity
    ) {
        USize newSize = 
            sizeof(KalDynArrayHeader) 
            + valueSize 
            * newCap;
        KalDynArrayHeader* newHeader = 
            header->allocator->alloc(newSize);

        if (newHeader) {
            newHeader->capacity = newCap;
            newHeader->allocator = header->allocator;
            newHeader->size = KalDynArraySize(array);

            // set the pointer to the next address available for the array elements.
            newHeader += 1;
        }
        else {
            DEBUG_LOG_MSG(ERROR, "unable to allocated memory!!");
        }

        void* newArray = newHeader;
        //memcpy(newArray, array, (KalDynArraySize(array)) * valueSize);
        memcpy(newArray, array, (KalDynArraySize(array)) * valueSize);
        KalDynArrayDeinit(array);

        array = newArray;

        return array;
    }

    return array;
}

void
KalDynArrayPop(void* array) {
    KAL_DYNARRAY_HEADER(array)->size--;
}

void
KalDynArrayClear(void* array) {
    KAL_DYNARRAY_HEADER(array)->size = 0;
}

bool
KalDynArrayIsEmpty(void* array) {
    return KAL_DYNARRAY_HEADER(array)->size <= 0;
}
#endif // KAL_CONTAINER_DYNARRAY_IMPL
