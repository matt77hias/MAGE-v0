//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                         | Default
//-----------------------------------------------------------------------------
// BRDF_DOT_EPSILON                         | 0.00001f
// BRDF_D_FUNCTION                          | D_GGX
// BRDF_FUNCTION                            | not defined
// BRDF_F_FUNCTION                          | F_Schlick
// BRDF_G_FUNCTION                          | G_GXX
// BRDF_MINIMUM_ALPHA                       | 0.1f
// DISABLE_BRDF_DIFFUSE                     | not defined
// DISABLE_BRDF_SPECULAR                    | not defined
// DISABLE_ILLUMINATION_DIRECT              | not defined
// DISABLE_ILLUMINATION_INDIRECT            | not defined
// DISABLE_LIGHTS_DIRECTIONAL               | not defined
// DISABLE_LIGHTS_OMNI                      | not defined
// DISABLE_LIGHTS_SPOT                      | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED             | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED_DIRECTIONAL | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED_OMNI        | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED_SPOT        | not defined
// DISABLE_TEXTURE_BASE_COLOR               | not defined
// DISABLE_TEXTURE_MATERIAL                 | not defined
// DISABLE_TSNM                             | not defined
// FOG_FACTOR_FUNCTION                      | FogFactor_Exponential
// LIGHT_ANGULAR_ATTENUATION_FUNCTION       | AngularAttenuation
// LIGHT_DISTANCE_ATTENUATION_FUNCTION      | DistanceAttenuation

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "forward\forward_input.hlsli"

#define DISABLE_BRDF_SPECULAR
#define DISABLE_FOG
#define DISABLE_LIGHT_AMBIENT
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
	// Valid range: [0,R)x(R,0]x[0,R)
	const  int3 s_index = WorldToVoxelIndex(input.p_world);
	const uint3   index = (uint3)s_index;

	[branch]
	if (any(s_index < 0 || index >= g_voxel_grid_resolution)) {
		return;
	}

	// Obtain the base color of the material.
	const float4 base_color = GetMaterialBaseColor(input.tex_material);
	
	clip(base_color.w - TRANSPARENCY_THRESHOLD);

	// Obtain the material parameters [roughness, metalness] of the material.
	const float2 material_params = GetMaterialParameters(input.tex_material);
	// Obtain the surface normal expressed in world space.
	const float3 n_world = GetNormal(input.p_world, input.n_world, 
									 input.tex_geometry);

	Material material;
	material.base_color = base_color.xyz;
	material.roughness  = material_params.x;
	material.metalness  = material_params.y;

	// Calculate the pixel radiance.
	const float3 L = GetRadiance(input.p_world, n_world, material);

	const uint flat_index = FlattenIndex(index, g_voxel_grid_resolution);

	// Encode the radiance and normal.
	const uint encoded_L = EncodeRadiance(L);
	const uint endoced_n = EncodeNormal(n_world);
	// Store the encoded radiance and normal.
	InterlockedMax(voxel_grid[flat_index].encoded_L, encoded_L);
	InterlockedMax(voxel_grid[flat_index].encoded_n, endoced_n);
}