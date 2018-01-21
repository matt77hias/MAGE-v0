//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_VERTEX_SEMANTIC_NAME_POSITION "POSITION"
#define MAGE_VERTEX_SEMANTIC_NAME_NORMAL   "NORMAL"
#define MAGE_VERTEX_SEMANTIC_NAME_COLOR    "COLOR"
#define MAGE_VERTEX_SEMANTIC_NAME_TEXTURE  "TEXCOORD"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const D3D11_INPUT_ELEMENT_DESC VertexPosition::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	static_assert(12 == sizeof(VertexPosition), 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormal::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ MAGE_VERTEX_SEMANTIC_NAME_NORMAL,	  0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	static_assert(24 == sizeof(VertexPositionNormal), 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionColor::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ MAGE_VERTEX_SEMANTIC_NAME_COLOR,    0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	static_assert(28 == sizeof(VertexPositionColor), 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionTexture::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ MAGE_VERTEX_SEMANTIC_NAME_TEXTURE,  0u, DXGI_FORMAT_R32G32_FLOAT,       0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	static_assert(20 == sizeof(VertexPositionTexture), 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalColor::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ MAGE_VERTEX_SEMANTIC_NAME_NORMAL,	  0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ MAGE_VERTEX_SEMANTIC_NAME_COLOR,    0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	static_assert(40 == sizeof(VertexPositionNormalColor), 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalTexture::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ MAGE_VERTEX_SEMANTIC_NAME_NORMAL,	  0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ MAGE_VERTEX_SEMANTIC_NAME_TEXTURE,  0u, DXGI_FORMAT_R32G32_FLOAT,       0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	static_assert(32 == sizeof(VertexPositionNormalTexture), 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionColorTexture::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ MAGE_VERTEX_SEMANTIC_NAME_COLOR,    0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ MAGE_VERTEX_SEMANTIC_NAME_TEXTURE,  0u, DXGI_FORMAT_R32G32_FLOAT,       0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	static_assert(36 == sizeof(VertexPositionColorTexture), 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalColorTexture::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ MAGE_VERTEX_SEMANTIC_NAME_NORMAL,	  0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ MAGE_VERTEX_SEMANTIC_NAME_COLOR,    0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ MAGE_VERTEX_SEMANTIC_NAME_TEXTURE,  0u, DXGI_FORMAT_R32G32_FLOAT,       0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	static_assert(48 == sizeof(VertexPositionNormalColorTexture), 
		"Vertex struct/layout mismatch");
}