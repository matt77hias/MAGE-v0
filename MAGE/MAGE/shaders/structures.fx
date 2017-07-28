//-----------------------------------------------------------------------------
// VS Input Structures
//-----------------------------------------------------------------------------

struct VSInputPosition {
	float4 m_p      : POSITION0;
};

struct VSInputPositionNormal {
	float4 m_p      : POSITION0;
	float3 m_n      : NORMAL0;
};

struct VSInputPositionColor {
	float4 m_p      : POSITION0;
	float4 m_color  : COLOR0;
};

struct VSInputPositionTexture {
	float4 m_p      : POSITION0;
	float2 m_tex    : TEXCOORD0;
};

struct VSInputPositionNormalColor {
	float4 m_p      : POSITION0;
	float3 m_n      : NORMAL0;
	float4 m_color  : COLOR0;
};

struct VSInputPositionNormalTexture {
	float4 m_p      : POSITION0;
	float3 m_n      : NORMAL0;
	float2 m_tex    : TEXCOORD0;
};

struct VSInputPositionColorTexture {
	float4 m_p      : POSITION0;
	float4 m_color  : COLOR0;
	float2 m_tex    : TEXCOORD0;
};

struct VSInputPositionNormalColorTexture {
	float4 m_p      : POSITION0;
	float3 m_n      : NORMAL0;
	float4 m_color  : COLOR0;
	float2 m_tex    : TEXCOORD0;
};

struct VSInputPositionTextureTexture {
	float4 m_p      : POSITION0;
	float2 m_tex1   : TEXCOORD0;
	float2 m_tex2   : TEXCOORD1;
};

//-----------------------------------------------------------------------------
// PS Input Structures
//-----------------------------------------------------------------------------

struct PSInputPositionColorTexture {
	float4 m_p      : SV_POSITION;
	float4 m_color  : COLOR0;
	float2 m_tex    : TEXCOORD0;
};

struct PSInputPositionNormalTexture {
	float4 m_p      : SV_POSITION;
	float4 m_p_view : POSITION0;
	float3 m_n_view : NORMAL0;
	float2 m_tex    : TEXCOORD0;
};