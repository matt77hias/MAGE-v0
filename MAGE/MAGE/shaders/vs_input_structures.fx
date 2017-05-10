//-----------------------------------------------------------------------------
// Input structures
//-----------------------------------------------------------------------------

struct VertexPosition_VS_INPUT {
	float4 p     : POSITION;
};

struct VertexPositionNormal_VS_INPUT {
	float4 p     : POSITION;
	float3 n     : NORMAL0;
};

struct VertexPositionColor_VS_INPUT {
	float4 p     : POSITION;
	float4 color : COLOR0;
};

struct VertexPositionTexture_VS_INPUT {
	float4 p     : POSITION;
	float2 tex   : TEXCOORD0;
};

struct VertexPositionNormalColor_VS_INPUT {
	float4 p     : POSITION;
	float3 n     : NORMAL0;
	float4 color : COLOR0;
};

struct VertexPositionNormalTexture_VS_INPUT {
	float4 p     : POSITION;
	float3 n     : NORMAL0;
	float2 tex   : TEXCOORD0;
};

struct VertexPositionColorTexture_VS_INPUT {
	float4 p     : POSITION;
	float4 color : COLOR0;
	float2 tex   : TEXCOORD0;
};

struct VertexPositionNormalColorTexture_VS_INPUT {
	float4 p     : POSITION;
	float3 n     : NORMAL0;
	float4 color : COLOR0;
	float2 tex   : TEXCOORD0;
};

struct VertexPositionTextureTexture_VS_INPUT {
	float4 p     : POSITION;
	float2 tex1  : TEXCOORD0;
	float2 tex2  : TEXCOORD1;
};