#ifndef MAGE_HEADER_HLSL
#define MAGE_HEADER_HLSL

#define MAGE_NVIDIA_WARP_SIZE   32
#define MAGE_AMD_WAFEFRONT_SIZE 64
#define DEFAULT_GROUP_SIZE      16

#define B_REGISTER(x)	(b##x)
#define T_REGISTER(x)	(t##x)
#define S_REGISTER(x)	(s##x)
#define U_REGISTER(x)	(u##x)

#define SLOT_CBUFFER_COLOR          0
#define SLOT_CBUFFER_LIGHT          0
#define SLOT_CBUFFER_PER_FRAME      1
#define SLOT_CBUFFER_PER_DRAW       2

#define SLOT_SRV_SPRITE             0
#define SLOT_SRV_DIRECTIONAL_LIGHTS 0
#define SLOT_SRV_OMNI_LIGHTS        1
#define SLOT_SRV_SPOT_LIGHTS        2
#define SLOT_SRV_DIFFUSE            3
#define SLOT_SRV_SPECULAR           4
#define SLOT_SRV_NORMAL             5
#define SLOT_SRV_DEPTH              6

#define SLOT_UAV_IMAGE              0

#endif // MAGE_HEADER_HLSL