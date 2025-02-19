// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Name: kal_bit.h
// Des: Bit logic and manipulation helper
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#pragma once

#include "kal_defines.h"
#include "kal_types.h"
#include <stdbool.h>

KAL_INLINE
void
kal_bit_enable(usize* var, usize flag) {
    *var |= flag;
}
KAL_INLINE
void
kal_bit_disable(usize* var, usize flag) {
    *var &= ~flag;
}
KAL_INLINE
void
kal_bit_toggle(usize* var, usize flag) {
    *var ^= flag;
}
KAL_INLINE
bool
kal_bit_ismatch(usize* var, usize flag) {
    return (var & flag) == flag;
}
