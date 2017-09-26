//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const D3D11_INPUT_ELEMENT_DESC VertexPosition::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	static_assert(sizeof(VertexPosition) == 12, 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormal::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_NORMAL,	  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	static_assert(sizeof(VertexPositionNormal) == 24, 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionColor::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_COLOR,    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	static_assert(sizeof(VertexPositionColor) == 28, 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionTexture::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_TEXTURE,  0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	static_assert(sizeof(VertexPositionTexture) == 20, 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalColor::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_NORMAL,	  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_COLOR,    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	static_assert(sizeof(VertexPositionNormalColor) == 40, 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalTexture::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_NORMAL,	  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_TEXTURE,  0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	static_assert(sizeof(VertexPositionNormalTexture) == 32, 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionColorTexture::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_COLOR,    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_TEXTURE,  0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	static_assert(sizeof(VertexPositionColorTexture) == 36, 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalColorTexture::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_NORMAL,	  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_COLOR,    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_TEXTURE,  0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	static_assert(sizeof(VertexPositionNormalColorTexture) == 48, 
		"Vertex struct/layout mismatch");

	const D3D11_INPUT_ELEMENT_DESC VertexPositionTextureTexture::s_input_element_desc[] = {
		{ MAGE_VERTEX_SEMANTIC_NAME_POSITION, 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_TEXTURE,  0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ MAGE_VERTEX_SEMANTIC_NAME_TEXTURE,  1, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	static_assert(sizeof(VertexPositionTextureTexture) == 28, 
		"Vertex struct/layout mismatch");
}