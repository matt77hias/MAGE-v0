//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "transform\transform.hlsli"

#define DISABLE_TEXTURE_BASE_COLOR
#define DISABLE_TEXTURE_MATERIAL
#define DISABLE_TSNM
#include "forward\forward_input.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(SecondaryCamera, SLOT_CBUFFER_SECONDARY_CAMERA) {

	/**
	 The world-to-camera transformation matrix.
	 */
	float4x4 g_world_to_camera2       : packoffset(c0);

	/**
	 The camera-to-projection transformation matrix.
	 */
	float4x4 g_camera2_to_projection2 : packoffset(c4);
}