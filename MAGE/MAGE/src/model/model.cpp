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

	Model::Model(const string &name)
		: WorldObject(name) {}

	Model::Model(const Model &model)
		: WorldObject(model) {

		for (set< SubModel * >::const_iterator it = model.m_submodels.cbegin(); it != model.m_submodels.cend(); ++it) {
			AddSubModel((*it)->Clone());
		}
	}

	void Model::AddSubModel(SubModel *submodel) {
		Assert(submodel);
		m_submodels.insert(submodel);
		submodel->GetTransform().SetDirty();
	}

	SubModel *Model::GetSubModel(const string &name) const {
		for (set< SubModel * >::const_iterator it = m_submodels.cbegin(); it != m_submodels.cend(); ++it) {
			if ((*it)->GetName() == name) {
				return (*it);
			}
		}
		return nullptr;
	}

	void Model::UpdateChildTransforms(bool dirty_ancestor) {
		ForEachSubModel([&](SubModel &submodel) {
			submodel.UpdateTransform(
				GetTransform().GetWorldToObjectMatrix(), 
				GetTransform().GetObjectToWorldMatrix(),
				dirty_ancestor);
		});
	}

	//-------------------------------------------------------------------------
	// SubModel
	//-------------------------------------------------------------------------

	SubModel::SubModel(const string &name, size_t start_index, size_t nb_indices, const ShadedMaterial &material)
		: Model(name), m_start_index(start_index), m_nb_indices(nb_indices),
		m_material(new ShadedMaterial(material)) {}
	
	SubModel::SubModel(const SubModel &submodel) 
		: Model(submodel), m_start_index(submodel.m_start_index), m_nb_indices(submodel.m_nb_indices),
		m_material(new ShadedMaterial(*submodel.m_material)) {}
}