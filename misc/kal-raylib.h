#ifndef KAL_RAYLIB_H
#define KAL_RAYLIB_H

#include "raylib.h"      // Core raylib functions
#include "raymath.h"     // Mathematical functions
#include "rlgl.h"        // OpenGL abstraction layer

//------------------------------------------------------------------------------
// Core types (lowercase with underscore naming)
//------------------------------------------------------------------------------
typedef Vector2 rl_vector2_s;
typedef Vector3 rl_vector3_s;
typedef Vector4 rl_vector4_s;
typedef Quaternion rl_quaternion_s;
typedef Matrix rl_matrix_s;
typedef Color rl_color_s;
typedef Rectangle rl_rectangle_s;
typedef Image rl_image_s;
typedef Texture2D rl_texture2d_s;
typedef RenderTexture2D rl_render_texture2d_s;
typedef NPatchInfo rl_n_patch_info_s;
typedef Camera2D rl_camera2d_s;
typedef Camera3D rl_camera3d_s;
typedef Ray rl_ray_s;
typedef RayCollision rl_ray_collision_s;
typedef BoundingBox rl_bounding_box_s;
typedef Font rl_font_s;
typedef Music rl_music_s;
typedef Sound rl_sound_s;
typedef Wave rl_wave_s;
typedef AudioStream rl_audio_stream_s;
typedef Shader rl_shader_s;
typedef Model rl_model_s;
typedef ModelAnimation rl_model_animation_s;
typedef Mesh rl_mesh_s;

//------------------------------------------------------------------------------
// Window-related functions
//------------------------------------------------------------------------------
#define rl_init_window InitWindow
#define rl_close_window CloseWindow
#define rl_window_should_close WindowShouldClose
#define rl_is_window_ready IsWindowReady
#define rl_is_window_fullscreen IsWindowFullscreen
#define rl_is_window_hidden IsWindowHidden
#define rl_is_window_minimized IsWindowMinimized
#define rl_is_window_maximized IsWindowMaximized
#define rl_is_window_focused IsWindowFocused
#define rl_is_window_resized IsWindowResized
#define rl_set_window_state SetWindowState
#define rl_clear_window_state ClearWindowState
#define rl_toggle_fullscreen ToggleFullscreen
#define rl_maximize_window MaximizeWindow
#define rl_minimize_window MinimizeWindow
#define rl_restore_window RestoreWindow
#define rl_set_window_icon SetWindowIcon
#define rl_set_window_title SetWindowTitle
#define rl_set_window_position SetWindowPosition
#define rl_set_window_monitor SetWindowMonitor
#define rl_set_window_min_size SetWindowMinSize
#define rl_set_window_size SetWindowSize
#define rl_get_window_position GetWindowPosition
#define rl_get_window_scale_dpi GetWindowScaleDPI
#define rl_get_screen_width GetScreenWidth
#define rl_get_screen_height GetScreenHeight
#define rl_get_monitor_count GetMonitorCount
#define rl_get_current_monitor GetCurrentMonitor
#define rl_get_monitor_position GetMonitorPosition
#define rl_get_monitor_width GetMonitorWidth
#define rl_get_monitor_height GetMonitorHeight
#define rl_get_monitor_physical_width GetMonitorPhysicalWidth
#define rl_get_monitor_physical_height GetMonitorPhysicalHeight
#define rl_get_monitor_refresh_rate GetMonitorRefreshRate
#define rl_get_window_position GetWindowPosition

//------------------------------------------------------------------------------
// Timing-related functions
//------------------------------------------------------------------------------
#define rl_set_target_fps SetTargetFPS
#define rl_get_fps GetFPS
#define rl_get_frame_time GetFrameTime
#define rl_get_time GetTime

//------------------------------------------------------------------------------
// Drawing-related functions
//------------------------------------------------------------------------------
#define rl_begin_drawing BeginDrawing
#define rl_end_drawing EndDrawing
#define rl_begin_mode2d BeginMode2D
#define rl_end_mode2d EndMode2D
#define rl_begin_mode3d BeginMode3D
#define rl_end_mode3d EndMode3D
#define rl_begin_texture_mode BeginTextureMode
#define rl_end_texture_mode EndTextureMode
#define rl_begin_shader_mode BeginShaderMode
#define rl_end_shader_mode EndShaderMode
#define rl_clear_background ClearBackground
#define rl_begin_blend_mode BeginBlendMode
#define rl_end_blend_mode EndBlendMode
#define rl_begin_scissor_mode BeginScissorMode
#define rl_end_scissor_mode EndScissorMode

