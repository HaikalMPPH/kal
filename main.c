#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

#define KAL_ALLOCATOR_IMPL
#include "allocator.h"

int main(void) {
    i32*  ptr = default_allocator.alloc(sizeof(i32));

    default_allocator.dealloc(ptr);
}
