#pragma once

#include <time.h>
#include <stdlib.h>
#include "../types.h"

void KalRngInit();
bool KalRngChance(F32 percentage);
F32 KalRngRandomRangeF32(F32 min, F32 max); // TODO

#ifdef KAL_RNG_IMPL

void
KalRngInit() {
    srand(time(nullptr));
}

bool
KalRngChance(F32 percentage) {
    if (percentage > rand() / (RAND_MAX / 100.f)) 
        return true;
    return false;
}

#endif // KAL_RNG_IMPL
