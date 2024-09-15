#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

#define ALLOCATOR_H_IMPL
#include "memory/allocator.h"

#define DYN_ARRAY_H_IMPL
#include "container/dyn_array.h"

#define HASH_MAP_H_IMPL
#include "container/hash_map.h"

i32 main(void) {
    i32* arr = dyn_array_init(sizeof(i32), &default_allocator);
    dyn_array_append(arr, 1);
    dyn_array_append(arr, 2);
    dyn_array_append(arr, 3);
    dyn_array_append(arr, 4);
    dyn_array_append(arr, 5);
    dyn_array_append(arr, 6);
    dyn_array_append(arr, 7);
    dyn_array_append(arr, 8);
    dyn_array_append(arr, 9);
    dyn_array_append(arr, 0);

    for (usize i = 0; i < dyn_array_size(arr); ++i) {
        dyn_array_swap_remove_at(arr, i);
    }
    for (usize i = 0; i < dyn_array_size(arr); ++i) {
        printf("%d, ", arr[i]);
    }
    puts("");

    dyn_array_deinit(arr);

    return 0;
}
