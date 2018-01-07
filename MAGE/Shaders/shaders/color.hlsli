#ifndef MAGE_HEADER_COLOR
#define MAGE_HEADER_COLOR

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Gamma Utilities
//-----------------------------------------------------------------------------

/**
 Converts the given spectrum from linear to gamma space.

 @param[in]		linear_color
				The spectrum in linear space.
 @param[in]		inv_gamma
				The inverse of the gamma exponent.
 @return		The spectrum in gamma space.
 */
float3 LinearToGamma(float3 linear_color, float inv_gamma) {
	return pow(abs(linear_color), inv_gamma);
}

/**
 Converts the given spectrum from linear to gamma space.

 @param[in]		linear_color
				The spectrum in linear space.
 @param[in]		inv_gamma
				The inverse of the gamma exponent.
 @return		The spectrum in gamma space.
 @note			The alpha channel of the given spectrum is preserved.
 */
float4 LinearToGamma(float4 linear_color, float inv_gamma) {
	return float4(LinearToGamma(linear_color.xyz, inv_gamma), linear_color.w);
}

/**
 Converts the given spectrum from gamma to linear space.

 @param[in]		gamma_color
				The spectrum in gamma space.
 @param[in]		gamma
				The gamma exponent.
 @return		The spectrum in linear space.
 */
float3 GammaToLinear(float3 gamma_color, float gamma) {
	return pow(abs(gamma_color), gamma);
}

/**
 Converts the given spectrum from gamma to linear space.

 @param[in]		gamma_color
				The spectrum in gamma space.
 @param[in]		gamma
				The gamma exponent.
 @return		The spectrum in linear space.
 @note			The alpha channel of the given spectrum is preserved.
 */
float4 GammaToLinear(float4 gamma_color, float gamma) {
	return float4(GammaToLinear(gamma_color.xyz, gamma), gamma_color.w);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: sRGB Utilities
//-----------------------------------------------------------------------------

/**
 Converts the given spectrum from linear to sRGB space.

 @param[in]		linear_color
				The spectrum in linear space.
 @return		The spectrum in sRGB space.
 */
float3 LinearToSRGB_Approximate(float3 linear_color) {
	return LinearToGamma(linear_color, 1.0f / 2.2f);
}

/**
 Converts the given spectrum from linear to sRGB space.

 @param[in]		linear_color
				The spectrum in linear space.
 @return		The spectrum in sRGB space.
 @note			The alpha channel of the given spectrum is preserved.
 */
float4 LinearToSRGB_Approximate(float4 linear_color) {
	return float4(LinearToSRGB_Approximate(linear_color.xyz), linear_color.w);
}

/**
 Converts the given spectrum from sRGB to linear space.

 @param[in]		srgb_color
				The spectrum in sRGB space.
 @return		The spectrum in linear space.
 */
float3 SRGBToLinear_Approximate(float3 srgb_color) {
	return GammaToLinear(srgb_color, 2.2f);
}

/**
 Converts the given spectrum from sRGB to linear space.

 @param[in]		srgb_color
				The spectrum in sRGB space.
 @return		The spectrum in linear space.
 @note			The alpha channel of the given spectrum is preserved.
 */
float4 SRGBToLinear_Approximate(float4 srgb_color) {
	return float4(SRGBToLinear_Approximate(srgb_color.xyz), srgb_color.w);
}

/**
 Converts the given spectrum from linear to sRGB space.

 @param[in]		linear_color
				The spectrum in linear space.
 @return		The spectrum in sRGB space.
 */
float3 LinearToSRGB_Accurate(float3 linear_color) {
	const float3 low  = linear_color * 12.92f;
	const float3 high = LinearToGamma(linear_color, 1.0f / 2.4f) * 1.055f - 0.055f;
	return (linear_color <= 0.0031308f) ? low : high;
}

/**
 Converts the given spectrum from linear to sRGB space.

 @param[in]		linear_color
				The spectrum in linear space.
 @return		The spectrum in sRGB space.
 @note			The alpha channel of the given spectrum is preserved.
 */
float4 LinearToSRGB_Accurate(float4 linear_color) {
	return float4(LinearToSRGB_Accurate(linear_color.xyz), linear_color.w);
}

/**
 Converts the given spectrum from sRGB to linear space.

 @param[in]		srgb_color
				The spectrum in sRGB space.
 @return		The spectrum in linear space.
 */
float3 SRGBToLinear_Accurate(float3 srgb_color) {
	static const float mlow  = 1.0f / 12.92f;
	static const float mhigh = 1.0f / 1.055f;

	const float3 low  = srgb_color * mlow;
	const float3 high = GammaToLinear((srgb_color + 0.055f) * mhigh, 2.4f);
	return (srgb_color <= 0.04045f) ? low : high;
}

/**
 Converts the given spectrum from sRGB to linear space.

 @param[in]		srgb_color
				The spectrum in sRGB space.
 @return		The spectrum in linear space.
 @note			The alpha channel of the given spectrum is preserved.
 */
float4 SRGBToLinear_Accurate(float4 srgb_color) {
	return float4(SRGBToLinear_Accurate(srgb_color.xyz), srgb_color.w);
}

#endif //MAGE_HEADER_COLOR