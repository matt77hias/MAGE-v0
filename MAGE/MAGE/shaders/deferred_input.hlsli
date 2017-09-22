//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "lighting.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerFrame, SLOT_CBUFFER_PER_FRAME) {
	// CAMERA
	// The projection values of the view-to-projection transformation matrix.
	// g_projection_values.x = 1 / view_to_projection00
	// g_projection_values.y = 1 / view_to_projection11
	// g_projection_values.z =  view_to_projection32
	// g_projection_values.w = -view_to_projection22
	float4 g_projection_values : packoffset(c0);
	
	// MATERIAL
	// The 1st BRDF dependent material coefficient start.
	// Ns    [(Modified) Phong/(Modified) Blinn-Phong]
	// alpha [Ward(-Duer)]
	// m     [Cook-Torrance]
	float g_mat1_start         : packoffset(c1.x);
	// The 1st BRDF dependent material coefficient range.
	// Ns    [(Modified) Phong/(Modified) Blinn-Phong]
	// alpha [Ward(-Duer)]
	// m     [Cook-Torrance]
	float g_mat1_range         : packoffset(c1.y);
	// The 2nd BRDF dependent material coefficient start.
	// R0    [Cook-Torrance]
	float g_mat2_start         : packoffset(c1.z);
	// The 2nd BRDF dependent material coefficient range.
	// R0    [Cook-Torrance]
	float g_mat2_range         : packoffset(c1.w);
};

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_diffuse_texture,  float4, SLOT_SRV_DIFFUSE);
TEXTURE_2D(g_specular_texture, float4, SLOT_SRV_SPECULAR);
TEXTURE_2D(g_normal_texture,   float3, SLOT_SRV_NORMAL);
TEXTURE_2D(g_depth_texture,    float,  SLOT_SRV_DEPTH);