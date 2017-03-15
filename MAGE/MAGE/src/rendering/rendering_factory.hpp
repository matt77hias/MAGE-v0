#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	HRESULT CreateVertexBuffer(ComPtr< ID3D11Device2 > device, ID3D11Buffer **buffer, const VertexT *vertices, size_t nb_vertices);

	template < typename IndexT >
	HRESULT CreateIndexBuffer(ComPtr< ID3D11Device2 > device, ID3D11Buffer **buffer, const IndexT *indices, size_t nb_indices);

	template < typename BufferT >
	HRESULT CreateConstantBuffer(ComPtr< ID3D11Device2 > device, ID3D11Buffer **buffer);

	HRESULT CreateLinearSamplerState(ComPtr< ID3D11Device2 > device, ID3D11SamplerState **sampler_state);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.tpp"

#pragma endregion