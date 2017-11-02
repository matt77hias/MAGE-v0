//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// MSAA_AS_SSAA                           | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
#ifdef MSAA_AS_SSAA
TEXTURE_2D_MS(g_base_color_texture, float4, SLOT_SRV_BASE_COLOR);
TEXTURE_2D_MS(g_material_texture,   float4, SLOT_SRV_MATERIAL);
TEXTURE_2D_MS(g_normal_texture,     float3, SLOT_SRV_NORMAL);
TEXTURE_2D_MS(g_depth_texture,      float,  SLOT_SRV_DEPTH);
#else  // MSAA_AS_SSAA
TEXTURE_2D(g_base_color_texture,    float4, SLOT_SRV_BASE_COLOR);
TEXTURE_2D(g_material_texture,      float4, SLOT_SRV_MATERIAL);
TEXTURE_2D(g_normal_texture,        float3, SLOT_SRV_NORMAL);
TEXTURE_2D(g_depth_texture,         float,  SLOT_SRV_DEPTH);
#endif // MSAA_AS_SSAA

//-----------------------------------------------------------------------------
// UAVs
//-----------------------------------------------------------------------------
RW_TEXTURE_2D(g_output,             float4, SLOT_UAV_IMAGE);

//-----------------------------------------------------------------------------
// Definitions and Declarations
//-----------------------------------------------------------------------------

#ifdef MSAA_AS_SSAA

/**
 Returns the base color of the material from the GBuffer corresponding to the 
 given location.

 @param[in]		location
				The location.
 @param[in]		index
				The sample index.
 @return		The base color of the material from the GBuffer corresponding 
				to the given location.
 */
float3 GetGBufferMaterialBaseColor(uint2 location, uint index) {
	// Load the base color from the GBuffer base color texture.
	return g_base_color_texture.sample[index][location].xyz;
}

/**
 Returns the parameters of the material from the GBuffer corresponding to the 
 given location.

 @param[in]		location
				The location.
 @param[in]		index
				The sample index.
 @return		The parameters of the material [roughness, metalness] from the 
				GBuffer corresponding to the given location.
 */
float2 GetGBufferMaterialParameters(uint2 location, uint index) {
	// Load the material data the GBuffer material texture.
	return g_material_texture.sample[index][location].xy;
}

/**
 Returns the view-space normal from the GBuffer corresponding to the given 
 location.

 @param[in]		location
				The location.
 @param[in]		index
				The sample index.
 @return		The view-space normal from the GBuffer corresponding to the 
				given location.
 */
float3 GetGBufferNormal(uint2 location, uint index) {
	// Load and unpack the view-space normal from the GBuffer normal texture.
	return UnpackNormal(g_normal_texture.sample[index][location]);
}

/**
 Returns the view-space position from the GBuffer corresponding to the given 
 location.

 @param[in]		location
				The location.
 @param[in]		index
				The sample index.
 @param[in]		p_ndc_xy
				The x and y coordinates of the NDC-space hit position.
 @return		The view-space position from the GBuffer corresponding to the 
				given location.
 */
float3 GetGBufferPosition(uint2 location, uint index, float2 p_ndc_xy) {
	// Load the depth from the GBuffer depth texture.
	const float  depth  = g_depth_texture.sample[index][location];
	// Obtain the projection space coodinates.
	const float4 p_proj = float4(p_ndc_xy, depth, 1.0f);
	// Obtain the view space coodinates.
	const float4 p_view = mul(p_proj, g_projection_to_view);
	const float  inv_p_view_w = 1.0f / p_view.w;
	return p_view.xyz * inv_p_view_w;
}

#else  // MSAA_AS_SSAA

/**
 Returns the base color of the material from the GBuffer corresponding to the 
 given location.

 @param[in]		location
				The location.
 @return		The base color of the material from the GBuffer corresponding 
				to the given location.
 */
float3 GetGBufferMaterialBaseColor(uint2 location) {
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
float2 GetGBufferMaterialParameters(uint2 location) {
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
float3 GetGBufferNormal(uint2 location) {
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
float3 GetGBufferPosition(uint2 location, float2 p_ndc_xy) {
	// Load the depth from the GBuffer depth texture.
	const float  depth  = g_depth_texture[location];
	// Obtain the projection space coodinates.
	const float4 p_proj = float4(p_ndc_xy, depth, 1.0f);
	// Obtain the view space coodinates.
	const float4 p_view = mul(p_proj, g_projection_to_view);
	const float  inv_p_view_w = 1.0f / p_view.w;
	return p_view.xyz * inv_p_view_w;
}

#endif // MSAA_AS_SSAA