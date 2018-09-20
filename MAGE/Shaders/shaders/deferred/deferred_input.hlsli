//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// MSAA                                     | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "normal.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
#ifdef MSAA
TEXTURE_2D_MS(g_base_color_texture, float4, SLOT_SRV_BASE_COLOR);
TEXTURE_2D_MS(g_material_texture,   float4, SLOT_SRV_MATERIAL);
TEXTURE_2D_MS(g_normal_texture,     float2, SLOT_SRV_NORMAL);
TEXTURE_2D_MS(g_depth_texture,      float,  SLOT_SRV_DEPTH);
#else  // MSAA
TEXTURE_2D(g_base_color_texture,    float4, SLOT_SRV_BASE_COLOR);
TEXTURE_2D(g_material_texture,      float4, SLOT_SRV_MATERIAL);
TEXTURE_2D(g_normal_texture,        float2, SLOT_SRV_NORMAL);
TEXTURE_2D(g_depth_texture,         float,  SLOT_SRV_DEPTH);
#endif // MSAA

//-----------------------------------------------------------------------------
// UAVs
//-----------------------------------------------------------------------------
RW_TEXTURE_2D(g_output,             float4, SLOT_UAV_IMAGE);

//-----------------------------------------------------------------------------
// Definitions and Declarations
//-----------------------------------------------------------------------------
#ifdef MSAA

/**
 Returns the base color of the material from the GBuffer corresponding to the
 given super-sampled display position.

 @param[in]		p_display
				The super-sampled display coordinates.
 @param[in]		index
				The sample index.
 @return		The base color of the material from the GBuffer corresponding
				to the given super-sampled display position.
 */
float3 GetGBufferMaterialBaseColor(uint2 p_ss_display, uint index) {
	// Load the base color from the GBuffer base color texture.
	return g_base_color_texture.sample[index][p_ss_display].xyz;
}

/**
 Returns the parameters of the material from the GBuffer corresponding to the
 given super-sampled display position.

 @param[in]		p_display
				The super-sampled display coordinates.
 @param[in]		index
				The sample index.
 @return		The parameters of the material [roughness, metalness] from the
				GBuffer corresponding to the given super-sampled display
				position.
 */
float2 GetGBufferMaterialParameters(uint2 p_ss_display, uint index) {
	// Load the material data the GBuffer material texture.
	return g_material_texture.sample[index][p_ss_display].xy;
}

/**
 Returns the surface normal from the GBuffer corresponding to the given
 super-sampled display position.

 @param[in]		p_display
				The super-sampled display coordinates.
 @param[in]		index
				The sample index.
 @return		The surface normal from the GBuffer expressed in world space
				corresponding to the given super-sampled display position.
 */
float3 GetGBufferNormal(uint2 p_ss_display, uint index) {
	// Load and unpack the view-space normal from the GBuffer normal texture.
	return NORMAL_DECODE_FUNCTION(g_normal_texture.sample[index][p_ss_display]);
}

/**
 Returns the surface position from the GBuffer corresponding to the given
 super-sampled display position.

 @param[in]		p_display
				The super-sampled display coordinates.
 @param[in]		index
				The sample index.
 @return		The surface position from the GBuffer expressed in world space
				corresponding to the given super-sampled display position.
 */
float3 GetGBufferPosition(uint2 p_ss_display, uint index) {
	// Load the depth from the GBuffer depth texture.
	const float depth = g_depth_texture.sample[index][p_ss_display];
	// Obtain the world space coodinates.
	const float3 p_camera = SSDisplayToCamera(p_ss_display, depth);
	return CameraToWorld(p_camera);
}

#else  // MSAA

/**
 Returns the base color of the material from the GBuffer corresponding to the
 given super-sampled display position.

 @param[in]		p_display
				The super-sampled display coordinates.
 @return		The base color of the material from the GBuffer corresponding
				to the given super-sampled display position.
 */
float3 GetGBufferMaterialBaseColor(uint2 p_ss_display) {
	// Load the base color from the GBuffer base color texture.
	return g_base_color_texture[p_ss_display].xyz;
}

/**
 Returns the parameters of the material from the GBuffer corresponding to the
 given super-sampled display position.

 @param[in]		p_display
				The super-sampled display coordinates.
 @return		The parameters of the material [roughness, metalness] from the
				GBuffer corresponding to the given super-sampled display
				position.
 */
float2 GetGBufferMaterialParameters(uint2 p_ss_display) {
	// Load the material data the GBuffer material texture.
	return g_material_texture[p_ss_display].xy;
}

/**
 Returns the surface normal from the GBuffer corresponding to the given
 super-sampled display position.

 @param[in]		p_display
				The super-sampled display coordinates.
 @return		The surface normal from the GBuffer expressed in world space
				corresponding to the given super-sampled display position.
 */
float3 GetGBufferNormal(uint2 p_ss_display) {
	// Load and unpack the view-space normal from the GBuffer normal texture.
	return NORMAL_DECODE_FUNCTION(g_normal_texture[p_ss_display]);
}

/**
 Returns the surface position from the GBuffer corresponding to the given
 super-sampled display position.

 @param[in]		p_display
				The super-sampled display coordinates.
 @return		The surface position from the GBuffer expressed in world space
				corresponding to the given super-sampled display position.
 */
float3 GetGBufferPosition(uint2 p_ss_display) {
	// Load the depth from the GBuffer depth texture.
	const float depth = g_depth_texture[p_ss_display];
	// Obtain the world space coodinates.
	const float3 p_camera = SSDisplayToCamera(p_ss_display, depth);
	return CameraToWorld(p_camera);
}

#endif // MSAA