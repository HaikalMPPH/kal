#pragma once

#include <time.h>
#include <stdlib.h>
#include "../types.h"

void kal_rng_init();
bool kal_rng_chance(f32 percentage);
f32 kal_rng_random_range_f32(f32 min, f32 max); // TODO

#ifdef KAL_RNG_H_IMPL

void
kal_rng_init() {
    srand(time(nullptr));
}

bool
kal_rng_chance(f32 percentage) {
    if (percentage > rand() / (RAND_MAX / 100.f)) 
        return true;
    return false;
}

#endif // KAL_RNG_H_IMPL
