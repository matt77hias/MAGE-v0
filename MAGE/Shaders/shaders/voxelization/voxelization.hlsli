//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// DISSABLE_BASE_COLOR_TEXTURE            | not defined
// DISSABLE_MATERIAL_TEXTURE              | not defined
// TSNM                                   | not defined
// DISSABLE_SPECULAR_BRDF                 | not defined
// BRDF_F_COMPONENT                       | F_Schlick
// BRDF_D_COMPONENT                       | D_GGX
// BRDF_G_COMPONENT                       | G_GXX
// BRDF_MINIMUM_ALPHA                     | 0.1f
// BRDF_DOT_EPSILON                       | 0.00001f
// LIGHT_DISTANCE_ATTENUATION_COMPONENT   | DistanceAttenuation
// LIGHT_ANGULAR_ATTENUATION_COMPONENT    | AngularAttenuation
// FOG_FACTOR_COMPONENT                   | FogFactor_Exponential
// BRDFxCOS                               | not defined
// DISSABLE_AMBIENT_LIGHT                 | not defined
// DISSABLE_DIRECTIONAL_LIGHTS            | not defined
// DISSABLE_OMNI_LIGHTS                   | not defined
// DISSABLE_SPOT_LIGHTS                   | not defined
// DISSABLE_SHADOW_MAPPING                | not defined
// DISSABLE_SHADOW_MAP_DIRECTIONAL_LIGHTS | not defined
// DISSABLE_SHADOW_MAP_OMNI_LIGHTS        | not defined
// DISSABLE_SHADOW_MAP_SPOT_LIGHTS        | not defined
// DISSABLE_FOG                           | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#define DISSABLE_DIFFUSE_BRDF
#include "forward\forward_input.hlsli"
#include "lighting.hlsli"
#include "voxelization\voxel.hlsli"

//-----------------------------------------------------------------------------
// UAV
//-----------------------------------------------------------------------------
RW_STRUCTURED_BUFFER(output, Voxel, SLOT_UAV_IMAGE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
void PS(PSInputPositionNormalTexture input) {
	
	// [m] * [voxels/m] * [1/voxels]
	const float3 relative = input.p_view * g_voxel_grid_inv_size 
		                                 * g_voxel_grid_inv_resolution;
	// [-1,1]^3 -> [0,1]x[1,0]x[0,1]
	const float3 uvw    = relative * float3(0.5f, -0.5f, 0.5f) + 0.5f;
	// [0,R)x(R,0]x[0,R)
	const uint3 index   = floor(uvw * g_voxel_grid_resolution);

	[branch]
	if (any(index < 0u || index > g_voxel_grid_resolution)) {
		return;
	}

	// Obtain the base color of the material.
	const float4 base_color = GetMaterialBaseColor(input.tex);
	
	clip(base_color.w - TRANSPARENCY_THRESHOLD);

	// Obtain the material parameters [roughness, metalness] of the material.
	const float2 material   = GetMaterialParameters(input.tex);
	// Obtain the view-space normal.
	const float3 n_view     = GetNormal(input.p_view, input.n_view, input.tex2);

	// Calculate the pixel radiance.
	const float3 L = BRDFShading(input.p_view, n_view, 
		                         base_color.xyz, material.x, material.y);

	const uint flat_index = FlattenIndex(index, uint2(g_voxel_grid_resolution, 
		                                              g_voxel_grid_resolution));

	// Store the encoded radiance and normal.
	InterlockedMax(output[flat_index].encoded_L, EncodeRadiance(L));
	InterlockedMax(output[flat_index].encoded_n, EncodeNormal(n_view));
}