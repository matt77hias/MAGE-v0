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
	Model< Vertex >::Model(const string &name, const wstring &fname, const MeshDescriptor &desc, ComPtr< ID3D11Device2 > device)
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
	
		for (set< SubModel< Vertex > * >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			AddChild(new SubModel< Vertex >(**it));
		}
	}

	template < typename Vertex >
	void Model< Vertex >::AddChild(SubModel< Vertex > *child) {
		Assert(child);
		m_transform->AddChild(child->m_transform);
		m_childs.insert(child);
	}

	template < typename Vertex >
	void Model< Vertex >::RemoveAllChilds() {
		set< SubModel< Vertex > * >::iterator it = m_childs.begin();
		while (it != m_childs.end()) {
			delete (*it);
			it = m_childs.erase(it);
		}
	}

	template < typename Vertex >
	void Model< Vertex >::Update(ComPtr< ID3D11DeviceContext2 > device_context) const {
		m_mesh->Update(device_context);

		for (set< SubModel< Vertex > * >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
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

		m_mesh = SharedPtr< Mesh< Vertex > >(new Mesh< Vertex >(fname, output.vertex_buffer, output.index_buffer, device));

		map< string, pair< SubModel< Vertex > *, string > > mapping;
		for (vector< ModelPart >::const_iterator it = output.model_parts.cbegin(); it != output.model_parts.cend(); ++it) {
			if (it->child == MAGE_MODEL_PART_DEFAULT_CHILD && it->nb_indices == 0) {
				continue;
			}
			SubModel< Vertex > *submodel = new SubModel< Vertex >(it->child, it->start_index, it->nb_indices);
			mapping[it->child] = pair< SubModel< Vertex > *, string >(submodel, it->parent);
		}
		for (map< string, pair< SubModel< Vertex > *, string > >::const_iterator it = mapping.cbegin(); it != mapping.cend(); ++it) {
			const pair< SubModel< Vertex > *, string > &element = it->second;
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

	//-------------------------------------------------------------------------
	// SubModel
	//-------------------------------------------------------------------------

	template < typename Vertex >
	SubModel< Vertex >::SubModel(const SubModel< Vertex > &submodel)
		: m_name(submodel.m_name), m_start_index(submodel.m_start_index), m_nb_indices(submodel.m_nb_indices),
		m_transform(new Transform(*submodel.m_transform)) {

		for (set< SubModel< Vertex > * >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			AddChild(new SubModel< Vertex >(**it));
		}
	}

	template < typename Vertex >
	void SubModel< Vertex >::AddChild(SubModel< Vertex > *child) {
		Assert(child);
		Assert(child != this);
		m_transform->AddChild(child->m_transform);
		m_childs.insert(child);
	}

	template < typename Vertex >
	void SubModel< Vertex >::RemoveAllChilds() {
		set< SubModel< Vertex > * >::iterator it = m_childs.begin();
		while (it != m_childs.end()) {
			delete (*it);
			it = m_childs.erase(it);
		}
	}

	template < typename Vertex >
	void SubModel< Vertex >::Update(ComPtr< ID3D11DeviceContext2 > device_context) const {
		device_context->DrawIndexed((UINT)GetNumberOfIndices(), (UINT)GetStartIndex(), 0);

		for (set< SubModel< Vertex > * >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			(*it)->Update(device_context);
		}
	}
}