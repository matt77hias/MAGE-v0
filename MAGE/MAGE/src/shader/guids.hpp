#pragma once

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

// Depth
#define MAGE_GUID_VS_DEPTH                         L"mage_depth_vs"
#define MAGE_GUID_VS_DEPTH_TRANSPARENT             L"mage_depth_transparent_vs"
#define MAGE_GUID_PS_DEPTH_TRANSPARENT             L"mage_depth_transparent_ps"

// GBuffer
#define MAGE_GUID_PS_GBUFFER                       L"mage_gbuffer_ps"
#define MAGE_GUID_PS_GBUFFER_TSNM                  L"mage_gbuffer_tsnm_ps"

// Deferred
#define MAGE_GUID_CS_DEFERRED_EMISSIVE             L"mage_deferred_emissive_cs"
#define MAGE_GUID_CS_DEFERRED_LAMBERTIAN           L"mage_deferred_lambertian_cs"
#define MAGE_GUID_CS_DEFERRED_COOK_TORRANCE        L"mage_deferred_cook_torrance_cs"

// Forward
#define MAGE_GUID_VS_TRANSFORM                     L"mage_transform_vs"
#define MAGE_GUID_PS_EMISSIVE                      L"mage_emissive_ps"
#define MAGE_GUID_PS_LAMBERTIAN                    L"mage_lambertian_ps"
#define MAGE_GUID_PS_COOK_TORRANCE                 L"mage_cook_torrance_ps"
#define MAGE_GUID_PS_TSNM_LAMBERTIAN               L"mage_tsnm_lambertian_ps"
#define MAGE_GUID_PS_TSNM_COOK_TORRANCE            L"mage_tsnm_cook_torrance_ps"

// Sky
#define MAGE_GUID_PS_SKY                           L"mage_sky_ps"

// Sprite
#define MAGE_GUID_VS_SPRITE                        L"mage_sprite_vs"
#define MAGE_GUID_PS_SPRITE                        L"mage_sprite_ps"

// Miscellaneous
#define MAGE_GUID_VS_MINIMAL_TRANSFORM             L"mage_minimal_transform_vs"
#define MAGE_GUID_PS_BACK_BUFFER                   L"mage_back_buffer_ps"
#define MAGE_GUID_PS_CONSTANT_COLOR                L"mage_constant_color_ps"
#define MAGE_GUID_PS_CONSTANT_COLOR_TEXTURE        L"mage_constant_color_texture_ps"
#define MAGE_GUID_PS_DISTANCE                      L"mage_distance_ps"
#define MAGE_GUID_VS_SHADING_NORMAL                L"mage_shading_normal_vs"
#define MAGE_GUID_PS_SHADING_NORMAL                L"mage_shading_normal_ps"
#define MAGE_GUID_PS_TSNM_SHADING_NORMAL           L"mage_tsnm_shading_normal_ps"
#define MAGE_GUID_VS_BOUNDING_VOLUME               L"mage_bounding_volume_vs"
#define MAGE_GUID_PS_BOUNDING_VOLUME               L"mage_bounding_volume_ps"

// Primitives
#define MAGE_GUID_VS_FAR_FULLSCREEN_TRIANGLE       L"mage_far_fullscreen_triangle_vs"
#define MAGE_GUID_VS_NEAR_FULLSCREEN_TRIANGLE      L"mage_near_fullscreen_triangle_vs"

#pragma endregion