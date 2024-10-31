#pragma once
#include "raylib.h"
#include "../types.h"

typedef Vector2 vec2_s;
typedef Vector3 vec3_s;
typedef Vector4 vec4_s;
typedef Color color_s;
typedef Texture2D tex2d_s;
typedef Rectangle rect_s;

// = RCORE ===============================================================
extern void (*const rl_init_window)(i32, i32, const char*);
extern void (*const rl_set_target_fps)(i32);
extern void (*const rl_close_window)(void);
extern void (*const rl_begin_drawing)(void);
extern void (*const rl_end_drawing)(void);
extern void (*const rl_clear_background)(color_s);
extern bool (*const rl_window_should_close)(void);
extern bool (*const rl_is_key_pressed)(i32);
extern bool (*const rl_is_key_down)(i32);
extern f32 (*const rl_get_frame_time)(void);
extern i32 (*const rl_get_screen_height)(void);
extern i32 (*const rl_get_screen_width)(void);
extern f64 (*const rl_get_time)(void);
extern i32 (*const rl_get_random_value)(i32, i32);
extern void (*const rl_set_random_seed)(u32);

// = RTEXTURES ===========================================================
extern tex2d_s (*const rl_load_texture)(const char*);
extern void (*const rl_unload_texture)(tex2d_s);
extern void (*const rl_draw_texture_v)(tex2d_s, vec2_s, color_s);

// = RSHAPES =============================================================
extern void (*const rl_draw_rectangle)(i32, i32, i32, i32, color_s);
extern void (*const rl_draw_rectangle_rec)(rect_s, color_s);
extern void (*const rl_draw_rectangle_v)(vec2_s, vec2_s, color_s);
extern bool (*const rl_check_collision_recs)(rect_s, rect_s);






#ifdef KAL_MISC_RAYLIB_IMPL
// = RCORE ===============================================================
void (*const rl_init_window)(i32, i32, const char*) = InitWindow;
void (*const rl_set_target_fps)(i32) = SetTargetFPS;
void (*const rl_close_window)(void) = CloseWindow;
void (*const rl_begin_drawing)(void) = BeginDrawing;
void (*const rl_end_drawing)(void) = EndDrawing;
void (*const rl_clear_background)(color_s) = ClearBackground;
bool (*const rl_window_should_close)(void) = WindowShouldClose;
bool (*const rl_is_key_pressed)(i32) = IsKeyPressed;
bool (*const rl_is_key_down)(i32) = IsKeyDown;
f32 (*const rl_get_frame_time)(void) = GetFrameTime;
i32 (*const rl_get_screen_height)(void) = GetScreenHeight;
i32 (*const rl_get_screen_width)(void) = GetScreenWidth;
f64 (*const rl_get_time)(void) = GetTime;
i32 (*const rl_get_random_value)(i32, i32) = GetRandomValue;
void (*const rl_set_random_seed)(u32) = SetRandomSeed;

// = RTEXTURES ===========================================================
tex2d_s (*const rl_load_texture)(const char*) = LoadTexture;
void (*const rl_unload_texture)(tex2d_s) = UnloadTexture;
void (*const rl_draw_texture_v)(tex2d_s, vec2_s, color_s) = DrawTextureV;

// = RSHAPES =============================================================
void (*const rl_draw_rectangle)(i32, i32, i32, i32, color_s) = DrawRectangle;
void (*const rl_draw_rectangle_rec)(rect_s, color_s) = DrawRectangleRec;
void (*const rl_draw_rectangle_v)(vec2_s, vec2_s, color_s) = DrawRectangleV;
bool (*const rl_check_collision_recs)(rect_s, rect_s) = CheckCollisionRecs;
#endif // KAL_MISC_RAYLIB_IMPL
