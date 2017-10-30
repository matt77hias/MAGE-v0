//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#define ENABLE_TRANSPARENCY
#define TSNM
#define BRDFxCOS CookTorranceBRDFxCos
#define BRDF_F_COMPONENT F_None
#define BRDF_D_COMPONENT D_WardDuer
#define BRDF_V_COMPONENT V_Ward
#include "forward\forward.hlsli"