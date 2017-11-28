//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// GROUP_SIZE                             | GROUP_SIZE_DEFAULT (CS only)
// DISSABLE_DIFFUSE_BRDF                  | not defined
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
// MSAA                                   | not defined (PS only)

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "deferred\deferred_input.hlsli"
#include "lighting.hlsli"

#ifdef MSAA

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------

float4 PS(PSInputNDCPosition input, uint index : SV_SampleIndex) : SV_Target {

	const uint2 location = input.p.xy;

	// Obtain the base color of the material.
	const float3 base_color = GetGBufferMaterialBaseColor(location, index);
	// Obtain the parameters of the material.
	const float2 material   = GetGBufferMaterialParameters(location, index);
	// Obtain the view-space normal.
	const float3 n_view     = GetGBufferNormal(location, index);
	// Obtain the view-space hit position.
	const float3 p_view     = GetGBufferPosition(location, index, input.p_ndc.xy);

	// Calculate the pixel radiance.
	const float3 L = BRDFShading(p_view, n_view, 
		                         base_color, material.x, material.y);

	return float4(L, 1.0f);
}

#else  // MSAA

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------

float4 PS(PSInputNDCPosition input) : SV_Target {

	const uint2 location = input.p.xy;

	// Obtain the base color of the material.
	const float3 base_color = GetGBufferMaterialBaseColor(location);
	// Obtain the parameters of the material.
	const float2 material   = GetGBufferMaterialParameters(location);
	// Obtain the view-space normal.
	const float3 n_view     = GetGBufferNormal(location);
	// Obtain the view-space hit position.
	const float3 p_view     = GetGBufferPosition(location, input.p_ndc.xy);

	// Calculate the pixel radiance.
	const float3 L = BRDFShading(p_view, n_view, 
		                         base_color, material.x, material.y);

	return float4(L, 1.0f);
}

//-----------------------------------------------------------------------------
// Compute Shader
//-----------------------------------------------------------------------------

// MSAA_AS_SSAA is not possible for deferred shading in the compute shader 
// without knowing the positioning of the subpixels inside the pixel.

#ifndef GROUP_SIZE
#define GROUP_SIZE GROUP_SIZE_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 location = g_ss_viewport_top_left + thread_id.xy;
	if (any(location >= g_ss_display_resolution)) {
		return;
	}

	// Obtain the base color of the material.
	const float3 base_color = GetGBufferMaterialBaseColor(location);
	// Obtain the parameters of the material.
	const float2 material   = GetGBufferMaterialParameters(location);
	// Obtain the view-space normal.
	const float3 n_view     = GetGBufferNormal(location);
	// Obtain the view-space hit position.
	const float2 p_ndc_xy   = SSDispatchThreadIDtoNDC(thread_id.xy);
	const float3 p_view     = GetGBufferPosition(location, p_ndc_xy);

	// Calculate the pixel radiance.
	const float3 L = BRDFShading(p_view, n_view, 
		                         base_color, material.x, material.y);

	// Store the pixel color.
	g_output[location] = float4(L, 1.0f);
}

#endif // MSAA