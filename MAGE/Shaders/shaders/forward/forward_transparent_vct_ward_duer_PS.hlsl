//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#define ENABLE_TRANSPARENCY
#define BRDF_FUNCTION CookTorranceBRDF
#define BRDF_F_FUNCTION   F_None
#define BRDF_D_FUNCTION   D_WardDuer
#define BRDF_V_FUNCTION   V_Ward
#define DISABLE_TSNM
#include "forward\forward.hlsli"