#pragma once

#include "../Types.h"
#include "../Memory/Allocator.h"

typedef struct KalHashMapHeader {
    USize capacity;
    USize size;
    const KalAllocator* allocator;
} KalHashMapHeader;

#define KAL_HASHMAP_HEADER(map) ((KalHashMapHeader*)(map) - 1)

void* KalHashMapInit(USize typeSize, const KalAllocator* allocator);
void* KalHashMapInitWithSize(USize initialCap, USize typeSize, const KalAllocator* allocator);
void KalHashMapDeinit(void* map);
