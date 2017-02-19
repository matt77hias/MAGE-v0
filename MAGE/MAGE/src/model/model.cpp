//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// SubModel
	//-------------------------------------------------------------------------

	SubModel::SubModel(const SubModel &submodel)
		: m_name(submodel.m_name), m_start_index(submodel.m_start_index), m_nb_indices(submodel.m_nb_indices),
		m_transform(new Transform(*submodel.m_transform)) {

		for (set< SubModel * >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			AddChild(new SubModel(**it));
		}
	}

	void SubModel::AddChild(SubModel *child) {
		Assert(child);
		Assert(child != this);
		m_transform->AddChild(child->m_transform);
		m_childs.insert(child);
	}

	void SubModel::RemoveAllChilds() {
		set< SubModel * >::iterator it = m_childs.begin();
		while (it != m_childs.end()) {
			delete (*it);
			it = m_childs.erase(it);
		}
	}

	void SubModel::Update(ComPtr< ID3D11DeviceContext2 > device_context) const {
		device_context->DrawIndexed((UINT)GetNumberOfIndices(), (UINT)GetStartIndex(), 0);

		for (set< SubModel * >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			(*it)->Update(device_context);
		}
	}
}