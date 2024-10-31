#pragma once

#include "../util/assert.h"
#include "../types.h"

#define MAT_MXN_AT(p_mat, r, c) (p_mat)->elements[(r) * (p_mat)->col + (c)]

// Matrix with the dimension of m cols x n rows
struct kal_mat_mxn {
    f64* elements;
    u64 row;
    u64 col;
    const struct kal_allocator* allocator;
};

struct kal_mat_mxn
kal_mat_mxn_init(
    u64 rows,
    u64 cols,
    const struct kal_allocator* allocator
);

void
kal_mat_mxn_deinit(struct kal_mat_mxn* matrix);

void
kal_mat_mxn_mul(
    struct kal_mat_mxn* dst,
    const struct kal_mat_mxn* m1,
    const struct kal_mat_mxn* m2
);

void
kal_mat_mxn_sum(
    struct kal_mat_mxn* dst,
    const struct kal_mat_mxn* m1,
    const struct kal_mat_mxn* m2
);

#ifdef KAL_MATH_LINALG_IMPL


struct kal_mat_mxn
kal_mat_mxn_init(
    u64 rows,
    u64 cols,
    const struct kal_allocator* allocator
) {
    return (struct kal_mat_mxn) {
        .row = rows,
        .col = cols,
        .allocator = allocator,
        .elements = allocator->alloc(sizeof(f64) * rows * cols),
    };
}

void
kal_mat_mxn_deinit(struct kal_mat_mxn* matrix) {
    matrix->allocator->dealloc(matrix->elements);
}

void
kal_mat_mxn_mul(
    struct kal_mat_mxn* dst,
    const struct kal_mat_mxn* m1,
    const struct kal_mat_mxn* m2
) {
    KAL_ASSERT(m1->col == m2->row);
    KAL_ASSERT(dst->col == m1->col);
    KAL_ASSERT(dst->row == m2->row);
}

void
kal_mat_mxn_sum(
    struct kal_mat_mxn* dst,
    const struct kal_mat_mxn* m1,
    const struct kal_mat_mxn* m2
) {
    KAL_ASSERT(m1->row == m2->row);
    KAL_ASSERT(m1->col == m2->col);
}


#endif
