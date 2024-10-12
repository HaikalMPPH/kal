#pragma once

#include <stdlib.h>
#include "../Types.h"
#include "../Memory/Allocator.h"

// optional for cleaner element access syntax.
#define KAL_DYNARRAY_AT(type, dynarray, index) ((type*)(dynarray.items))[(index)]

typedef struct KalDynArray KalDynArray;

struct KalDynArray {
    void* items;
    USize elementSize;
    USize size;
    USize capacity;
    const KalAllocator* allocator;
};

KalDynArray KalDynArrayInit(USize elementSize, const KalAllocator* allocator);
void KalDynArrayDeinit(KalDynArray* dynarray);
void KalDynArrayAdd(KalDynArray* dynarray, void* element);
void KalDynArrayResize(KalDynArray* dynarray, USize newCapacity);
void KalDynArrayPop(KalDynArray* dynarray);
void KalDynArrayClear(KalDynArray* dynarray);
void KalDynArraySwapRemoveAt(KalDynArray* dynarray, USize index);


#ifdef KAL_CONTAINER_DYNARRAY_IMPL
constexpr USize DYNARRAY_INIT_CAP = 4;

KalDynArray KalDynArrayInit(USize elementSize, const KalAllocator* allocator) {
    return (KalDynArray) {
        .items = allocator->alloc(elementSize * DYNARRAY_INIT_CAP),
        .elementSize = elementSize,
        .size = 0,
        .capacity = DYNARRAY_INIT_CAP,
        .allocator = allocator,
    };
}

void KalDynArrayDeinit(KalDynArray* dynarray) {
    dynarray->allocator->dealloc(dynarray->items);
}

void KalDynArrayAdd(KalDynArray* dynarray, void* element) {
    if (dynarray->size >= dynarray->capacity) {
        KalDynArrayResize(dynarray, dynarray->capacity << 1);
    }

    // copy Byte-per-byte data of element to items at index (size * elementSize)
    memcpy(
        (U8*)dynarray->items + (dynarray->size * dynarray->elementSize),
        element,
        dynarray->elementSize
    );

    ++dynarray->size;
}

void KalDynArrayResize(KalDynArray* dynarray, USize newCapacity) {
    void* newArray = dynarray->allocator->alloc(dynarray->elementSize * newCapacity);

    memcpy(newArray, dynarray->items, dynarray->size * dynarray->elementSize);

    dynarray->allocator->dealloc(dynarray->items);
    dynarray->items = newArray;
    dynarray->capacity = newCapacity;
}

void KalDynArrayPop(KalDynArray* dynarray) {}
void KalDynArrayClear(KalDynArray* dynarray) {}
void KalDynArraySwapRemoveAt(KalDynArray* dynarray, USize index) {}
#endif // KAL_CONTAINER_DYNARRAY_IMPL
