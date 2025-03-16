// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Name: kal_bit.h
// Des: Bit logic and manipulation helper
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#pragma once

#include "defines.h"
#include "types.h"

#define kal_bit_enable(a, b) (a) |= (b)
#define kal_bit_disable(a, b) (a) &= ~(b)
#define kal_bit_toggle(a, b) (a) ^= (b)
#define kal_bit_match(a, b) ((a) & (b)) == (b)
