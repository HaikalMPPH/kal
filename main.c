#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "allocator.h"

int main(void) {
    i32* ptr = default_allocator.alloc(sizeof(i32));

    default_allocator.dealloc(ptr);
}
