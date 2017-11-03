#ifndef MAGE_HEADER_HLSL
#define MAGE_HEADER_HLSL

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// DISSABLE_INVERTED_Z_BUFFER             | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------

#define TRANSPARENCY_SHADOW_THRESHOLD 0.75f
#define TRANSPARENCY_SKIP_THRESHOLD   0.00392157f // ~  1/255
#define TRANSPARENCY_THRESHOLD        0.95686275f // ~244/255

#ifdef DISSABLE_INVERTED_Z_BUFFER
	#define Z_NEAR 0.0f
	#define Z_FAR  1.0f
#else  // DISSABLE_INVERTED_Z_BUFFER
	#define Z_FAR  0.0f
	#define Z_NEAR 1.0f
#endif // DISSABLE_INVERTED_Z_BUFFER

//-----------------------------------------------------------------------------
// Engine Includes: Thread Configurations
//-----------------------------------------------------------------------------

#define MAGE_NVIDIA_WARP_SIZE   32
#define MAGE_AMD_WAFEFRONT_SIZE 64
#define GROUP_SIZE_DEFAULT      16

#define GROUP_SIZE_MSAA_2X      16
#define GROUP_SIZE_MSAA_4X      16
#define GROUP_SIZE_MSAA_8X       8
#define GROUP_SIZE_MSAA_16X      8
#define GROUP_SIZE_MSAA_32X      4

#define GROUP_SIZE_SSAA_2X      16
#define GROUP_SIZE_SSAA_3X       8
#define GROUP_SIZE_SSAA_4X       8

//-----------------------------------------------------------------------------
// Engine Includes: Samplers
//-----------------------------------------------------------------------------

#define SLOT_SAMPLER_VARIABLE_0                 0
#define SLOT_SAMPLER_VARIABLE_1                 1
#define SLOT_SAMPLER_VARIABLE_2                 2
#define SLOT_SAMPLER_VARIABLE_3                 3
#define SLOT_SAMPLER_VARIABLE_START             SLOT_SAMPLER_VARIABLE_0
#define SLOT_SAMPLER_VARIABLE_END               SLOT_SAMPLER_VARIABLE_3
#define SLOT_SAMPLER_VARIABLE_COUNT             (SLOT_SAMPLER_VARIABLE_END + 1 \
													- SLOT_SAMPLER_VARIABLE_START)

#define SLOT_SAMPLER_POINT_WRAP                 4
#define SLOT_SAMPLER_POINT_CLAMP                5
#define SLOT_SAMPLER_POINT_MIRROR               6
#define SLOT_SAMPLER_LINEAR_WRAP                7
#define SLOT_SAMPLER_LINEAR_CLAMP               8
#define SLOT_SAMPLER_LINEAR_MIRROR              9
#define SLOT_SAMPLER_ANISOTROPIC_WRAP           10
#define SLOT_SAMPLER_ANISOTROPIC_CLAMP          11
#define SLOT_SAMPLER_ANISOTROPIC_MIRROR         12
#define SLOT_SAMPLER_PCF                        13
#define SLOT_SAMPLER_PERSISTENT_START           SLOT_SAMPLER_POINT_WRAP
#define SLOT_SAMPLER_PERSISTENT_END             SLOT_SAMPLER_PCF
#define SLOT_SAMPLER_PERSISTENT_COUNT           (SLOT_SAMPLER_PERSISTENT_END + 1 \
													- SLOT_SAMPLER_PERSISTENT_START)

//-----------------------------------------------------------------------------
// Engine Includes: Constant Buffers 
//-----------------------------------------------------------------------------

#define SLOT_CBUFFER_GAME                       0
#define SLOT_CBUFFER_PRIMARY_CAMERA             1
#define SLOT_CBUFFER_COLOR                      2
#define SLOT_CBUFFER_LIGHTING                   2
#define SLOT_CBUFFER_MODEL                      3
#define SLOT_CBUFFER_SECONDARY_CAMERA           4

//-----------------------------------------------------------------------------
// Engine Includes: Light and Shadow Map SRVs
//-----------------------------------------------------------------------------

