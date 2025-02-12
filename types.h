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

// Used for conditionals with bitmasking
typedef u8 bool8;
typedef u16 bool16;
typedef u32 bool32;
typedef u64 bool64;

typedef float f32;
typedef double f64;

typedef struct vec2f_s {
    f32 x, y;
} vec2f_s;
typedef struct vec3f_s {
    f32 x, y, z;
} vec3f_s;
typedef struct vec4f_s {
    f32 x, y, z, w;
} vec4f_s;

