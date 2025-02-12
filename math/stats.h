#pragma once

#include "../types.h"

f64 kal_mean(usize n_elements, f64 elements[]);
f64 kal_median(usize n_elements, f64 elements[]);
f64 kal_quantile(usize n_elements, f64 elements[], f64 percentage);
f64 kal_data_range(usize n_elements, f64 elements[]);
f64 kal_deviation(usize n_elements, f64 elements[]);
f64 kal_sample_variance(usize n_elements, f64 elements[], bool is_sample);
f64 kal_standard_deviation(usize n_elements, f64 elements[], bool is_sample);
f64 kal_interquartile_range(usize n_elements, f64 elements[]);
f64 kal_covariance(usize n_elements, f64 el1[], f64 el2[]);

#ifdef KAL_MATH_STATS_IMPL
#include "../memory/allocator.h"
#include <limits.h>
#include <stdlib.h>

static
i32
f64_elem_compare(const void* rhs, const void* lhs) {
    if (*(f64*)rhs < *(f64*)lhs) {
        return -1;
    }
    return 1;
}

static
f64
median_even(usize n_elements, f64 elements[]) {
    usize mid = (usize)((f64)n_elements / 2.);
    return (elements[mid - 1] + elements[mid]) / 2;
}

static
f64
median_odd(usize n_elements, f64 elements[]) {
    return elements[(usize)((f64)n_elements/2.)];
}

f64
kal_mean(usize n_elements, f64 elements[]) {
    f64 sum = 0.;

    for (usize i = 0; i < n_elements; ++i) {
        sum += elements[i];
    }
    return sum / (f64)n_elements;
}

f64
kal_median(usize n_elements, f64 elements[]) {
    f64 res = 0.;
    f64* elem = KAL_ALLOC(sizeof(f64) * n_elements);
    memcpy(elem, elements, sizeof(f64) * n_elements);

    qsort(elem, n_elements, sizeof(f64), f64_elem_compare);

    res = (n_elements % 2 == 0)
        ? median_even(n_elements, elem)
        : median_odd(n_elements, elem);

    KAL_DEALLOC(elem);
    return res;
}

f64
kal_quantile(usize n_elements, f64 elements[], f64 percentage) {
    KAL_ASSERT(1.0 >= percentage);

    f64 res = 0;
    usize index = (usize)((f64)(n_elements-1) * percentage);
    f64* elem = KAL_ALLOC(sizeof(f64) * n_elements);
    
    memcpy(elem, elements, sizeof(f64) * n_elements);
    qsort(elem, n_elements, sizeof(f64), f64_elem_compare);
    res = elem[index];

    KAL_DEALLOC(elem);

    return res;
}

f64
kal_data_range(usize n_elements, f64 elements[]) {
    f64 min = (f64)ULONG_MAX;
    f64 max = -(f64)ULONG_MAX;

    for (usize i = 0; i < n_elements; ++i) {
        if (min > elements[i]) {
            min = elements[i];
        }
        else if (max < elements[i]) {
            max = elements[i];
        }
    }
    //printf("max: %f, min: %f\n", max, min);

    return max - min;
}

f64
kal_deviation(usize n_elements, f64 elements[]) {
    f64 deviation = 0;
    f64 mean = kal_mean(n_elements, elements);
    for (usize i = 0; i < n_elements; ++i) {
        deviation += (elements[i] - mean) * (elements[i] - mean);
    }

    return deviation;
}

f64
kal_sample_variance(usize n_elements, f64 elements[], bool is_sample) {
    if (is_sample) {
        return kal_deviation(n_elements, elements) / (n_elements - 1);
    }
    else {
        return kal_deviation(n_elements, elements) / (n_elements);
    }
}

f64
kal_standard_deviation(usize n_elements, f64 elements[], bool is_sample) {
    return sqrt(kal_sample_variance(n_elements, elements, is_sample));
}

f64
kal_interquartile_range(usize n_elements, f64 elements[]) {
    return 
        kal_quantile(n_elements, elements, 0.75) -
        kal_quantile(n_elements, elements, 0.25);
}

f64
kal_covariance(usize n_elements, f64 el1, f64 el2) {
    f64 dot = 0.;
    for (usize i = 0) // TODO

    return 0.;
}

#endif
