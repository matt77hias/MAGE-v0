//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// LIGHT_DISTANCE_ATTENUATION_COMPONENT     | DistanceAttenuation
// LIGHT_ANGULAR_ATTENUATION_COMPONENT      | AngularAttenuation
// DISABLE_AMBIENT_LIGHT                    | not defined
// DISABLE_DIRECTIONAL_LIGHTS               | not defined
// DISABLE_OMNI_LIGHTS                      | not defined
// DISABLE_SPOT_LIGHTS                      | not defined
// DISABLE_SHADOW_MAPPING                   | not defined
// DISABLE_SHADOW_MAPPED_DIRECTIONAL_LIGHTS | not defined
// DISABLE_SHADOW_MAPPED_OMNI_LIGHTS        | not defined
// DISABLE_SHADOW_MAPPED_SPOT_LIGHTS        | not defined
// MSAA_AS_SSAA                             | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------

#define DISABLE_BASE_COLOR_TEXTURE
#define DISABLE_MATERIAL_TEXTURE
#define DISABLE_TSNM
#include "forward\forward_input.hlsli"

#define BRDFxCOS_COMPONENT LambertianBRDFxCos
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
	const float2 material   = GetMaterialParameters(input.tex_material);
	// Obtain the surface normal expressed in world space.
	const float3 n_world    = GetNormal(input.p_world, input.n_world, 
										input.tex_geometry);

	// Calculate the pixel radiance.
	const float3 L = GetRadiance(input.p_world, n_world,
		                         base_color, material.x, material.y);

	OMInputForward output;
	// Store the radiance.
	output.color = float4(L, 1.0f);
	// Pack and store the normal.
	#pragma warning( push )
	#pragma warning( disable : 3578 ) // Partial initialization.
	output.n.xyz = PackNormal(n_world);
	#pragma warning( pop )
								
	return output;
}