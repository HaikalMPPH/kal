#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

#define ALLOCATOR_H_IMPL
#include "memory/allocator.h"

#define DYN_ARRAY_H_IMPL
#include "container/dyn_array.h"

int main(void) {
    i32* array = dyn_array_init(sizeof(i32), &default_allocator);
    printf("%lu\n", dyn_array_size(array));
    printf("%lu\n", dyn_array_capacity(array));

    dyn_array_append(array, 1);
    dyn_array_append(array, 2);
    dyn_array_append(array, 3);
    dyn_array_append(array, 4);
    dyn_array_append(array, 5);
    dyn_array_append(array, 6);
    dyn_array_append(array, 7);
    dyn_array_append(array, 8);

    dyn_array_append(array, 1);
    dyn_array_append(array, 2);
    dyn_array_append(array, 3);
    dyn_array_append(array, 4);
    dyn_array_append(array, 5);
    dyn_array_append(array, 6);
    dyn_array_append(array, 7);
    dyn_array_append(array, 8);

    dyn_array_append(array, 1);
    dyn_array_append(array, 2);
    dyn_array_append(array, 3);
    dyn_array_append(array, 4);
    dyn_array_append(array, 5);
    dyn_array_append(array, 6);
    dyn_array_append(array, 7);
    dyn_array_append(array, 8);

    dyn_array_append(array, 1);
    dyn_array_append(array, 2);
    dyn_array_append(array, 3);
    dyn_array_append(array, 4);
    dyn_array_append(array, 5);
    dyn_array_append(array, 6);
    dyn_array_append(array, 7);
    dyn_array_append(array, 8);
    for (usize i = 0; i < dyn_array_size(array); ++i) {
        printf("%d, ", array[i]);
    }
    puts("");

    printf("%lu\n", dyn_array_size(array));
    printf("%lu\n", dyn_array_capacity(array));


    dyn_array_deinit(array);
}
