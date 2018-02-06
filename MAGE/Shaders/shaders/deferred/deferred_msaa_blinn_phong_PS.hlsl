//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#define MSAA
#define BRDFxCOS_COMPONENT CookTorranceBRDFxCos
#define BRDF_F_COMPONENT   F_None
#define BRDF_D_COMPONENT   D_BlinnPhong
#define BRDF_V_COMPONENT   V_Implicit
#define DISABLE_VCT
#include "deferred\deferred.hlsli"