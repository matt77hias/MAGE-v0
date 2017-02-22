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
	
	//-------------------------------------------------------------------------
	// MeshModel
	//-------------------------------------------------------------------------

	template < typename Vertex >
	MeshModel< Vertex >::MeshModel(const string &name, ComPtr< ID3D11Device2 > device, const wstring &fname, const MeshDescriptor &desc, const CombinedShader &shader)
		: Model(name) {

		ModelOutput< Vertex > buffer;
		const HRESULT result_load = LoadModelFromFile< Vertex >(fname, buffer, desc);
		if (FAILED(result_load)) {
			Error("Model loading failed: %ld.", result_load);
			return;
		}

		const HRESULT result_initialization = InitializeModel(device, buffer, shader);
		if (FAILED(result_initialization)) {
			Error("Model initialization failed: %ld.", result_initialization);
			return;
		}
	}

	template < typename Vertex >
	MeshModel< Vertex >::MeshModel(const string &name, ComPtr< ID3D11Device2 > device, ModelOutput< Vertex > &buffer, const CombinedShader &shader)
		: Model(name) {
	
		const HRESULT result_initialization = InitializeModel(device, buffer, shader);
		if (FAILED(result_initialization)) {
			Error("Model initialization failed: %ld.", result_initialization);
			return;
		}
	}

	template < typename Vertex >
	HRESULT MeshModel< Vertex >::InitializeModel(ComPtr< ID3D11Device2 > device, ModelOutput< Vertex > &buffer, const CombinedShader &shader) {
		m_mesh = SharedPtr< Mesh< Vertex > >(new Mesh< Vertex >(device, buffer.vertex_buffer, buffer.index_buffer));

		map< string, pair< SubModel *, string > > mapping;
		for (vector< ModelPart >::const_iterator it = buffer.model_parts.cbegin(); it != buffer.model_parts.cend(); ++it) {
			if (it->child == MAGE_MODEL_PART_DEFAULT_CHILD && it->nb_indices == 0) {
				continue;
			}
			
			Material material;
			if (it->material != MAGE_MODEL_PART_DEFAULT_MATERIAL) {
				for (vector< Material >::const_iterator mit = buffer.material_buffer.cbegin(); mit != buffer.material_buffer.cend(); ++mit) {
					if (mit->m_name == it->child) {
						material = *mit;
						break;
					}
				}
			}
			ShadedMaterial shaded_material(shader, material);
			
			SubModel *submodel = new MeshSubModel(it->child, it->start_index, it->nb_indices, shaded_material);
			mapping[it->child] = pair< SubModel *, string >(submodel, it->parent);
		}
		for (map< string, pair< SubModel *, string > >::const_iterator it = mapping.cbegin(); it != mapping.cend(); ++it) {
			const pair< SubModel *, string > &element = it->second;
			const string &parent = element.second;
			if (parent == MAGE_MODEL_PART_DEFAULT_PARENT) {
				AddSubModel(element.first);
			}
			else {
				mapping[parent].first->AddSubModel(element.first);
			}
		}
			
		return S_OK;
	}
}