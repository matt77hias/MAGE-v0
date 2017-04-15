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

		for (vector< SubModel * >::const_iterator it = model.m_submodels.cbegin(); it != model.m_submodels.cend(); ++it) {
			AddSubModel((*it)->Clone());
		}
	}

	Model::~Model() {
		RemoveAndDestructAllElements(m_submodels);
	}

	void Model::AddSubModel(SubModel *submodel) {
		Assert(submodel);
		m_submodels.push_back(submodel);
		submodel->GetTransform()->SetDirty();
	}

	SubModel *Model::GetSubModel(const string &name) const {
		for (vector< SubModel * >::const_iterator it = m_submodels.cbegin(); it != m_submodels.cend(); ++it) {
			if ((*it)->GetName() == name) {
				return (*it);
			}
		}
		return nullptr;
	}

	void Model::Draw(const World &world, const TransformBuffer &transform_buffer) const {
		UNUSED(world);
		UNUSED(transform_buffer);
	}

	void Model::UpdateChildTransforms(bool dirty_ancestor) {
		ForEachSubModel([&](SubModel &submodel) {
			submodel.UpdateTransform(
				GetTransform()->GetWorldToObjectMatrix(), 
				GetTransform()->GetObjectToWorldMatrix(),
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

	void SubModel::Draw(const Mesh &mesh, const World &world, const TransformBuffer &transform_buffer) const {
		// Appearance
		transform_buffer.SetModelToWorld(GetTransform()->GetObjectToWorldMatrix());
		m_material->PrepareShading(world, transform_buffer);
		// Geometry
		mesh.Draw(m_start_index, m_nb_indices);
		// Childs
		ForEachSubModel([&](SubModel &submodel) {
			submodel.Draw(mesh, world, transform_buffer);
		});
	}
}