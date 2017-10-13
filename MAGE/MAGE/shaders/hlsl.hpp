#ifndef MAGE_HEADER_HLSL
#define MAGE_HEADER_HLSL

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------

#define TRANSPARENCY_THRESHOLD  0.75f

//-----------------------------------------------------------------------------
// Engine Includes: Thread Configurations
//-----------------------------------------------------------------------------

#define MAGE_NVIDIA_WARP_SIZE   32
#define MAGE_AMD_WAFEFRONT_SIZE 64
#define GROUP_SIZE_DEFAULT      16

//-----------------------------------------------------------------------------
// Engine Includes: Sampler Types
//-----------------------------------------------------------------------------

#define CONCAT_REG_S(x) s##x
#define REG_S(x) CONCAT_REG_S(x)

#define SAMPLER_STATE(name, slot)               SamplerState name \
													: register(REG_S(slot))
#define SAMPLER_COMPARISON_STATE(name, slot)    SamplerComparisonState name \
													: register(REG_S(slot))

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
// Engine Includes: Constant Buffer Types 
//-----------------------------------------------------------------------------

#define CONCAT_REG_B(x) b##x
#define REG_B(x) CONCAT_REG_B(x)

#define CBUFFER(name, slot)                     cbuffer name \
													: register(REG_B(slot))

//-----------------------------------------------------------------------------
// Engine Includes: Constant Buffers 
//-----------------------------------------------------------------------------

#define SLOT_CBUFFER_GAME                       0
#define SLOT_CBUFFER_COLOR                      1
#define SLOT_CBUFFER_LIGHTING                   1
#define SLOT_CBUFFER_PER_FRAME                  2
#define SLOT_CBUFFER_PER_DRAW                   3

//-----------------------------------------------------------------------------
// Engine Includes: SRV and UAV Types
//-----------------------------------------------------------------------------

#define CONCAT_REG_T(x) t##x
#define REG_T(x) CONCAT_REG_T(x)

#define CONCAT_REG_U(x) u##x
#define REG_U(x) CONCAT_REG_U(x)

#define BYTE_ADDRESS_BUFFER(name, slot)         ByteAddressBuffer name \
													: register(REG_T(slot))
#define RW_BYTE_ADDRESS_BUFFER(name,slot)       RWByteAddressBuffer name \
													: register(REG_U(slot))

#define BUFFER(name, type, slot)                Buffer< type > name \
													: register(REG_T(slot))
#define RW_BUFFER(name, type, slot)             RWBuffer< type > name \
													: register(REG_U(slot))

#define STRUCTURED_BUFFER(name, type, slot)     StructuredBuffer< type > name \
													: register(REG_T(slot))
#define RW_STRUCTURED_BUFFER(name, type, slot)  RWStructuredBuffer< type > name \
													: register(REG_U(slot))
#define ROV_STRUCTURED_BUFFER(name, type, slot) RasterizerOrderedStructuredBuffer< type > name \
													: register(REG_U(slot))

#define APPEND_STRUCTURED_BUFFER(name, type, slot) ConsumeStructuredBuffer< type > name \
													: register(REG_U(slot))
#define CONSUME_STRUCTURED_BUFFER(name, type, slot) AppendStructuredBuffer< type > name \
													: register(REG_U(slot))

#define TEXTURE_1D(name, type, slot)            Texture1D< type > name \
													: register(REG_T(slot))
#define TEXTURE_1D_ARRAY(name, type, slot)      Texture1DArray< type > name \
													: register(REG_T(slot))
#define RW_TEXTURE_1D(name, type, slot)         RWTexture1D< type > name \
													: register(REG_U(slot))
#define RW_TEXTURE_1D_ARRAY(name, type, slot)   RWTexture1DArray< type > name \
													: register(REG_U(slot))

#define TEXTURE_2D(name, type, slot)            Texture2D< type > name \
													: register(REG_T(slot))
#define TEXTURE_2D_ARRAY(name, type, slot)      Texture2DArray< type > name \
													: register(REG_T(slot))
#define TEXTURE_2D_MS(name, type, slot)         Texture2DMS< type > name \
													: register(REG_T(slot))
#define TEXTURE_2D_MS_ARRAY(name, type, slot)   Texture2DMSArray< type > name \
													: register(REG_T(slot))
#define RW_TEXTURE_2D(name, type, slot)         RWTexture2D< type > name \
													: register(REG_U(slot))
#define RW_TEXTURE_2D_ARRAY(name, type, slot)   RWTexture2DArray< type > name \
													: register(REG_U(slot))
#define ROV_TEXTURE_2D(name, type, slot)        RasterizerOrderedTexture2D< type > name \
													: register(REG_U(slot))

#define TEXTURE_CUBE(name, type, slot)          TextureCube< type > name \
													: register(REG_T(slot))
#define TEXTURE_CUBE_ARRAY(name, type, slot)    TextureCubeArray< type > name \
													: register(REG_T(slot))

#define TEXTURE_3D(name, type, slot)            Texture3D< type > name \
													: register(REG_T(slot))
#define RW_TEXTURE_3D(name, type, slot)         RWTexture3D< type > name \
													: register(REG_U(slot))
#define ROV_TEXTURE_3D(name, type, slot)        RasterizerOrderedTexture3D< type > name \
													: register(REG_U(slot))

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

#endif // MAGE_HEADER_HLSL