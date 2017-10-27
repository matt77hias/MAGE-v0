//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#define DISSABLE_DIFFUSE_BRDF
#include "forward\forward_input.hlsli"
#include "voxel.hlsli"
#include "lighting.hlsli"

//TODO move to buffer
static const float3 g_voxel_grid_center = 0.0f;
static const float  g_voxel_grid_size = 1.0f;
static const float  g_voxel_grid_inv_size = 1.0f;
static const uint   g_voxel_grid_resolution = 256u;
static const float  g_voxel_grid_inv_resolution = 1.0f / 256.0f; // pixel/texel size

//-----------------------------------------------------------------------------
// UAV
//-----------------------------------------------------------------------------

RW_STRUCTURED_BUFFER(output, Voxel, SLOT_UAV_IMAGE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
void PS(PSInputPositionNormalTexture input) {
	
	// [m] * [voxels/m]
	const int3 index = floor((input.p_view - g_voxel_grid_center) 
		                     * g_voxel_grid_inv_size);
	
	[branch]
	if (any(index < 0 || index > (int3)g_voxel_grid_resolution)) {
		return;
	}

	// Obtain the base color of the material.
	const float4 base_color = GetMaterialBaseColor(input.tex);
	
	//TODO: less conservative?
	clip(base_color.w - TRANSPARENCY_THRESHOLD);

	// Obtain the material parameters [roughness, metalness] of the material.
	const float2 material   = GetMaterialParameters(input.tex);
	// Obtain the view-space normal.
	const float3 n_view     = GetNormal(input.p_view, input.n_view, input.tex2);

	// Calculate the pixel radiance.
	const float3 L = BRDFShading(input.p_view, n_view, 
		                         base_color.xyz, material.x, material.y);

	const uint flat_index = FlattenIndex((uint3)index, g_voxel_grid_resolution);

	//TODO: encoding
	const uint color_mask  = 0;
	const uint normal_mask = 0;

	InterlockedMax(output[flat_index].color_mask,  color_mask);
	InterlockedMax(output[flat_index].normal_mask, normal_mask);
}