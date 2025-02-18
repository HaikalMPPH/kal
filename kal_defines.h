// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#pragma once

// :: Static keyword rename :::::::::::::::::::::::::::::::::::::::::::::::::::
#define global static
#define internal static

// :: Static Inline Wrapper :::::::::::::::::::::::::::::::::::::::::::::::::::
#ifdef _MSC_VER
    #define KAL_INLINE static __forceinline
#else
    #define KAL_INLINE static inline __attribute__((always_inline))
#endif // _MSC_VER

// :: Array tools :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define kal_arrlen(arr) sizeof((arr)) / sizeof((arr)[0])
