//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// DISABLE_BASE_COLOR_TEXTURE               | not defined
// DISABLE_MATERIAL_TEXTURE                 | not defined
// DISABLE_TSNM                             | not defined
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
// MSAA_AS_SSAA                             | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "forward\forward_input.hlsli"
#include "lighting.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
#ifdef MSAA_AS_SSAA
OMInputForward PS(PSInputPositionNormalTexture input, 
				  uint index : SV_SampleIndex) {
#else  // MSAA_AS_SSAA
OMInputForward PS(PSInputPositionNormalTexture input) {
#endif // MSAA_AS_SSAA

	// Obtain the base color of the material.
	const float4 base_color = GetMaterialBaseColor(input.tex);

	#ifdef ENABLE_TRANSPARENCY
	clip(base_color.w - TRANSPARENCY_SKIP_THRESHOLD);
	#else  // ENABLE_TRANSPARENCY
	clip(base_color.w - TRANSPARENCY_THRESHOLD);
	#endif // ENABLE_TRANSPARENCY

	// Obtain the material parameters [roughness, metalness] of the material.
	const float2 material = GetMaterialParameters(input.tex);
	// Obtain the view-space normal.
	const float3 n_view = GetNormal(input.p_view, input.n_view, input.tex2);

	// Calculate the pixel radiance.
	const float3 L = GetRadiance(input.p_view, n_view,
		                         base_color.xyz, material.x, material.y);

	OMInputForward output;
	// Store the color.
	output.color = float4(L, base_color.w);
	// Pack and store the view-space normal.
	#pragma warning( push )
	#pragma warning( disable : 3578 ) // Partial initialization.
	output.normal.xyz = PackNormal(n_view);
	#pragma warning( pop )
								
	return output;
}