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

float3 ToneMap_Reinhard(float3 hdr) {
	return hdr / (1.0f + hdr);
}

float3 ToneMap_ACESFilmic(float3 hdr) {
	static const float a = 2.51f;
	static const float b = 0.03f;
	static const float c = 2.43f;
	static const float d = 0.59f;
	static const float e = 0.14f;

	return (hdr * (a * hdr + b)) 
		 / (hdr * (c * hdr + d) + e);
}

float3 ToneMap_Uncharted(float3 hdr) {
	static const float a = 0.22f;
	static const float b = 0.30f;
	static const float c = 0.10f;
	static const float d = 0.20f;
	static const float e = 0.01f;
	static const float f = 0.30f;

	return ((hdr * (a * hdr + c * b) + d * e)
		  / (hdr * (a * hdr + b) + d * f)) - e / f;
}

#ifndef TONE_MAP
#define TONE_MAP ToneMap_Uncharted
#endif

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

#endif //MAGE_HEADER_TONE_MAPPIN