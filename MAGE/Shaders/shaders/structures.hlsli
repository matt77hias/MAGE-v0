#ifndef MAGE_HEADER_STRUCTURES
#define MAGE_HEADER_STRUCTURES

//-----------------------------------------------------------------------------
// VS Input Structures
//-----------------------------------------------------------------------------

/**
 A vertex shader input struct of vertices having a position.
 */
struct VSInputPosition {
	float3 p     : POSITION0;
};

/**
 A vertex shader input struct of vertices having a position and a normal.
 */
struct VSInputPositionNormal {
	float3 p     : POSITION0;
	float3 n     : NORMAL0;
};

/**
 A vertex shader input struct of vertices having a position and a color.
 */
struct VSInputPositionColor {
	float3 p     : POSITION0;
	float4 color : COLOR0;
};

/**
 A vertex shader input struct of vertices having a position and a pair of 
 texture coordinates.
 */
struct VSInputPositionTexture {
	float3 p     : POSITION0;
	float2 tex   : TEXCOORD0;
};

/**
 A vertex shader input struct of vertices having a position, a normal and a 
 color.
 */
struct VSInputPositionNormalColor {
	float3 p     : POSITION0;
	float3 n     : NORMAL0;
	float4 color : COLOR0;
};

/**
 A vertex shader input struct of vertices having a position, a normal and a 
 pair of texture coordinates.
 */
struct VSInputPositionNormalTexture {
	float3 p     : POSITION0;
	float3 n     : NORMAL0;
	float2 tex   : TEXCOORD0;
};

/**
 A vertex shader input struct of vertices having a position, a color and a 
 pair of texture coordinates.
 */
struct VSInputPositionColorTexture {
	float3 p     : POSITION0;
	float4 color : COLOR0;
	float2 tex   : TEXCOORD0;
};

/**
 A vertex shader input struct of vertices having a position, a normal, a color 
 and a pair of texture coordinates.
 */
struct VSInputPositionNormalColorTexture {
	float3 p     : POSITION0;
	float3 n     : NORMAL0;
	float4 color : COLOR0;
	float2 tex   : TEXCOORD0;
};

//-----------------------------------------------------------------------------
// GS Input Structures
//-----------------------------------------------------------------------------

/**
 A geometry shader input struct of vertices having a position and a normal 
 expressed in world space, and a pair of material and a pair of geometry texture 
 coordinates.
 */
struct GSInputPositionNormalTexture {
	float3 p_world      : POSITION0;
	float3 n_world      : NORMAL0;
	float2 tex_material : TEXCOORD0;
	float2 tex_geometry : TEXCOORD1;
};

//-----------------------------------------------------------------------------
// PS Input Structures
//-----------------------------------------------------------------------------

// The semantic SV_POSITION is always included and is, therefore, not reflected 
// in the naming of the struct identifier.

/**
 A pixel shader input struct of fragments having a position expressed in 
 viewport and world space.
 */
struct PSInputWorldPosition {
	float4 p            : SV_POSITION;
	float3 p_world      : POSITION0;
};

/**
 A pixel shader input struct of fragments having a position expressed in 
 viewport space and a pair of texture coordinates.
 */
struct PSInputTexture {
	float4 p            : SV_POSITION;
	float2 tex          : TEXCOORD0;
};

/**
 A pixel shader input struct of fragments having a position expressed in
 viewport space, a color and a pair of texture coordinates.
 */
struct PSInputColorTexture {
	float4 p            : SV_POSITION;
	float4 color        : COLOR0;
	float2 tex          : TEXCOORD0;
};

/**
 A pixel shader input struct of fragments having a position expressed in 
 viewport and world space, a normal expressed in world space, and a pair of 
 material and a pair of geometry texture coordinates.
 */
struct PSInputPositionNormalTexture {
	float4 p            : SV_POSITION;
	float3 p_world      : POSITION0;
	float3 n_world      : NORMAL0;
	float2 tex_material : TEXCOORD0;
	float2 tex_geometry : TEXCOORD1;
};

//-----------------------------------------------------------------------------
// OM Input Structures
//-----------------------------------------------------------------------------

/**
 An ouput merger input struct of fragments having a base color, a material and 
 a normal for deferred rendering.
 */
struct OMInputDeferred {
	float4 base_color : SV_Target0;
	float4 material   : SV_Target1;
	float4 n          : SV_Target2;
};

/**
 An ouput merger input struct of fragments having a color and normal for 
 forward rendering.
 */
struct OMInputForward {
	float4 color      : SV_Target0;
	float4 n          : SV_Target1;
};

#endif // MAGE_HEADER_STRUCTURES