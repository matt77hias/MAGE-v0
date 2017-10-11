//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerFrame, SLOT_CBUFFER_PER_FRAME) {
	// CAMERA
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection      : packoffset(c0);
};

CBUFFER(PerDraw, SLOT_CBUFFER_PER_DRAW) {
	// TRANSFORM
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view          : packoffset(c0);
	// The object-to-view inverse transpose transformation matrix
	// = The normal-to-view transformation matrix.
	float4x4 g_normal_to_view          : packoffset(c4);
	// The texture transformation matrix.
	float4x4 g_texture_transform       : packoffset(c8);

	// MATERIAL
	// The base color of the material.
	float4 g_base_color                : packoffset(c12);
	// The roughness of the material.
	float  g_roughness                 : packoffset(c13.x);
	// The metalness of the material.
	float  g_metalness                 : packoffset(c13.y);
}

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_base_color_texture, float4, SLOT_SRV_BASE_COLOR);
TEXTURE_2D(g_material_texture,   float4, SLOT_SRV_MATERIAL);
TEXTURE_2D(g_normal_texture,     float3, SLOT_SRV_NORMAL);