//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerFrame, SLOT_CBUFFER_PER_FRAME) {
	// CAMERA
	// The projection-to-view transformation matrix.
	float4x4 g_projection_to_view : packoffset(c0);
};

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_base_color_texture, float4, SLOT_SRV_BASE_COLOR);
TEXTURE_2D(g_material_texture,   float4, SLOT_SRV_MATERIAL);
TEXTURE_2D(g_normal_texture,     float3, SLOT_SRV_NORMAL);
TEXTURE_2D(g_depth_texture,      float,  SLOT_SRV_DEPTH);

//-----------------------------------------------------------------------------
// UAVs
//-----------------------------------------------------------------------------
RW_TEXTURE_2D(g_output,          float4, SLOT_UAV_IMAGE);

//-----------------------------------------------------------------------------
// Definitions and Declarations
//-----------------------------------------------------------------------------

/**
 Returns the base color of the material from the GBuffer corresponding to the 
 given location.

 @param[in]		location
				The location.
 @return		The base color of the material from the GBuffer corresponding 
				to the given location.
 */
float3 GetGBufferMaterialBaseColor(float2 location) {
	// Load the base color from the GBuffer base color texture.
	return g_base_color_texture[location].xyz;
}

/**
 Returns the parameters of the material from the GBuffer corresponding to the 
 given location.

 @param[in]		location
				The location.
 @return		The parameters of the material [roughness, metalness] from the 
				GBuffer corresponding to the given location.
 */
float2 GetGBufferMaterialParameters(float2 location) {
	// Load the material data the GBuffer material texture.
	return g_material_texture[location].xy;
}

/**
 Returns the view-space normal from the GBuffer corresponding to the given 
 location.

 @param[in]		location
				The location.
 @return		The view-space normal from the GBuffer corresponding to the 
				given location.
 */
float3 GetGBufferNormal(float2 location) {
	// Load and unpack the view-space normal from the GBuffer normal texture.
	return UnpackNormal(g_normal_texture[location]);
}

/**
 Returns the view-space position from the GBuffer corresponding to the given 
 location.

 @param[in]		p_ndc_xy
				The x and y coordinates of the NDC-space hit position.
 @param[in]		location
				The location.
 @return		The view-space position from the GBuffer corresponding to the 
				given location.
 */
float3 GetGBufferPosition(float2 location, float2 p_ndc_xy) {
	// Load the depth from the GBuffer depth texture.
	const float  depth  = g_depth_texture[location];
	// Obtain the projection space coodinates.
	const float4 p_proj = float4(p_ndc_xy, depth, 1.0f);
	// Obtain the view space coodinates.
	const float4 p_view = mul(p_proj, g_projection_to_view);
	const float  inv_p_view_w = 1.0f / p_view.w;
	return p_view.xyz * inv_p_view_w;
}