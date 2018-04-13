#ifndef MAGE_HEADER_VOXEL
#define MAGE_HEADER_VOXEL

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "color.hlsli"
#include "math.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

struct Voxel {
	uint encoded_L;
	uint encoded_n;
};

static const float g_max_length = 1.0f;

uint EncodeRadiance(float3 L) {
	return PackR8G8B8A8(RGBtoLogLuv(L));
}

float3 DecodeRadiance(uint encoded_L) {
	return LogLuvToRGB(UnpackR8G8B8A8(encoded_L));
}

uint EncodeNormal(float3 n) {
	static const float3 f_to_i = float3(1023.0f, 511.0f, 1023.0f);

	// [-1,1]^3 -> [-1023,1023]x[-511,511]x[-1023,1023]
	const int3  normal      = int3(n * f_to_i);
	const uint3 normal_sign = min(sign(normal), 0u);
	const uint3 normal_size = abs(normal);

	// |.:.......|...:.:....|.....:.:..|........|
	// |s|     x     |s|     y    |s|     z     |
	const uint encoded_n = (normal_sign.x << 31u)
		                 | (normal_size.x << 21u)
		                 | (normal_sign.y << 20u)
		                 | (normal_size.y << 11u)
		                 | (normal_sign.z << 10u)
		                 |  normal_size.z;
	return encoded_n;
}

float3 DecodeNormal(uint encoded_n) {
	static const float3 i_to_f = float3(1.0f / 1023.0f, 
										1.0f /  511.0f, 
										1.0f / 1023.0f);

	const uint3 normal_sign = 0x1 & uint3(encoded_n >> 31u,
		                                  encoded_n >> 20u,
		                                  encoded_n >> 10u);
	const uint3 normal_size = uint3(0x3FF, 0x1FF, 0x3FF)
		                    & uint3(encoded_n >> 21u,
		                            encoded_n >> 11u,
		                            encoded_n);
	
	// [-1023,1023]x[-511,511]x[-1023,1023]
	const int3 normal = (2*int3(normal_sign)-1) * normal_size;
	// [-1023,1023]x[-511,511]x[-1023,1023] -> [-1,1]^3
	const float3 n = normal * i_to_f;

	return normalize(n);
}

#endif // MAGE_HEADER_VOXEL