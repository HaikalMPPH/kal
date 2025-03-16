// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#pragma once

// :: Static keyword rename :::::::::::::::::::::::::::::::::::::::::::::::::::
#define global static
#define internal static

// :: Static Inline Wrapper :::::::::::::::::::::::::::::::::::::::::::::::::::
#ifdef _MSC_VER
    #define KAL_INLINE __forceinline
#else
    #define KAL_INLINE inline __attribute__((always_inline))
#endif // _MSC_VER

// :: Array tools :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define kal_arr_len(arr) sizeof((arr)) / sizeof((arr)[0])
#define kal_row_col(row, col, max_col) ((row) * (max_col) + (col))

// :: Max and Min :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define kal_max(a, b) (a) > (b) ? (a) : (b)
#define kal_min(a, b) (a) < (b) ? (a) : (b)

