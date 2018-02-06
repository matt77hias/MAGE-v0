//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#define ENABLE_TRANSPARENCY
#define BRDFxCOS_COMPONENT CookTorranceBRDFxCos
#define BRDF_F_COMPONENT   F_None
#define BRDF_D_COMPONENT   D_WardDuer
#define BRDF_V_COMPONENT   V_Ward
#define DISABLE_TSNM
#define DISABLE_VCT
#include "forward\forward.hlsli"