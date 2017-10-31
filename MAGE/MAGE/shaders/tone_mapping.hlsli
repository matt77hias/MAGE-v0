#ifndef MAGE_HEADER_TONE_MAPPING
#define MAGE_HEADER_TONE_MAPPING

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// TONE_MAP_COMPONENT                     | ToneMap_Reinhard
// INVERSE_TONE_MAP_COMPONENT             | InverseToneMap_Reinhard

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

float4 ToneMap_Reinhard(float4 hdr) {
	return float4(ToneMap_Reinhard(hdr.xyz), hdr.w);
}

float3 InverseToneMap_Reinhard(float3 ldr) {
	return ldr / (1.0f - ldr);
}

float4 InverseToneMap_Reinhard(float4 ldr) {
	return float4(InverseToneMap_Reinhard(ldr.xyz), ldr.w);
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

#ifndef TONE_MAP_COMPONENT
#define TONE_MAP_COMPONENT ToneMap_Reinhard
#endif // TONE_MAP_COMPONENT

#ifndef INVERSE_TONE_MAP_COMPONENT
#define INVERSE_TONE_MAP_COMPONENT InverseToneMap_Reinhard
#endif // INVERSE_TONE_MAP_COMPONENT

#endif //MAGE_HEADER_TONE_MAPPIN