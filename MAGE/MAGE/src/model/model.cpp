//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Model
	//-------------------------------------------------------------------------

	Model::Model(const Model &model)
		: WorldObject(model) {

		for (set< SubModel * >::const_iterator it = m_submodels.cbegin(); it != m_submodels.cend(); ++it) {
			AddSubModel((*it)->Clone());
		}
	}

	void Model::AddSubModel(SubModel *submodel) {
		Assert(submodel);
		AddChildTransform(*submodel);
		m_submodels.insert(submodel);
	}

	SubModel *Model::GetSubModel(const string &name) const {
		for (set< SubModel * >::const_iterator it = m_submodels.cbegin(); it != m_submodels.cend(); ++it) {
			if ((*it)->GetName() == name) {
				return (*it);
			}
		}
		return nullptr;
	}

	//-------------------------------------------------------------------------
	// SubModel
	//-------------------------------------------------------------------------

	SubModel::SubModel(const SubModel &submodel)
		: Model(submodel), m_material(new ShadedMaterial(*submodel.m_material)) {}
}