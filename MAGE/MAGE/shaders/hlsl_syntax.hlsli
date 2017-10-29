#ifndef MAGE_HEADER_HLSL_SYNTAX
#define MAGE_HEADER_HLSL_SYNTAX

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
// Engine Includes: Constant Buffer Types 
//-----------------------------------------------------------------------------

#define CONCAT_REG_B(x) b##x
#define REG_B(x) CONCAT_REG_B(x)

#define CBUFFER(name, slot)                     cbuffer name \
													: register(REG_B(slot))

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

#endif // MAGE_HEADER_HLSL_SYNTAX