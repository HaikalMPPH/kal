#pragma once

#include "../defines.h"
#include "../types.h"
#include "../mem/allocator.h"

typedef struct KalDynArray {
    const KalAllocator allocator;
    usize elementSize,
          size,
          cap;
    void* items;
} KalDynArray;

KalDynArray 
kalDynArrayInit(
    usize elementSize,
    usize initCap,
    const KalAllocator allocator
);
void 
kalDynArrayDeinit(
    KalDynArray* d
);
void
kalDynArrayEnsureCap(
    KalDynArray* d
);
void 
kalDynArrayAdd(
    KalDynArray* d,
    void* element
);
void 
kalDynArraySwapRemove(
    KalDynArray* d,
    usize index
);
void 
kalDynArrayPop(
    KalDynArray* d
);



#ifdef KAL_DYNARRAY_IMPL
#include "../Mem/MemUtil.h"

KalDynArray 
kalDynArrayInit(
    usize elementSize,
    usize initcap,
    const KalAllocator allocator
) {
    return (KalDynArray) {
        .items = allocator.alloc(elementSize * initcap),
        .elementSize = elementSize,
        .size = 0,
        .cap = initcap,
        .allocator = allocator,
    };
}

void 
kalDynArrayDeinit(
    KalDynArray* d
) {
    d->allocator.dealloc(d->items);
    d->items = NULL;
}

void
kalDynArrayEnsureCap(
    KalDynArray* d
) {
    if (d->size >= d->cap) {
        void* temp;
        usize newCap;

        newCap = d->cap << 1;
        temp = d->allocator.alloc(d->size * newCap);
        kalByteCopy(
            temp,
            d->items,
            d->cap * d->elementSize
        );
        d->allocator.dealloc(d->items);
        d->items = temp;
        d->cap = newCap;
    }
}

void 
kalDynArrayAdd(
    KalDynArray* d,
    void* element
) {
    kalDynArrayEnsureCap(d);
    kalByteCopy(
        ((u8*)d->items) + d->elementSize * d->size,
        element,
        d->elementSize
    );
    ++d->size;
}

void 
kalDynArraySwapRemove(
    KalDynArray* d,
    usize index
) {
    kalByteCopy(
        ((u8*)d->items) + d->elementSize * index,
        ((u8*)d->items) + d->elementSize * (d->size - 1),
        d->elementSize
    );
    kalDynArrayPop(d);
}
void 
kalDynArrayPop(
    KalDynArray* d
) {
    --d->size;
}

#endif