//------------------------------------------------------------------------------
// Input-related functions: keyboard
//------------------------------------------------------------------------------
#define rl_is_key_pressed IsKeyPressed
#define rl_is_key_down IsKeyDown
#define rl_is_key_released IsKeyReleased
#define rl_is_key_up IsKeyUp
#define rl_set_exit_key SetExitKey
#define rl_get_key_pressed GetKeyPressed
#define rl_get_char_pressed GetCharPressed

//------------------------------------------------------------------------------
// Input-related functions: mouse
//------------------------------------------------------------------------------
#define rl_is_mouse_button_pressed IsMouseButtonPressed
#define rl_is_mouse_button_down IsMouseButtonDown
#define rl_is_mouse_button_released IsMouseButtonReleased
#define rl_is_mouse_button_up IsMouseButtonUp
#define rl_get_mouse_x GetMouseX
#define rl_get_mouse_y GetMouseY
#define rl_get_mouse_position GetMousePosition
#define rl_get_mouse_delta GetMouseDelta
#define rl_set_mouse_position SetMousePosition
#define rl_set_mouse_offset SetMouseOffset
#define rl_set_mouse_scale SetMouseScale
#define rl_get_mouse_wheel_move GetMouseWheelMove
#define rl_get_mouse_wheel_move_v GetMouseWheelMoveV

//------------------------------------------------------------------------------
// Shapes Drawing Functions
//------------------------------------------------------------------------------
#define rl_draw_pixel DrawPixel
#define rl_draw_pixel_v DrawPixelV
#define rl_draw_line DrawLine
#define rl_draw_line_v DrawLineV
#define rl_draw_line_ex DrawLineEx
#define rl_draw_line_strip DrawLineStrip
#define rl_draw_circle DrawCircle
#define rl_draw_circle_sector DrawCircleSector
#define rl_draw_circle_sector_lines DrawCircleSectorLines
#define rl_draw_circle_gradient DrawCircleGradient
#define rl_draw_circle_v DrawCircleV
#define rl_draw_circle_lines DrawCircleLines
#define rl_draw_circle_lines_v DrawCircleLinesV
#define rl_draw_ellipse DrawEllipse
#define rl_draw_ellipse_lines DrawEllipseLines
#define rl_draw_ring DrawRing
#define rl_draw_ring_lines DrawRingLines
#define rl_draw_rectangle DrawRectangle
#define rl_draw_rectangle_v DrawRectangleV
#define rl_draw_rectangle_rec DrawRectangleRec
#define rl_draw_rectangle_pro DrawRectanglePro
#define rl_draw_rectangle_gradient_v DrawRectangleGradientV
#define rl_draw_rectangle_gradient_h DrawRectangleGradientH
#define rl_draw_rectangle_gradient_ex DrawRectangleGradientEx
#define rl_draw_rectangle_lines DrawRectangleLines
#define rl_draw_rectangle_lines_ex DrawRectangleLinesEx
#define rl_draw_triangle DrawTriangle
#define rl_draw_triangle_lines DrawTriangleLines
#define rl_draw_triangle_fan DrawTriangleFan
#define rl_draw_triangle_strip DrawTriangleStrip
#define rl_draw_poly DrawPoly
#define rl_draw_poly_lines DrawPolyLines
#define rl_draw_poly_lines_ex DrawPolyLinesEx

//------------------------------------------------------------------------------
// Texture Loading and Drawing Functions
//------------------------------------------------------------------------------
#define rl_load_texture LoadTexture
#define rl_load_texture_from_image LoadTextureFromImage
#define rl_load_render_texture LoadRenderTexture
#define rl_unload_texture UnloadTexture
#define rl_unload_render_texture UnloadRenderTexture
#define rl_update_texture UpdateTexture
#define rl_update_texture_rec UpdateTextureRec
#define rl_get_texture_data GetTextureData
#define rl_get_screen_data GetScreenData
#define rl_gen_texture_mipmaps GenTextureMipmaps
#define rl_set_texture_filter SetTextureFilter
#define rl_set_texture_wrap SetTextureWrap
#define rl_draw_texture DrawTexture
#define rl_draw_texture_v DrawTextureV
#define rl_draw_texture_ex DrawTextureEx
#define rl_draw_texture_rec DrawTextureRec
#define rl_draw_texture_pro DrawTexturePro
#define rl_draw_texture_npatch DrawTextureNPatch
#define rl_draw_texture_tiled DrawTextureTiled

