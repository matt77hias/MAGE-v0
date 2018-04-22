#ifndef MAGE_HEADER_VOXEL
#define MAGE_HEADER_VOXEL

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "color.hlsli"
#include "normal.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

struct Voxel {
	uint encoded_L;
	uint encoded_n;
};

uint EncodeRadiance(float3 L) {
	return PackR8G8B8A8(RGBtoLogLuv(L));
}

float3 DecodeRadiance(uint encoded_L) {
	return LogLuvToRGB(UnpackR8G8B8A8(encoded_L));
}

uint EncodeNormal(float3 n) {
	return PackR16G16(EncodeNormal_Octahedron(n));
}

float3 DecodeNormal(uint encoded_n) {
	return DecodeNormal_Octahedron(UnpackR16G16(encoded_n));
}

#endif // MAGE_HEADER_VOXEL