#ifndef MAGE_HEADER_GLOBAL
#define MAGE_HEADER_GLOBAL

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "..\src\hlsl.hpp"
#include "hlsl_syntax.hlsli"
#include "math.hlsli"
#include "structures.hlsli"

//-----------------------------------------------------------------------------
// Samplers
//-----------------------------------------------------------------------------
SAMPLER_STATE(g_variable_sampler0,          SLOT_SAMPLER_VARIABLE_0);
SAMPLER_STATE(g_variable_sampler1,          SLOT_SAMPLER_VARIABLE_1);
SAMPLER_STATE(g_variable_sampler2,          SLOT_SAMPLER_VARIABLE_2);
SAMPLER_STATE(g_variable_sampler3,          SLOT_SAMPLER_VARIABLE_3);

SAMPLER_STATE(g_point_wrap_sampler,         SLOT_SAMPLER_POINT_WRAP);
SAMPLER_STATE(g_point_clamp_sampler,        SLOT_SAMPLER_POINT_CLAMP);
SAMPLER_STATE(g_point_mirror_sampler,       SLOT_SAMPLER_POINT_MIRROR);
SAMPLER_STATE(g_linear_wrap_sampler,        SLOT_SAMPLER_LINEAR_WRAP);
SAMPLER_STATE(g_linear_clamp_sampler,       SLOT_SAMPLER_LINEAR_CLAMP);
SAMPLER_STATE(g_linear_mirror_sampler,      SLOT_SAMPLER_LINEAR_MIRROR);
SAMPLER_STATE(g_anisotropic_wrap_sampler,   SLOT_SAMPLER_ANISOTROPIC_WRAP);
SAMPLER_STATE(g_anisotropic_clamp_sampler,  SLOT_SAMPLER_ANISOTROPIC_CLAMP);
SAMPLER_STATE(g_anisotropic_mirror_sampler, SLOT_SAMPLER_ANISOTROPIC_MIRROR);

SAMPLER_COMPARISON_STATE(g_pcf_sampler,     SLOT_SAMPLER_PCF);

//-----------------------------------------------------------------------------
// Constant Buffers 
//-----------------------------------------------------------------------------

CBUFFER(Game, SLOT_CBUFFER_GAME) {

	//-------------------------------------------------------------------------
	// Member Variables: Voxelization
	//-------------------------------------------------------------------------

	// The center of the voxel grid expressed in world space.
	float3   g_voxel_grid_center                 : packoffset(c0);
	// The resolution of the voxel grid for all dimensions.
	uint     g_voxel_grid_resolution             : packoffset(c1.x);
	// The inverse resolution of the voxel grid for all dimensions.
	float    g_voxel_grid_inv_resolution         : packoffset(c1.y);
	// The size of a voxel for all dimensions. [m/voxel]
	float    g_voxel_size                        : packoffset(c1.z);
	// The inverse size of a voxel for all dimensions. [voxels/m]
	float    g_voxel_inv_size                    : packoffset(c1.w);

	//-------------------------------------------------------------------------
	// Member Variables: Display Resolution
	//-------------------------------------------------------------------------

	// The resolution of the display.
	// g_display_resolution.x = the display width
	// g_display_resolution.y = the display height
	uint2  g_display_resolution                  : packoffset(c2);
	// The inverse of the resolution of the display minus 1.
	// g_display_inv_resolution_minus1.x = 1 / (g_display_resolution.x - 1)
	// g_display_inv_resolution_minus1.y = 1 / (g_display_resolution.y - 1)
	float2 g_display_inv_resolution_minus1       : packoffset(c2.z);
	// The resolution of the super-sampled display.
	// g_ss_display_resolution.x = the super-sampled display width
	// g_ss_display_resolution.y = the super-sampled display height
	uint2  g_ss_display_resolution               : packoffset(c3);
	// The inverse of the resolution of the super-sampled display minus 1.
	// g_ss_display_inv_resolution_minus1.x = 1 / (g_ss_display_resolution.x - 1)
	// g_ss_display_inv_resolution_minus1.y = 1 / (g_ss_display_resolution.y - 1)
	float2 g_ss_display_inv_resolution_minus1    : packoffset(c3.z);
};

