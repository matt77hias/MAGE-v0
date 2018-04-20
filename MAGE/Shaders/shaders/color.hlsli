#ifndef MAGE_HEADER_COLOR
#define MAGE_HEADER_COLOR

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: (linear) RGB <-> Gamma
//-----------------------------------------------------------------------------

/**
 Converts the given spectrum from linear to gamma space.

 @param[in]		color
				The spectrum in linear space.
 @param[in]		inv_gamma
				The inverse of the gamma exponent.
 @return		The spectrum in gamma space.
 */
float3 LinearToGamma(float3 color, float inv_gamma) {
	return pow(abs(color), inv_gamma);
}

/**
 Converts the given spectrum from linear to gamma space.

 @param[in]		color
				The spectrum in linear space.
 @param[in]		inv_gamma
				The inverse of the gamma exponent.
 @return		The spectrum in gamma space.
 @note			The alpha channel of the given spectrum is preserved.
 */
float4 LinearToGamma(float4 color, float inv_gamma) {
	return float4(LinearToGamma(color.xyz, inv_gamma), color.w);
}

/**
 Converts the given spectrum from gamma to linear space.

 @param[in]		color
				The spectrum in gamma space.
 @param[in]		gamma
				The gamma exponent.
 @return		The spectrum in linear space.
 */
float3 GammaToLinear(float3 color, float gamma) {
	return pow(abs(color), gamma);
}

/**
 Converts the given spectrum from gamma to linear space.

 @param[in]		color
				The spectrum in gamma space.
 @param[in]		gamma
				The gamma exponent.
 @return		The spectrum in linear space.
 @note			The alpha channel of the given spectrum is preserved.
 */
float4 GammaToLinear(float4 color, float gamma) {
	return float4(GammaToLinear(color.xyz, gamma), color.w);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: (linear) RGB <-> sRGB
//-----------------------------------------------------------------------------

/**
 Converts the given spectrum from (linear) RGB to sRGB space.

 @param[in]		rgb
				The spectrum in (linear) RGB space.
 @return		The spectrum in sRGB space.
 */
float3 RGBtoSRGB_Approximate(float3 rgb) {
	return LinearToGamma(rgb, 1.0f / 2.2f);
}

/**
 Converts the given spectrum from (linear) RGB to sRGB space.

 @param[in]		rgb
				The spectrum in (linear) RGB space.
 @return		The spectrum in sRGB space.
 @note			The alpha channel of the given spectrum is preserved.
 */
float4 RGBtoSRGB_Approximate(float4 rgb) {
	return float4(RGBtoSRGB_Approximate(rgb.xyz), rgb.w);
}

/**
 Converts the given spectrum from sRGB to (linear) RGB space.

 @param[in]		srgb
				The spectrum in sRGB space.
 @return		The spectrum in (linear) RGB space.
 */
float3 SRGBtoRGB_Approximate(float3 srgb) {
	return GammaToLinear(srgb, 2.2f);
}

/**
 Converts the given spectrum from sRGB to (linear) RGB space.

 @param[in]		srgb
				The spectrum in sRGB space.
 @return		The spectrum in (linear) RGB space.
 @note			The alpha channel of the given spectrum is preserved.
 */
float4 SRGBtoRGB_Approximate(float4 srgb) {
	return float4(SRGBtoRGB_Approximate(srgb.xyz), srgb.w);
}

/**
 Converts the given spectrum from (linear) RGB to sRGB space.

 @param[in]		rgb
				The spectrum in (linear) RGB space.
 @return		The spectrum in sRGB space.
 */
float3 RGBtoSRGB_Accurate(float3 rgb) {
	const float3 low  = rgb * 12.92f;
	const float3 high = LinearToGamma(rgb, 1.0f / 2.4f) * 1.055f - 0.055f;
	return (0.0031308f >= rgb) ? low : high;
}

/**
 Converts the given spectrum from (linear) RGB to sRGB space.

 @param[in]		rgb
				The spectrum in (linear) RGB space.
 @return		The spectrum in sRGB space.
 @note			The alpha channel of the given spectrum is preserved.
 */
float4 RGBtoSRGB_Accurate(float4 rgb) {
	return float4(RGBtoSRGB_Accurate(rgb.xyz), rgb.w);
}

/**
 Converts the given spectrum from sRGB to (linear) RGB space.

 @param[in]		srgb
				The spectrum in sRGB space.
 @return		The spectrum in (linear) RGB space.
 */
float3 SRGBtoRGB_Accurate(float3 srgb) {
	static const float mlow  = 1.0f / 12.92f;
	static const float mhigh = 1.0f / 1.055f;

	const float3 low  = srgb * mlow;
	const float3 high = GammaToLinear((srgb + 0.055f) * mhigh, 2.4f);
	return (0.04045f >= srgb) ? low : high;
}

/**
 Converts the given spectrum from sRGB to (linear) RGB space.

 @param[in]		srgb
				The spectrum in sRGB space.
 @return		The spectrum in (linear) RGB space.
 @note			The alpha channel of the given spectrum is preserved.
 */
float4 SRGBtoRGB_Accurate(float4 srgb) {
	return float4(SRGBtoRGB_Accurate(srgb.xyz), srgb.w);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: (linear) RGB <-> LogLuv
//-----------------------------------------------------------------------------

/**
 Converts the given spectrum from (linear) RGB to LogLuv space.

 @param[in]		rgb
				The spectrum in (linear) RGB space.
 @return		The spectrum in LogLuv space.
 */
float4 RGBtoLogLuv(float3 rgb) {
	static const float3x3 s_rgb_to_x1yd1 
		= float3x3(0.22088889f, 0.339f, 0.41843111f, 
				   0.11377778f, 0.678f, 0.73187556f, 
				   0.01022222f, 0.113f, 0.29691111f);

	const float3 x1yd1  = max(mul(rgb, s_rgb_to_x1yd1), 1e-6f);
	const float2 uv     = x1yd1.xy / x1yd1.z;
	const float  L      = 2.0f * log2(x1yd1.y) + 127.0f;
	const float  L_low  = frac(L);
	const float  L_high = (L - floor(L_low * 255.0f) / 255.0f) / 255.0f;
	
	return float4(L_high, L_low, uv);
}

/**
 Converts the given spectrum from LogLuv to (linear) RGB space.

 @param[in]		logluv
				The spectrum in LogLuv space.
 @return		The spectrum in (linear) RGB space.
 */
float3 LogLuvToRGB(float4 logluv) {
	static const float3x3 s_x1yd1_to_rgb 
		= float3x3( 6.00157563f, -2.70063025f, -1.80094538f, 
				   -1.33085447f,  3.10225329f, -5.77139883f, 
				    0.29987802f, -1.08769314f,  5.62652480f);

	const float  L = 255.0f * logluv.x + logluv.y;
	float3 x1yd1;
	x1yd1.y = exp2((L - 127.0f) * 0.5f);
	x1yd1.z = x1yd1.y / logluv.w;
	x1yd1.x = logluv.z * x1yd1.z;
	
	return max(mul(x1yd1, s_x1yd1_to_rgb), 0.0f);
}

#endif // MAGE_HEADER_COLOR