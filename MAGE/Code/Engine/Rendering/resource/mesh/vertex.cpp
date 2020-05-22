//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	namespace {
		constexpr const_zstring g_vertex_semantic_name_color    = "COLOR";
		constexpr const_zstring g_vertex_semantic_name_normal   = "NORMAL";
		constexpr const_zstring g_vertex_semantic_name_position = "POSITION";
		constexpr const_zstring g_vertex_semantic_name_texture  = "TEXCOORD";
	}

	const D3D11_INPUT_ELEMENT_DESC VertexPosition::s_input_element_descs[] = {
		{ g_vertex_semantic_name_position, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormal::s_input_element_descs[] = {
		{ g_vertex_semantic_name_position, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ g_vertex_semantic_name_normal,   0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	const D3D11_INPUT_ELEMENT_DESC VertexPositionColor::s_input_element_descs[] = {
		{ g_vertex_semantic_name_position, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ g_vertex_semantic_name_color,    0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	const D3D11_INPUT_ELEMENT_DESC VertexPositionTexture::s_input_element_descs[] = {
		{ g_vertex_semantic_name_position, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ g_vertex_semantic_name_texture,  0u, DXGI_FORMAT_R32G32_FLOAT,       0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalColor::s_input_element_descs[] = {
		{ g_vertex_semantic_name_position, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ g_vertex_semantic_name_normal,   0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ g_vertex_semantic_name_color,    0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalTexture::s_input_element_descs[] = {
		{ g_vertex_semantic_name_position, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ g_vertex_semantic_name_normal,   0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ g_vertex_semantic_name_texture,  0u, DXGI_FORMAT_R32G32_FLOAT,       0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	const D3D11_INPUT_ELEMENT_DESC VertexPositionColorTexture::s_input_element_descs[] = {
		{ g_vertex_semantic_name_position, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ g_vertex_semantic_name_color,    0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ g_vertex_semantic_name_texture,  0u, DXGI_FORMAT_R32G32_FLOAT,       0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalColorTexture::s_input_element_descs[] = {
		{ g_vertex_semantic_name_position, 0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ g_vertex_semantic_name_normal,   0u, DXGI_FORMAT_R32G32B32_FLOAT,    0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ g_vertex_semantic_name_color,    0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ g_vertex_semantic_name_texture,  0u, DXGI_FORMAT_R32G32_FLOAT,       0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};
}