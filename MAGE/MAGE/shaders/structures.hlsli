#ifndef MAGE_HEADER_STRUCTURES
#define MAGE_HEADER_STRUCTURES

//-----------------------------------------------------------------------------
// VS Input Structures
//-----------------------------------------------------------------------------

/**
 A vertex shader input struct of vertices having 
 a position.
 */
struct VSInputPosition {
	float3 p      : POSITION0;
};

/**
 A vertex shader input struct of vertices having 
 a position and normal.
 */
struct VSInputPositionNormal {
	float3 p      : POSITION0;
	float3 n      : NORMAL0;
};

/**
 A vertex shader input struct of vertices having 
 a position and color.
 */
struct VSInputPositionColor {
	float3 p      : POSITION0;
	float4 color  : COLOR0;
};

/**
 A vertex shader input struct of vertices having 
 a position and a pair of texture coordinates.
 */
struct VSInputPositionTexture {
	float3 p      : POSITION0;
	float2 tex    : TEXCOORD0;
};

/**
 A vertex shader input struct of vertices having 
 a position, normal and color.
 */
struct VSInputPositionNormalColor {
	float3 p      : POSITION0;
	float3 n      : NORMAL0;
	float4 color  : COLOR0;
};

/**
 A vertex shader input struct of vertices having 
 a position, normal and a pair of texture coordinates.
 */
struct VSInputPositionNormalTexture {
	float3 p      : POSITION0;
	float3 n      : NORMAL0;
	float2 tex    : TEXCOORD0;
};

/**
 A vertex shader input struct of vertices having 
 a position, color and a pair of texture coordinates.
 */
struct VSInputPositionColorTexture {
	float3 p      : POSITION0;
	float4 color  : COLOR0;
	float2 tex    : TEXCOORD0;
};

/**
 A vertex shader input struct of vertices having 
 a position, normal, color and a pair of texture coordinates.
 */
struct VSInputPositionNormalColorTexture {
	float3 p      : POSITION0;
	float3 n      : NORMAL0;
	float4 color  : COLOR0;
	float2 tex    : TEXCOORD0;
};

/**
 A vertex shader input struct of vertices having 
 a position and two pairs of texture coordinates.
 */
struct VSInputPositionTextureTexture {
	float3 p      : POSITION0;
	float2 tex    : TEXCOORD0;
	float2 tex2   : TEXCOORD1;
};

//-----------------------------------------------------------------------------
// PS Input Structures
//-----------------------------------------------------------------------------

// SV_POSITION is always included. 
// Therefore, it is not reflected in the struct naming.

/**
 A pixel shader input struct of fragments having
 a position and NDC space position.
 */
struct PSInputNDCPosition {
	float4 p      : SV_POSITION;
	float2 p_ndc  : POSITION0;
};

/**
 A pixel shader input struct of fragments having
 a position, color and a pair of texture coordinates.
 */
struct PSInputColorTexture {
	float4 p      : SV_POSITION;
	float4 color  : COLOR0;
	float2 tex    : TEXCOORD0;
};

/**
 A pixel shader input struct of fragments having
 a position, view-space position and view-space normal,
 a pair of material and a pair of geometry texture coordinates.
 */
struct PSInputPositionNormalTexture {
	float4 p      : SV_POSITION;
	float3 p_view : POSITION0;
	float3 n_view : NORMAL0;
	float2 tex    : TEXCOORD0;
	float2 tex2   : TEXCOORD1;
};

//-----------------------------------------------------------------------------
// OM Input Structures
//-----------------------------------------------------------------------------

/**
 A ouput merger input struct of fragments having
 a normal, diffuse and specular component.
 */
struct OMInputDeferred {
	float4 diffuse  : SV_Target0;
	float4 specular : SV_Target1;
	float4 normal   : SV_Target2;
};

#endif // MAGE_HEADER_STRUCTURES