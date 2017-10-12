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
 Tone map the given radiance value using Reinhard's tone mapping.

 @param[in]		L
				The radiance value (in linear space).
 @return		The tone mapped radiance value.
 */
float3 ToneMap_Reinhard(float3 L) {
	return L / (1.0f + L);
}

#endif //MAGE_HEADER_TONE_MAPPIN