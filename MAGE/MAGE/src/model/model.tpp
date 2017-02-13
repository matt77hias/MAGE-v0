#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename Vertex >
	Model< Vertex >::Model(const string &name, ComPtr< ID3D11Device2 > device, const string &fname, const MeshDescriptor &desc)
		: m_name(name), m_transform(UniquePtr< Transform >(new Transform())) {
	
		const HRESULT result_initialization = InitializeModel(device, fname, desc);
		if (FAILED(result_initialization)) {
			Error("Model initialization failed: %ld.", result_initialization);
			return;
		}
	}

	template < typename Vertex >
	Model< Vertex >::Model(const Model< Vertex > &model) 
		: m_name(model.m_name) {
		
		//@TODO: transform
	}

	template < typename Vertex >
	void Model< Vertex >::Update(ComPtr< ID3D11DeviceContext2 > device_context) const {
		m_mesh->Update(device_context);

		device_context->DrawIndexed((UINT)m_mesh->GetNumberOfIndices(), 0, 0);
	}

	template < typename Vertex >
	HRESULT Model< Vertex >::InitializeModel(ComPtr< ID3D11Device2 > device, const string &fname, const MeshDescriptor &desc) {
		ModelOutput< Vertex > output;
		const HRESULT result_load = LoadModelFromFile< Vertex >(fname, output, desc);
		if (FAILED(result_load)) {
			Error("Model loading failed: %ld.", result_load);
			return result_load;
		}

		m_mesh = make_unique< Mesh< Vertex > >(device, output.vertex_buffer, output.index_buffer);

		//@TODO: transform
		return S_OK;
	}

}