//------------------------------------------------------------------------------
// Math Functions
//------------------------------------------------------------------------------
#define rl_lerp Lerp
#define rl_clamp Clamp
#define rl_normalize Normalize
#define rl_remap Remap
#define rl_vector2_add Vector2Add
#define rl_vector2_subtract Vector2Subtract
#define rl_vector2_length Vector2Length
#define rl_vector2_scale Vector2Scale
#define rl_vector2_multiply Vector2Multiply
#define rl_vector2_normalize Vector2Normalize
#define rl_vector2_distance Vector2Distance
#define rl_vector2_angle Vector2Angle
#define rl_vector3_add Vector3Add
#define rl_vector3_subtract Vector3Subtract
#define rl_vector3_scale Vector3Scale
#define rl_vector3_multiply Vector3Multiply
#define rl_vector3_cross Vector3CrossProduct
#define rl_vector3_perpendicular Vector3Perpendicular
#define rl_vector3_length Vector3Length
#define rl_vector3_dot_product Vector3DotProduct
#define rl_vector3_distance Vector3Distance
#define rl_vector3_normalize Vector3Normalize

//------------------------------------------------------------------------------
// Text Drawing Functions
//------------------------------------------------------------------------------
#define rl_load_font LoadFont
#define rl_load_font_ex LoadFontEx
#define rl_unload_font UnloadFont
#define rl_draw_text DrawText
#define rl_draw_text_ex DrawTextEx
#define rl_draw_text_pro DrawTextPro
#define rl_draw_text_codepoint DrawTextCodepoint
#define rl_measure_text MeasureText
#define rl_measure_text_ex MeasureTextEx
#define rl_get_font_default GetFontDefault

//------------------------------------------------------------------------------
// Audio Loading and Playing Functions
//------------------------------------------------------------------------------
#define rl_init_audio_device InitAudioDevice
#define rl_close_audio_device CloseAudioDevice
#define rl_is_audio_device_ready IsAudioDeviceReady
#define rl_load_wave LoadWave
#define rl_load_sound LoadSound
#define rl_load_music LoadMusicStream
#define rl_unload_wave UnloadWave
#define rl_unload_sound UnloadSound
#define rl_unload_music UnloadMusicStream
#define rl_play_sound PlaySound
#define rl_pause_sound PauseSound
#define rl_resume_sound ResumeSound
#define rl_stop_sound StopSound
#define rl_play_music PlayMusicStream
#define rl_update_music UpdateMusicStream
#define rl_stop_music StopMusicStream
#define rl_pause_music PauseMusicStream
#define rl_resume_music ResumeMusicStream
#define rl_is_music_playing IsMusicStreamPlaying
#define rl_set_music_volume SetMusicVolume
#define rl_set_sound_volume SetSoundVolume

//------------------------------------------------------------------------------
// Color palette - constants
//------------------------------------------------------------------------------
#define RL_LIGHTGRAY  LIGHTGRAY
#define RL_GRAY       GRAY
#define RL_DARKGRAY   DARKGRAY
#define RL_YELLOW     YELLOW
#define RL_GOLD       GOLD
#define RL_ORANGE     ORANGE
#define RL_PINK       PINK
#define RL_RED        RED
#define RL_MAROON     MAROON
#define RL_GREEN      GREEN
#define RL_LIME       LIME
#define RL_DARKGREEN  DARKGREEN
#define RL_SKYBLUE    SKYBLUE
#define RL_BLUE       BLUE
#define RL_DARKBLUE   DARKBLUE
#define RL_PURPLE     PURPLE
#define RL_VIOLET     VIOLET
#define RL_DARKPURPLE DARKPURPLE
#define RL_BEIGE      BEIGE
#define RL_BROWN      BROWN
#define RL_DARKBROWN  DARKBROWN
#define RL_WHITE      WHITE
#define RL_BLACK      BLACK
#define RL_BLANK      BLANK
#define RL_MAGENTA    MAGENTA
#define RL_RAYWHITE   RAYWHITE

//------------------------------------------------------------------------------
// Key codes constants
//------------------------------------------------------------------------------
#define RL_KEY_SPACE           KEY_SPACE
#define RL_KEY_ESCAPE          KEY_ESCAPE
#define RL_KEY_ENTER           KEY_ENTER
#define RL_KEY_TAB             KEY_TAB
#define RL_KEY_RIGHT           KEY_RIGHT
#define RL_KEY_LEFT            KEY_LEFT
#define RL_KEY_DOWN            KEY_DOWN
#define RL_KEY_UP              KEY_UP
#define RL_KEY_W               KEY_W
#define RL_KEY_S               KEY_S
#define RL_KEY_D               KEY_D
#define RL_KEY_A               KEY_A
#define RL_MOUSE_LEFT_BUTTON   MOUSE_LEFT_BUTTON
#define RL_MOUSE_RIGHT_BUTTON  MOUSE_RIGHT_BUTTON
#define RL_MOUSE_MIDDLE_BUTTON MOUSE_MIDDLE_BUTTON

#endif // KAL_RAYLIB_H
