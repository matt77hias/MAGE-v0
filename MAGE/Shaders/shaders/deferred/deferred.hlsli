//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// BRDF_DOT_EPSILON                         | 0.00001f
// BRDF_D_FUNCTION                          | D_GGX
// BRDF_FUNCTION                            | not defined
// BRDF_F_FUNCTION                          | F_Schlick
// BRDF_G_FUNCTION                          | G_GXX
// BRDF_MINIMUM_ALPHA                       | 0.1f
// DISABLE_BRDF_DIFFUSE                     | not defined
// DISABLE_BRDF_SPECULAR                    | not defined
// DISABLE_FOG                              | not defined
// DISABLE_LIGHTS_AMBIENT                   | not defined
// DISABLE_LIGHTS_DIRECTIONAL               | not defined
// DISABLE_LIGHTS_OMNI                      | not defined
// DISABLE_LIGHTS_SPOT                      | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED             | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED_DIRECTIONAL | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED_OMNI        | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED_SPOT        | not defined
// DISABLE_VCT                              | not defined
// FOG_FACTOR_FUNCTION                      | FogFactor_Exponential
// GROUP_SIZE                               | GROUP_SIZE_2D_DEFAULT (CS only)
// LIGHT_ANGULAR_ATTENUATION_FUNCTION       | AngularAttenuation
// LIGHT_DISTANCE_ATTENUATION_FUNCTION      | DistanceAttenuation
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

float4 PS(float4 input : SV_POSITION, 
		  uint index : SV_SampleIndex) : SV_Target {

	const float2 p_ss_display = input.xy;

	// Obtain the base color of the material.
	const float3 base_color = GetGBufferMaterialBaseColor(p_ss_display, index);
	// Obtain the parameters of the material.
	const float2 material_params = GetGBufferMaterialParameters(p_ss_display, index);
	// Obtain the surface normal expressed in world space.
	const float3 n_world = GetGBufferNormal(p_ss_display, index);
	// Obtain the surface position expressed in world space.
	const float3 p_world = GetGBufferPosition(p_ss_display, index);

	Material material;
	material.base_color = base_color;
	material.roughness  = material_params.x;
	material.metalness  = material_params.y;

	// Calculate the pixel radiance.
	const float3 L = GetRadiance(p_world, n_world, material);
	return float4(L, 1.0f);
}

#else  // MSAA

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------

float4 PS(float4 input : SV_POSITION) : SV_Target {
	const float2 p_ss_display = input.xy;

	// Obtain the base color of the material.
	const float3 base_color = GetGBufferMaterialBaseColor(p_ss_display);
	// Obtain the parameters of the material.
	const float2 material_params = GetGBufferMaterialParameters(p_ss_display);
	// Obtain the surface normal expressed in world space.
	const float3 n_world = GetGBufferNormal(p_ss_display);
	// Obtain the surface position expressed in world space.
	const float3 p_world = GetGBufferPosition(p_ss_display);

	Material material;
	material.base_color = base_color;
	material.roughness  = material_params.x;
	material.metalness  = material_params.y;

	// Calculate the pixel radiance.
	const float3 L = GetRadiance(p_world, n_world, material);
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

	// Texture2D::operator[] requires a uint2 index.
	// For the computation of p_ndc/p_world, a float2 is required.
	const float2 p_ss_viewport = (float2)thread_id.xy + 0.5f;
	const float2 p_ss_display  = SSViewportToSSDisplay(p_ss_viewport);
		
	[branch]
	if (any(0.0f > p_ss_display
			|| g_ss_display_resolution  <= (uint2)p_ss_display
			|| g_ss_viewport_resolution <= (uint2)p_ss_viewport)) {
		return;
	}

	// Obtain the base color of the material.
	const float3 base_color = GetGBufferMaterialBaseColor(p_ss_display);
	// Obtain the parameters of the material.
	const float2 material_params = GetGBufferMaterialParameters(p_ss_display);
	// Obtain the surface normal expressed in world space.
	const float3 n_world = GetGBufferNormal(p_ss_display);
	// Obtain the surface position expressed in world space.
	const float3 p_world = GetGBufferPosition(p_ss_display);

	Material material;
	material.base_color = base_color;
	material.roughness  = material_params.x;
	material.metalness  = material_params.y;

	// Calculate the pixel radiance.
	const float3 L = GetRadiance(p_world, n_world, material);
	// Store the pixel color.
	g_output[p_ss_display] = float4(L, 1.0f);
}

#endif // MSAA