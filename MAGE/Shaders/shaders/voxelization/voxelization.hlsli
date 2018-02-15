//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                         | Default
//-----------------------------------------------------------------------------
// DISABLE_BASE_COLOR_TEXTURE               | not defined
// DISABLE_MATERIAL_TEXTURE                 | not defined
// DISABLE_TSNM                             | not defined
// DISABLE_DIFFUSE_BRDF                     | not defined
// DISABLE_SPECULAR_BRDF                    | not defined
// BRDF_F_COMPONENT                         | F_Schlick
// BRDF_D_COMPONENT                         | D_GGX
// BRDF_G_COMPONENT                         | G_GXX
// BRDF_MINIMUM_ALPHA                       | 0.1f
// BRDF_DOT_EPSILON                         | 0.00001f
// LIGHT_DISTANCE_ATTENUATION_COMPONENT     | DistanceAttenuation
// LIGHT_ANGULAR_ATTENUATION_COMPONENT      | AngularAttenuation
// FOG_FACTOR_COMPONENT                     | FogFactor_Exponential
// BRDFxCOS_COMPONENT                       | not defined
// DISABLE_DIRECTIONAL_LIGHTS               | not defined
// DISABLE_OMNI_LIGHTS                      | not defined
// DISABLE_SPOT_LIGHTS                      | not defined
// DISABLE_SHADOW_MAPPING                   | not defined
// DISABLE_SHADOW_MAPPED_DIRECTIONAL_LIGHTS | not defined
// DISABLE_SHADOW_MAPPED_OMNI_LIGHTS        | not defined
// DISABLE_SHADOW_MAPPED_SPOT_LIGHTS        | not defined
// DISABLE_FOG                              | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "forward\forward_input.hlsli"

#define DISABLE_AMBIENT_LIGHT
#define DISABLE_VCT  
#include "lighting.hlsli"

#include "voxelization\voxel.hlsli"

//-----------------------------------------------------------------------------
// UAV
//-----------------------------------------------------------------------------
RW_STRUCTURED_BUFFER(voxel_grid, Voxel, SLOT_UAV_VOXEL_BUFFER);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
void PS(PSInputPositionNormalTexture input) {
	// Valid range: [-R/2,R/2]x[R/2,-R/2]x[-R/2,R/2]
	const float3 voxel  = input.p_view * g_voxel_inv_size 
		                               * float3(1.0f, -1.0f, 1.0f);
	// Valid range: [0,R)x(R,0]x[0,R)
	const  int3 s_index = floor(voxel + 0.5f * g_voxel_grid_resolution);
	const uint3   index = (uint3)s_index;

	[branch]
	if (any(s_index < 0 || index >= g_voxel_grid_resolution)) {
		return;
	}

	// Obtain the base color of the material.
	const float4 base_color = GetMaterialBaseColor(input.tex);
	
	clip(base_color.w - TRANSPARENCY_THRESHOLD);

	// Obtain the material parameters [roughness, metalness] of the material.
	const float2 material = GetMaterialParameters(input.tex);
	// Obtain the view-space normal.
	const float3 n_view   = GetNormal(input.p_view, input.n_view, input.tex2);

	// Calculate the pixel radiance.
	const float3 L = GetDirectRadiance(input.p_view, n_view, 
									   base_color.xyz, material.x, material.y);

	const uint flat_index = FlattenIndex(index, g_voxel_grid_resolution);

	// Encode the radiance and normal.
	const uint encoded_L = EncodeRadiance(L);
	const uint endoced_n = EncodeNormal(n_view);
	// Store the encoded radiance and normal.
	InterlockedMax(voxel_grid[flat_index].encoded_L, encoded_L);
	InterlockedMax(voxel_grid[flat_index].encoded_n, endoced_n);
}