//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// GROUP_SIZE                               | GROUP_SIZE_2D_DEFAULT (CS only)
// ENABLE_TRANSPARENCY                      | not defined
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
// DISABLE_AMBIENT_LIGHT                    | not defined
// DISABLE_DIRECTIONAL_LIGHTS               | not defined
// DISABLE_OMNI_LIGHTS                      | not defined
// DISABLE_SPOT_LIGHTS                      | not defined
// DISABLE_SHADOW_MAPPING                   | not defined
// DISABLE_SHADOW_MAPPED_DIRECTIONAL_LIGHTS | not defined
// DISABLE_SHADOW_MAPPED_OMNI_LIGHTS        | not defined
// DISABLE_SHADOW_MAPPED_SPOT_LIGHTS        | not defined
// DISABLE_FOG                              | not defined
// DISABLE_VCT                              | not defined
// MSAA                                     | not defined (PS only)

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "deferred\deferred_input.hlsli"
#include "lighting.hlsli"

#ifdef MSAA

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------

float4 PS(float4 input : SV_POSITION, uint index : SV_SampleIndex) : SV_Target {
	const uint2 p_ss_display = input.xy;

	// Obtain the base color of the material.
	const float3 base_color = GetGBufferMaterialBaseColor(p_ss_display, index);
	// Obtain the parameters of the material.
	const float2 material   = GetGBufferMaterialParameters(p_ss_display, index);
	// Obtain the surface normal expressed in world space.
	const float3 n_world    = GetGBufferNormal(p_ss_display, index);
	// Obtain the surface position expressed in world space.
	const float3 p_view     = GetGBufferPosition(p_ss_display, index);

	// Calculate the pixel radiance.
	const float3 L = GetRadiance(p_world, n_world,
		                         base_color, material.x, material.y);
	return float4(L, 1.0f);
}

#else  // MSAA

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------

float4 PS(float4 input : SV_POSITION) : SV_Target {
	const uint2 p_ss_display = input.xy;

	// Obtain the base color of the material.
	const float3 base_color = GetGBufferMaterialBaseColor(p_ss_display);
	// Obtain the parameters of the material.
	const float2 material   = GetGBufferMaterialParameters(p_ss_display);
	// Obtain the surface normal expressed in world space.
	const float3 n_world    = GetGBufferNormal(p_ss_display);
	// Obtain the surface position expressed in world space.
	const float3 p_world    = GetGBufferPosition(p_ss_display);

	// Calculate the pixel radiance.
	const float3 L = GetRadiance(p_world, n_world,
		                         base_color, material.x, material.y);
	return float4(L, 1.0f);
}

//-----------------------------------------------------------------------------
// Compute Shader
//-----------------------------------------------------------------------------

// MSAA_AS_SSAA is not possible for deferred shading in the compute shader 
// without knowing the positioning of the subpixels inside the pixel.

#ifndef GROUP_SIZE
	#define GROUP_SIZE GROUP_SIZE_2D_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 p_ss_display = g_ss_viewport_top_left + thread_id.xy;
	
	[branch]
	if (any(p_ss_display >= g_ss_display_resolution)) {
		return;
	}

	// Obtain the base color of the material.
	const float3 base_color = GetGBufferMaterialBaseColor(p_ss_display);
	// Obtain the parameters of the material.
	const float2 material   = GetGBufferMaterialParameters(p_ss_display);
	// Obtain the surface normal expressed in world space.
	const float3 n_world    = GetGBufferNormal(p_ss_display);
	// Obtain the surface position expressed in world space.
	const float3 p_world    = GetGBufferPosition(p_ss_display);

	// Calculate the pixel radiance.
	const float3 L = GetRadiance(p_world, n_world,
		                         base_color, material.x, material.y);
	// Store the pixel color.
	g_output[location] = float4(L, 1.0f);
}

#endif // MSAA