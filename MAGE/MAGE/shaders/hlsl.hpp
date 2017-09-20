#ifndef MAGE_HEADER_HLSL
#define MAGE_HEADER_HLSL

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------

#define TRANSPARENCY_THRESHOLD  0.8f

//-----------------------------------------------------------------------------
// Engine Includes: Thread Configurations
//-----------------------------------------------------------------------------

#define MAGE_NVIDIA_WARP_SIZE   32
#define MAGE_AMD_WAFEFRONT_SIZE 64
#define GROUP_SIZE_DEFAULT      16

//-----------------------------------------------------------------------------
// Engine Includes: Registers
//-----------------------------------------------------------------------------

#define CONCAT_REG_B(x) b##x
#define CONCAT_REG_T(x) t##x
#define CONCAT_REG_S(x) s##x
#define CONCAT_REG_U(x) u##x

#define REG_B(x) CONCAT_REG_B(x)
#define REG_T(x) CONCAT_REG_T(x)
#define REG_S(x) CONCAT_REG_S(x)
#define REG_U(x) CONCAT_REG_U(x)

//-----------------------------------------------------------------------------
// Engine Includes: Samplers
//-----------------------------------------------------------------------------

#define SLOT_SAMPLER_VARIABLE_0                0
#define SLOT_SAMPLER_VARIABLE_1                1
#define SLOT_SAMPLER_VARIABLE_2                2
#define SLOT_SAMPLER_VARIABLE_3                3
#define SLOT_SAMPLER_VARIABLE_START            SLOT_SAMPLER_VARIABLE_0
#define SLOT_SAMPLER_VARIABLE_END              SLOT_SAMPLER_VARIABLE_3
#define SLOT_SAMPLER_VARIABLE_COUNT            (SLOT_SAMPLER_VARIABLE_END + 1 - SLOT_SAMPLER_VARIABLE_START)

#define SLOT_SAMPLER_POINT_WRAP                4
#define SLOT_SAMPLER_POINT_CLAMP               5
#define SLOT_SAMPLER_POINT_MIRROR              6
#define SLOT_SAMPLER_LINEAR_WRAP               7
#define SLOT_SAMPLER_LINEAR_CLAMP              8
#define SLOT_SAMPLER_LINEAR_MIRROR             9
#define SLOT_SAMPLER_ANISOTROPIC_WRAP          10
#define SLOT_SAMPLER_ANISOTROPIC_CLAMP         11
#define SLOT_SAMPLER_ANISOTROPIC_MIRROR        12
#define SLOT_SAMPLER_PCF                       13
#define SLOT_SAMPLER_PERSISTENT_START          SLOT_SAMPLER_POINT_WRAP
#define SLOT_SAMPLER_PERSISTENT_END            SLOT_SAMPLER_PCF
#define SLOT_SAMPLER_PERSISTENT_COUNT          (SLOT_SAMPLER_PERSISTENT_END + 1 - SLOT_SAMPLER_PERSISTENT_START)

//-----------------------------------------------------------------------------
// Engine Includes: Constant Buffers 
//-----------------------------------------------------------------------------

#define SLOT_CBUFFER_COLOR                     0
#define SLOT_CBUFFER_LIGHTING                  0
#define SLOT_CBUFFER_PER_FRAME                 1
#define SLOT_CBUFFER_PER_DRAW                  2

//-----------------------------------------------------------------------------
// Engine Includes: Light and Shadow Map SRVs
//-----------------------------------------------------------------------------

#define SLOT_SRV_DIRECTIONAL_LIGHTS            0
#define SLOT_SRV_OMNI_LIGHTS                   1
#define SLOT_SRV_SPOT_LIGHTS                   2

#define SLOT_SRV_SHADOW_MAP_DIRECTIONAL_LIGHTS 3
#define SLOT_SRV_SHADOW_MAP_OMNI_LIGHTS        4
#define SLOT_SRV_SHADOW_MAP_SPOT_LIGHTS        5

#define SLOT_SRV_DIRECTIONAL_SHADOW_MAPS       6
#define SLOT_SRV_OMNI_SHADOW_MAPS              7
#define SLOT_SRV_SPOT_SHADOW_MAPS              8

#define SLOT_SRV_LIGHTS_START                  SLOT_SRV_DIRECTIONAL_LIGHTS
#define SLOT_SRV_SHADOW_MAP_LIGHTS_START       SLOT_SRV_SHADOW_MAP_DIRECTIONAL_LIGHTS
#define SLOT_SRV_SHADOW_MAPS_START             SLOT_SRV_DIRECTIONAL_SHADOW_MAPS

//-----------------------------------------------------------------------------
// Engine Includes: GBuffer SRVs
//-----------------------------------------------------------------------------

#define SLOT_SRV_DIFFUSE                       9
#define SLOT_SRV_SPECULAR                      10
#define SLOT_SRV_NORMAL                        11
#define SLOT_SRV_DEPTH                         12
#define SLOT_SRV_GBUFFER_START                 SLOT_SRV_DIFFUSE

//-----------------------------------------------------------------------------
// Engine Includes: General SRVs
//-----------------------------------------------------------------------------

#define SLOT_SRV_IMAGE                         SLOT_SRV_DIFFUSE
#define SLOT_SRV_SPRITE                        SLOT_SRV_DIFFUSE
#define SLOT_SRV_TEXTURE                       SLOT_SRV_DIFFUSE

//-----------------------------------------------------------------------------
// Engine Includes: General UAVs
//-----------------------------------------------------------------------------

#define SLOT_UAV_IMAGE                         0

#endif // MAGE_HEADER_HLSL