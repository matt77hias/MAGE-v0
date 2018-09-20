//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// BRDF_DOT_EPSILON                         | 1e-5f
// BRDF_D_FUNCTION                          | D_GGX
// BRDF_F_FUNCTION                          | F_Schlick
// BRDF_FUNCTION                            | not defined
// BRDF_MINIMUM_ALPHA                       | 1e-1f
// BRDF_V_FUNCTION                          | G_GXX
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
// GROUP_SIZE                               | GROUP_SIZE_2D_DEFAULT (CS only)
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

	const Material material = {
		base_color,
		material_params.x,
		material_params.y
	};

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

	const Material material = {
		base_color,
		material_params.x,
		material_params.y
	};

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

	const uint2 p_ss_viewport = thread_id.xy;
	uint2 p_ss_display;

	[branch]
	if (IsSSViewportOutOfBounds(p_ss_viewport, p_ss_display)) {
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

	const Material material = {
		base_color,
		material_params.x,
		material_params.y
	};

	// Calculate the pixel radiance.
	const float3 L = GetRadiance(p_world, n_world, material);

	// Store the pixel color.
	g_output[p_ss_display] = float4(L, 1.0f);
}

#endif // MSAA