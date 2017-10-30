//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#define ENABLE_TRANSPARENCY
#define BRDFxCOS CookTorranceBRDFxCos
#define BRDF_F_COMPONENT F_None
#define BRDF_D_COMPONENT D_BlinnPhong
#define BRDF_V_COMPONENT V_Implicit
#include "forward\forward.hlsli"