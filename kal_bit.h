// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Name: kal_bit.h
// Des: Bit logic and manipulation helper
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#pragma once

#include "kal_defines.h"
#include "kal_types.h"
#include <stdbool.h>

#define kal_bit_enable(a, b) (a) |= (b)
#define kal_bit_disable(a, b) (a) &= ~(b)
#define kal_bit_toggle(a, b) (a) ^= (b)
#define kal_bit_match(a, b) ((a) & (b)) == (b)