CBUFFER(PrimaryCamera, SLOT_CBUFFER_PRIMARY_CAMERA) {
	
	//-------------------------------------------------------------------------
	// Member Variables: Transformations
	//-------------------------------------------------------------------------
	
	// The world-to-camera transformation matrix.
	float4x4 g_world_to_camera                   : packoffset(c0);
	// The camera-to-projection transformation matrix.
	float4x4 g_camera_to_projection              : packoffset(c4);
	// The projection-to-camera transformation matrix.
	float4x4 g_projection_to_camera              : packoffset(c8);
	// The camera-to-world transformation matrix.
	float4x4 g_camera_to_world                   : packoffset(c12);

	//-------------------------------------------------------------------------
	// Member Variables: Viewports
	//-------------------------------------------------------------------------

	// The top left corner of the camera viewport.
	uint2    g_viewport_top_left                 : packoffset(c16);
	// The resolution of the camera viewport.
	// g_viewport_resolution.x = the viewport width
	// g_viewport_resolution.y = the viewport height
	uint2    g_viewport_resolution               : packoffset(c16.z);
	// The top left corner of the super-sampled camera viewport.
	uint2    g_ss_viewport_top_left              : packoffset(c17);
	// The resolution of the super-sampled camera viewport.
	// g_ss_viewport_resolution.x = the super-sampled viewport width
	// g_ss_viewport_resolution.y = the super-sampled viewport height
	uint2    g_ss_viewport_resolution            : packoffset(c17.z);
	// The inverse of the resolution of the camera viewport minus 1.
	// g_viewport_inv_resolution_minus1.x = 1 / (g_viewport_resolution.x - 1)
	// g_viewport_inv_resolution_minus1.y = 1 / (g_viewport_resolution.y - 1)
	float2   g_viewport_inv_resolution_minus1    : packoffset(c18);
	// The inverse of the resolution of the super-sampled camera viewport minus 1.
	// g_ss_viewport_inv_resolution_minus1.x = 1 / (g_ss_viewport_resolution.x - 1)
	// g_ss_viewport_inv_resolution_minus1.y = 1 / (g_ss_viewport_resolution.y - 1)
	float2   g_ss_viewport_inv_resolution_minus1 : packoffset(c18.z);
	
	//-------------------------------------------------------------------------
	// Member Variables: Fog
	//-------------------------------------------------------------------------

	// The (linear) color of the fog.
	float3   g_fog_color                         : packoffset(c19);
	// The density of the fog.
	float    g_fog_density                       : packoffset(c19.w);

	//-------------------------------------------------------------------------
	// Member Variables: Sky
	//-------------------------------------------------------------------------

	// The scaling factor of the z component of sky domes.
	float    g_sky_dome_scale_z                  : packoffset(c20.x);

	//-------------------------------------------------------------------------
	// Member Variables: Post-processing
	//-------------------------------------------------------------------------

	// The lens radius of this camera.
	float    g_lens_radius                       : packoffset(c20.y);
	// The focal length of this camera.
	float    g_focal_length                      : packoffset(c20.z);
	// The maximum circle-of-confusion radius of this camera.
	float    g_max_coc_radius                    : packoffset(c20.w);

	//-------------------------------------------------------------------------
	// Member Variables: Gamma Correction
	//-------------------------------------------------------------------------

	// The inverse of the gamma exponent used for gamma correction.
	float    g_inv_gamma                         : packoffset(c21.x);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Transform Utilities
//-----------------------------------------------------------------------------

/**
 Returns the position of the camera expressed in world space.

 @return		The position of the camera expressed in world space.
 */
float3 GetCameraPosition() {
	return g_camera_to_world._m30_m31_m32;
}

/**
 Converts the given position expressed in world space to the corresponding 
 UVW coordinates.

 @param[in]		p_world
				the position expressed in world space.
 @return		The UVW coordinates.
 */
float3 WorldToVoxelUVW(float3 p_world) {
	const float3 voxel = (p_world - g_voxel_grid_center) * g_voxel_inv_size 
		               * g_voxel_grid_inv_resolution + 0.5f;
	return float3(0.0f, 1.0f, 0.0f) + float3(1.0f, -1.0f, 1.0f) * voxel;
}

/**
 Converts the given position expressed in world space to the corresponding 
 voxel index.

 @param[in]		p_world
				the position expressed in world space.
 @return		The voxel index.
 */
int3 WorldToVoxelIndex(float3 p_world) {
	const float3 voxel = (p_world - g_voxel_grid_center) * g_voxel_inv_size 
		               + 0.5f * g_voxel_grid_resolution;
	return int3(0, g_voxel_grid_resolution, 0) + int3(1, -1, 1) * floor(voxel);
}

/**
 Converts the given voxel index to the corresponding position expressed in 
 world space (i.e. left, lower, near corner of the voxel).

 @param[in]		p_world
				the position expressed in world space.
 @return		The voxel index.
 */
float3 VoxelIndexToWorld(uint3 voxel_index) {
	const uint3 voxel = int3(0, g_voxel_grid_resolution, 0) 
		              + int3(1, -1, 1) * (int3)voxel_index;
	return (voxel - 0.5f * g_voxel_grid_resolution) * g_voxel_size 
		   + g_voxel_grid_center;
}

/**
 Converts the given position expressed in NDC space to the corresponding 
 position expressed in world space.

 @param[in]		p_ndc
				The position expressed in NDC space.
 @return		The position expressed in world space.
 */
float3 NDCToWorld(float3 p_ndc) {
	const float4 p_hcamera = mul(float4(p_ndc, 1.0f), g_projection_to_camera);
	const float3 p_camera  = HomogeneousDivide(p_hcamera);
	return mul(float4(p_camera, 1.0f), g_camera_to_world).xyz;
}

/**
 Converts the given (non-linear) depth to the (linear) camera space.

 @param[in]		depth
				The (non-linear) depth.
 @return		The z coordinate expressed in camera space.
 */
float DepthToCameraZ(float depth) {
	const float2 p_camera_zw = mul(float4(0.0f, 0.0f, depth, 1.0f), 
								   g_projection_to_camera).zw;
	return p_camera_zw.x / p_camera_zw.y;
}

/**
 Converts the given display coordinates to UV coordinates.

 @param[in]		p_display
				The display coordinates.
 @return		The UV u and v coordinates.
 */
float2 DisplayToUV(float2 p_display) {
	// x: [0,g_display_resolution.x-1] -> [0,1]
	// y: [0,g_display_resolution.y-1] -> [0,1]
	return p_display * g_display_inv_resolution_minus1;
}

/**
 Converts the given super-sampled display coordinates to UV coordinates.

 @param[in]		p_ss_display
				The super-sampled display coordinates.
 @return		The UV u and v coordinates.
 */
float2 SSDisplayToUV(float2 p_ss_display) {
	// x: [0,g_ss_display_resolution.x-1] -> [0,1]
	// y: [0,g_ss_display_resolution.y-1] -> [0,1]
	return p_ss_display * g_ss_display_inv_resolution_minus1;
}

/**
 Converts the given viewport coordinates to UV coordinates.

 @param[in]		p_viewport
				The viewport coordinates.
 @return		The UV u and v coordinates.
 */
float2 ViewportToUV(float2 p_viewport) {
	// x: [0,g_viewport_resolution.x-1] -> [0,1]
	// y: [0,g_viewport_resolution.y-1] -> [0,1]
	return p_viewport * g_viewport_inv_resolution_minus1;
}

/**
 Converts the given super-sampled viewport coordinates to UV coordinates.

 @param[in]		p_ss_viewport
				The super-sampled viewport coordinates.
 @return		The UV u and v coordinates.
 */
float2 SSViewportToUV(float2 p_ss_viewport) {
	// x: [0,g_ss_viewport_resolution.x-1] -> [0,1]
	// y: [0,g_ss_viewport_resolution.y-1] -> [0,1]
	return p_ss_viewport * g_ss_viewport_inv_resolution_minus1;
}

/**
 Converts the given (viewport) dispatch thread id to NDC coordinates.

 @param[in]		id
				The (viewport) dispatch thread id.
 @return		The NDC coordinates.
 */
float2 DispatchThreadIDtoNDC(float2 id) {
	return UVtoNDC(ViewportToUV(id));
}

/**
 Converts the given (super-sampled viewport) dispatch thread id to NDC 
 coordinates.

 @param[in]		id
				The (super-sampled viewport) dispatch thread id.
 @return		The NDC coordinates.
 */
float2 SSDispatchThreadIDtoNDC(float2 id) {
	return UVtoNDC(SSViewportToUV(id));
}

#endif // MAGE_HEADER_GLOBAL