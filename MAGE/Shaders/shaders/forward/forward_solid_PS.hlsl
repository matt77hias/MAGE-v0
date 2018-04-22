//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// DISABLE_LIGHTS_DIRECTIONAL               | not defined
// DISABLE_LIGHTS_OMNI                      | not defined
// DISABLE_LIGHTS_SPOT                      | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED             | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED_DIRECTIONAL | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED_OMNI        | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED_SPOT        | not defined
// DISABLE_LIGHT_AMBIENT                    | not defined
// LIGHT_ANGULAR_ATTENUATION_FUNCTION       | AngularAttenuation
// LIGHT_DISTANCE_ATTENUATION_FUNCTION      | DistanceAttenuation
// MSAA_AS_SSAA                             | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------

#define DISABLE_TEXTURE_BASE_COLOR
#define DISABLE_TEXTURE_MATERIAL
#define DISABLE_TSNM
#include "forward\forward_input.hlsli"

#define BRDF_FUNCTION LambertianBRDF
#define DISABLE_FOG
#define DISABLE_VCT
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
	const float3 base_color = 1.0f;
	// Obtain the material parameters [roughness, metalness] of the material.
	const float2 material_params = GetMaterialParameters(input.tex_material);
	// Obtain the surface normal expressed in world space.
	const float3 n_world = GetNormal(input.p_world, input.n_world, 
									 input.tex_geometry);

	Material material;
	material.base_color = base_color.xyz;
	material.roughness  = material_params.x;
	material.metalness  = material_params.y;

	// Calculate the pixel radiance.
	const float3 L = GetRadiance(input.p_world, n_world, material);

	OMInputForward output;
	// Store the radiance.
	output.color = float4(L, 1.0f);
	// Pack and store the normal.
	#pragma warning( push )
	#pragma warning( disable : 3578 ) // Partial initialization.
	output.n.xy  = NORMAL_ENCODE_FUNCTION(n_world);
	#pragma warning( pop )
								
	return output;
}