#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef size_t  usize;

typedef float f32;
typedef double f64;

typedef union vec2f_u {
    f32 arr[2];
    struct {
        f32 x, y;
    };
} vec2f_u;
typedef union vec3f_u {
    f32 arr[3];
    struct {
        f32 x, y, z;
    };
} vec3f_u;
typedef union vec4f_u {
    f32 arr[4];
    struct {
        f32 x, y, z, w;
    };
} vec4f_u;
