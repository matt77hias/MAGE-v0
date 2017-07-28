//-----------------------------------------------------------------------------
// Input structures
//-----------------------------------------------------------------------------

struct VSInputPosition {
	float4 p     : POSITION0;
};

struct VSInputPositionNormal {
	float4 p     : POSITION0;
	float3 n     : NORMAL0;
};

struct VSInputPositionColor {
	float4 p     : POSITION0;
	float4 color : COLOR0;
};

struct VSInputPositionTexture {
	float4 p     : POSITION0;
	float2 tex   : TEXCOORD0;
};

struct VSInputPositionNormalColor {
	float4 p     : POSITION0;
	float3 n     : NORMAL0;
	float4 color : COLOR0;
};

struct VSInputPositionNormalTexture {
	float4 p     : POSITION0;
	float3 n     : NORMAL0;
	float2 tex   : TEXCOORD0;
};

struct VSInputPositionColorTexture {
	float4 p     : POSITION0;
	float4 color : COLOR0;
	float2 tex   : TEXCOORD0;
};

struct VSInputPositionNormalColorTexture {
	float4 p     : POSITION0;
	float3 n     : NORMAL0;
	float4 color : COLOR0;
	float2 tex   : TEXCOORD0;
};

struct VSInputPositionTextureTexture {
	float4 p     : POSITION0;
	float2 tex1  : TEXCOORD0;
	float2 tex2  : TEXCOORD1;
};