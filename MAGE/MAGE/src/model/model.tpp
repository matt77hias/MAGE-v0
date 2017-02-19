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
	// Model
	//-------------------------------------------------------------------------

	template < typename Vertex >
	Model< Vertex >::Model(ComPtr< ID3D11Device2 > device, const wstring &fname, const MeshDescriptor &desc, const string &name)
		: m_name(name), m_transform(new Transform()) {
	
		const HRESULT result_initialization = InitializeModel(device, fname, desc);
		if (FAILED(result_initialization)) {
			Error("Model initialization failed: %ld.", result_initialization);
			return;
		}
	}

	template < typename Vertex >
	Model< Vertex >::Model(const Model< Vertex > &model)
		: m_name(model.m_name), m_mesh(model.m_mesh), m_transform(new Transform(*model.m_transform)) {
	
		for (set< SubModel * >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			AddChild(new SubModel(**it));
		}
	}

	template < typename Vertex >
	void Model< Vertex >::AddChild(SubModel *child) {
		Assert(child);
		m_transform->AddChild(child->m_transform);
		m_childs.insert(child);
	}

	template < typename Vertex >
	void Model< Vertex >::RemoveAllChilds() {
		set< SubModel * >::iterator it = m_childs.begin();
		while (it != m_childs.end()) {
			delete (*it);
			it = m_childs.erase(it);
		}
	}

	template < typename Vertex >
	void Model< Vertex >::Update(ComPtr< ID3D11DeviceContext2 > device_context) const {
		m_mesh->Update(device_context);

		for (set< SubModel * >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			(*it)->Update(device_context);
		}
	}

	template < typename Vertex >
	HRESULT Model< Vertex >::InitializeModel(ComPtr< ID3D11Device2 > device, const wstring &fname, const MeshDescriptor &desc) {
		ModelOutput< Vertex > output;
		const HRESULT result_load = LoadModelFromFile< Vertex >(fname, output, desc);
		if (FAILED(result_load)) {
			Error("Model loading failed: %ld.", result_load);
			return result_load;
		}

		m_mesh = SharedPtr< Mesh< Vertex > >(new Mesh< Vertex >(device, fname, output.vertex_buffer, output.index_buffer));

		map< string, pair< SubModel *, string > > mapping;
		for (vector< ModelPart >::const_iterator it = output.model_parts.cbegin(); it != output.model_parts.cend(); ++it) {
			if (it->child == MAGE_MODEL_PART_DEFAULT_CHILD && it->nb_indices == 0) {
				continue;
			}
			SubModel *submodel = new SubModel(it->child, it->start_index, it->nb_indices);
			mapping[it->child] = pair< SubModel *, string >(submodel, it->parent);
		}
		for (map< string, pair< SubModel *, string > >::const_iterator it = mapping.cbegin(); it != mapping.cend(); ++it) {
			const pair< SubModel *, string > &element = it->second;
			const string &parent = element.second;
			if (parent == MAGE_MODEL_PART_DEFAULT_PARENT) {
				AddChild(element.first);
			}
			else {
				mapping[parent].first->AddChild(element.first);
			}
		}
			
		return S_OK;
	}
}