#define SLOT_SRV_LIGHT_INDEX_LIST               0

#define SLOT_SRV_DIRECTIONAL_LIGHTS             1
#define SLOT_SRV_OMNI_LIGHTS                    2
#define SLOT_SRV_SPOT_LIGHTS                    3
#define SLOT_SRV_LIGHTS_START                   SLOT_SRV_DIRECTIONAL_LIGHTS
#define SLOT_SRV_LIGHTS_END                     SLOT_SRV_SPOT_LIGHTS
#define SLOT_SRV_LIGHTS_COUNT                   (SLOT_SRV_LIGHTS_END + 1 \
													- SLOT_SRV_LIGHTS_START)

#define SLOT_SRV_SHADOW_MAP_DIRECTIONAL_LIGHTS  4
#define SLOT_SRV_SHADOW_MAP_OMNI_LIGHTS         5
#define SLOT_SRV_SHADOW_MAP_SPOT_LIGHTS         6
#define SLOT_SRV_SHADOW_MAP_LIGHTS_START        SLOT_SRV_SHADOW_MAP_DIRECTIONAL_LIGHTS
#define SLOT_SRV_SHADOW_MAP_LIGHTS_END          SLOT_SRV_SHADOW_MAP_SPOT_LIGHTS
#define SLOT_SRV_SHADOW_MAP_LIGHTS_COUNT        (SLOT_SRV_SHADOW_MAP_LIGHTS_END + 1 \
													- SLOT_SRV_SHADOW_MAP_LIGHTS_START)

#define SLOT_SRV_DIRECTIONAL_SHADOW_MAPS        7
#define SLOT_SRV_OMNI_SHADOW_MAPS               8
#define SLOT_SRV_SPOT_SHADOW_MAPS               9
#define SLOT_SRV_SHADOW_MAPS_START              SLOT_SRV_DIRECTIONAL_SHADOW_MAPS
#define SLOT_SRV_SHADOW_MAPS_END                SLOT_SRV_SPOT_SHADOW_MAPS
#define SLOT_SRV_SHADOW_MAPS_COUNT              (SLOT_SRV_SHADOW_MAPS_END + 1 \
													- SLOT_SRV_SHADOW_MAPS_START)

#define SLOT_SRV_LIGHTING_START                 SLOT_SRV_LIGHTS_START
#define SLOT_SRV_LIGHTING_END                   SLOT_SRV_SHADOW_MAPS_END
#define SLOT_SRV_LIGHTING_COUNT                 (SLOT_SRV_LIGHTING_END + 1 \
													- SLOT_SRV_LIGHTING_START)

//-----------------------------------------------------------------------------
// Engine Includes: GBuffer SRVs
//-----------------------------------------------------------------------------

#define SLOT_SRV_BASE_COLOR                     10
#define SLOT_SRV_MATERIAL                       11
#define SLOT_SRV_NORMAL                         12
#define SLOT_SRV_DEPTH                          13
#define SLOT_SRV_GBUFFER_START                  SLOT_SRV_BASE_COLOR
#define SLOT_SRV_GBUFFER_END                    SLOT_SRV_DEPTH
#define SLOT_SRV_GBUFFER_COUNT                  (SLOT_SRV_GBUFFER_END + 1 \
													- SLOT_SRV_GBUFFER_START)

//-----------------------------------------------------------------------------
// Engine Includes: General SRVs
//-----------------------------------------------------------------------------

#define SLOT_SRV_IMAGE                          SLOT_SRV_BASE_COLOR
#define SLOT_SRV_SPRITE                         SLOT_SRV_BASE_COLOR
#define SLOT_SRV_TEXTURE                        SLOT_SRV_BASE_COLOR

//-----------------------------------------------------------------------------
// Engine Includes: General UAVs
//-----------------------------------------------------------------------------

#define SLOT_UAV_IMAGE                          0
#define SLOT_UAV_NORMAL                         1
#define SLOT_UAV_DEPTH                          2

#endif // MAGE_HEADER_HLSL