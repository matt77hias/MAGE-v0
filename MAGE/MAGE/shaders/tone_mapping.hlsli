#ifndef MAGE_HEADER_TONE_MAPPING
#define MAGE_HEADER_TONE_MAPPING

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 Calculates the luminance of the given RGB color.

 @param[in]		rgb
				The RGB color.
 @return		The luminance of the given RGB color.
 */
float Luminance(float3 rgb) {
	return max(dot(rgb, float3(0.212671f, 0.715160f, 0.072169f)), 0.0001f);
}

/**
 Tone map the given HDR radiance value using Reinhard's tone mapping.

 @param[in]		hdr
				The HDR radiance value.
 @return		The tone mapped LDR radiance value.
 */
float3 HDRtoLDR(float3 hdr) {
	return hdr / (1.0f + hdr);
}

/**
 Tone map the given HDR radiance value using Reinhard's tone mapping.

 @param[in]		hdr
				The HDR radiance value.
 @return		The tone mapped LDR radiance value.
 @note			The alpha channel of the given RGBA spectrum is preserved.
 */
float4 HDRtoLDR(float4 hdr) {
	return float4(HDRtoLDR(hdr.xyz), hdr.w);
}

/**
 Inversely one map the given LDR radiance value using Reinhard's tone mapping.

 @param[in]		ldr
				The LDR radiance value.
 @return		The tone mapped HDR radiance value.
 */
float3 LDRtoHDR(float3 ldr) {
	return ldr / (1.0f - ldr);
}

/**
 Inversely one map the given LDR radiance value using Reinhard's tone mapping.

 @param[in]		ldr
				The LDR radiance value.
 @return		The tone mapped HDR radiance value.
 @note			The alpha channel of the given RGBA spectrum is preserved.
 */
float4 LDRtoHDR(float4 ldr) {
	return float4(LDRtoHDR(ldr.xyz), ldr.w);
}

#endif //MAGE_HEADER_TONE_MAPPIN