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
#define MAGE_GUID_CS_DEFERRED_PHONG                L"mage_deferred_phong_cs"
#define MAGE_GUID_CS_DEFERRED_MODIFIED_PHONG       L"mage_deferred_modified_phong_cs"
#define MAGE_GUID_CS_DEFERRED_BLINN_PHONG          L"mage_deferred_blinn_phong_cs"
#define MAGE_GUID_CS_DEFERRED_MODIFIED_BLINN_PHONG L"mage_deferred_modified_blinn_phong_cs"
#define MAGE_GUID_CS_DEFERRED_WARD                 L"mage_deferred_ward_cs"
#define MAGE_GUID_CS_DEFERRED_WARD_DUER            L"mage_deferred_ward_duer_cs"
#define MAGE_GUID_CS_DEFERRED_COOK_TORRANCE        L"mage_deferred_cook_torrance_cs"

// Forward
#define MAGE_GUID_VS_TRANSFORM                     L"mage_transform_vs"
#define MAGE_GUID_PS_EMISSIVE                      L"mage_emissive_ps"
#define MAGE_GUID_PS_LAMBERTIAN                    L"mage_lambertian_ps"
#define MAGE_GUID_PS_PHONG                         L"mage_phong_ps"
#define MAGE_GUID_PS_MODIFIED_PHONG                L"mage_modified_phong_ps"
#define MAGE_GUID_PS_BLINN_PHONG                   L"mage_blinn_phong_ps"
#define MAGE_GUID_PS_MODIFIED_BLINN_PHONG          L"mage_modified_blinn_phong_ps"
#define MAGE_GUID_PS_WARD                          L"mage_ward_ps"
#define MAGE_GUID_PS_WARD_DUER                     L"mage_ward_duer_ps"
#define MAGE_GUID_PS_COOK_TORRANCE                 L"mage_cook_torrance_ps"
#define MAGE_GUID_PS_TSNM_LAMBERTIAN               L"mage_tsnm_lambertian_ps"
#define MAGE_GUID_PS_TSNM_PHONG                    L"mage_tsnm_phong_ps"
#define MAGE_GUID_PS_TSNM_MODIFIED_PHONG           L"mage_tsnm_modified_phong_ps"
#define MAGE_GUID_PS_TSNM_BLINN_PHONG              L"mage_tsnm_blinn_phong_ps"
#define MAGE_GUID_PS_TSNM_MODIFIED_BLINN_PHONG     L"mage_tsnm_modified_blinn_phong_ps"
#define MAGE_GUID_PS_TSNM_WARD                     L"mage_tsnm_ward_ps"
#define MAGE_GUID_PS_TSNM_WARD_DUER                L"mage_tsnm_ward_duer_ps"
#define MAGE_GUID_PS_TSNM_COOK_TORRANCE            L"mage_tsnm_cook_torrance_ps"

// Sprite
#define MAGE_GUID_VS_SPRITE                        L"mage_sprite_vs"
#define MAGE_GUID_PS_SPRITE                        L"mage_sprite_ps"

// Miscellaneous
#define MAGE_GUID_VS_MINIMAL_TRANSFORM             L"mage_minimal_transform_vs"
#define MAGE_GUID_PS_IMAGE                         L"mage_image_ps"
#define MAGE_GUID_PS_IMAGE_DEPTH                   L"mage_image_depth_ps"
#define MAGE_GUID_PS_CONSTANT_COLOR                L"mage_constant_color_ps"
#define MAGE_GUID_PS_CONSTANT_COLOR_TEXTURE        L"mage_constant_color_texture_ps"
#define MAGE_GUID_PS_DISTANCE                      L"mage_distance_ps"
#define MAGE_GUID_VS_SHADING_NORMAL                L"mage_shading_normal_vs"
#define MAGE_GUID_PS_SHADING_NORMAL                L"mage_shading_normal_ps"
#define MAGE_GUID_PS_TSNM_SHADING_NORMAL           L"mage_tsnm_shading_normal_ps"
#define MAGE_GUID_VS_BOUNDING_VOLUME               L"mage_bounding_volume_vs"
#define MAGE_GUID_PS_BOUNDING_VOLUME               L"mage_bounding_volume_ps"

// Primitives
#define MAGE_GUID_VS_FULLSCREEN_TRIANGLE           L"mage_fullscreen_triangle_vs"

#pragma endregion