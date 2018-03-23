//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#define DISABLE_TSNM
#define BRDF_FUNCTION CookTorranceBRDF
#define BRDF_F_FUNCTION   F_None
#define BRDF_D_FUNCTION   D_BlinnPhong
#define BRDF_V_FUNCTION   V_Implicit
#include "voxelization\voxelization.hlsli"