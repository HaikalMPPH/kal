#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

#define KAL_ALLOCATOR_H_IMPL
#include "memory/allocator.h"

#define KAL_DYNARRAY_H_IMPL
#include "container/dynarray.h"

#define HASH_MAP_H_IMPL
#include "container/hash_map.h"

#define KAL_RNG_H_IMPL
#include "rng/rng.h"

i32 main(void) {
    kal_rng_init();

    i32* arr = kal_dynarray_init(sizeof(i32), &kal_default_allocator);
    kal_dynarray_append(arr, 1);
    printf("size: %ld, capacity: %ld - %lu\n", kal_dynarray_size(arr), kal_dynarray_capacity(arr), sizeof(arr));
    kal_dynarray_append(arr, 2);
    kal_dynarray_append(arr, 3);
    kal_dynarray_append(arr, 4);
    kal_dynarray_append(arr, 5);
    kal_dynarray_append(arr, 6);
    kal_dynarray_append(arr, 7);
    kal_dynarray_append(arr, 8);
    kal_dynarray_append(arr, 9);
    kal_dynarray_append(arr, 0);
    printf("size: %ld, capacity: %ld - %lu\n", kal_dynarray_size(arr), kal_dynarray_capacity(arr), sizeof(arr));

    for (usize i = 0; i < kal_dynarray_size(arr); ++i) {
        kal_dynarray_swap_remove_at(arr, i);
    }
    for (usize i = 0; i < kal_dynarray_size(arr); ++i) {
        printf("%d, ", arr[i]);
    }
    puts("");
    printf("size: %ld, capacity: %ld - %lu\n", kal_dynarray_size(arr), kal_dynarray_capacity(arr), sizeof(arr));

    kal_dynarray_shrink_fit(arr);
    for (usize i = 0; i < kal_dynarray_size(arr); ++i) {
        printf("%d, ", arr[i]);
    }
    puts("");
    printf("size: %ld, capacity: %ld - %lu\n", kal_dynarray_size(arr), kal_dynarray_capacity(arr), sizeof(arr));

    kal_dynarray_deinit(arr);

    for (usize i = 0; i < 5; ++i) {
        if (kal_rng_chance(89.f))
            printf("SUCC\n");
        else 
            printf("ERRR\n");
    }

    return 0;
}
