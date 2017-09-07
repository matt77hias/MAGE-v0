#ifndef MAGE_HEADER_HLSL
#define MAGE_HEADER_HLSL

#define MAGE_NVIDIA_WARP_SIZE   32
#define MAGE_AMD_WAFEFRONT_SIZE 64
#define GROUP_SIZE_DEFAULT      16

#define CONCAT_REG_B(x) b##x
#define CONCAT_REG_T(x) t##x
#define CONCAT_REG_S(x) s##x
#define CONCAT_REG_U(x) u##x
#define REG_B(x) CONCAT_REG_B(x)
#define REG_T(x) CONCAT_REG_T(x)
#define REG_S(x) CONCAT_REG_S(x)
#define REG_U(x) CONCAT_REG_U(x)

#define SLOT_SAMPLER_DEFAULT        0

#define SLOT_CBUFFER_COLOR          0
#define SLOT_CBUFFER_LIGHTING       0
#define SLOT_CBUFFER_PER_FRAME      1
#define SLOT_CBUFFER_PER_DRAW       2

#define SLOT_SRV_SPRITE             0
#define SLOT_SRV_TEXTURE            0

#define SLOT_SRV_LIGHTS_START       0
#define SLOT_SRV_DIRECTIONAL_LIGHTS 0
#define SLOT_SRV_OMNI_LIGHTS        1
#define SLOT_SRV_SPOT_LIGHTS        2

#define SLOT_SRV_GBUFFER_START      3
#define SLOT_SRV_DIFFUSE            3
#define SLOT_SRV_SPECULAR           4
#define SLOT_SRV_NORMAL             5
#define SLOT_SRV_DEPTH              6

#define SLOT_UAV_IMAGE              0

#endif // MAGE_HEADER_HLSL