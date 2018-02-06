//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#define ENABLE_TRANSPARENCY
#define BRDFxCOS_COMPONENT CookTorranceBRDFxCos
#define BRDF_F_COMPONENT   F_None
#define BRDF_D_COMPONENT   D_BlinnPhong
#define BRDF_V_COMPONENT   V_Implicit
#define DISABLE_TSNM
#include "forward\forward.hlsli"