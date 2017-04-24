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

	Model::Model(const string &name, const ModelDescriptor &desc, const CombinedShader &shader)
		: WorldObject(name), m_mesh(desc.GetMesh()) {

		const HRESULT result_initialization = InitializeModel(desc, shader);
		if (FAILED(result_initialization)) {
			Error("Model initialization failed: %08X.", result_initialization);
			return;
		}
	}

	Model::Model(const Model &model)
		: WorldObject(model), m_mesh(model.m_mesh) {

		// Deep copy
		model.ForEachSubModel([this](const SubModel &submodel) {
			AddSubModel(submodel.Clone());
		});
	}

	Model::~Model() {
		m_submodels.clear();
	}

	HRESULT Model::InitializeModel(const ModelDescriptor &desc, const CombinedShader &shader) {
		map< string, pair< SharedPtr< SubModel >, string > > mapping;
		for (vector< ModelPart >::const_iterator it = desc.ModelPartsBegin(); it != desc.ModelPartsEnd(); ++it) {
			if (it->child == MAGE_MDL_PART_DEFAULT_CHILD && it->nb_indices == 0) {
				continue;
			}

			Material material(MAGE_MDL_PART_DEFAULT_MATERIAL);
			if (it->material != MAGE_MDL_PART_DEFAULT_MATERIAL) {
				for (vector< Material >::const_iterator mit = desc.MaterialsBegin(); mit != desc.MaterialsEnd(); ++mit) {
					if (mit->m_name == it->material) {
						material = *mit;
						break;
					}
				}
			}
			ShadedMaterial shaded_material(shader, material);

			SharedPtr< SubModel > submodel(new SubModel(it->child, m_mesh, it->start_index, it->nb_indices, shaded_material));
			mapping[it->child] = pair< SharedPtr< SubModel >, string >(submodel, it->parent);
		}
		for (map< string, pair< SharedPtr< SubModel >, string > >::const_iterator it = mapping.cbegin(); it != mapping.cend(); ++it) {
			const pair< SharedPtr< SubModel >, string > &element = it->second;
			const string &parent = element.second;
			if (parent == MAGE_MDL_PART_DEFAULT_PARENT) {
				AddSubModel(element.first);
			}
			else {
				mapping[parent].first->AddSubModel(element.first);
			}
		}

		return S_OK;
	}

	SharedPtr< SubModel > Model::GetSubModel(const string &name) const {
		for (vector< SharedPtr< SubModel > >::const_iterator it = m_submodels.cbegin(); it != m_submodels.cend(); ++it) {
			if ((*it)->GetName() == name) {
				return (*it);
			}
		}
		return nullptr;
	}

	void Model::AddSubModel(SharedPtr< SubModel > submodel) {
		Assert(submodel);
		m_submodels.push_back(submodel);
		submodel->GetTransform()->SetDirty();
	}

	void Model::UpdateChildTransforms(bool dirty_ancestor) {
		ForEachSubModel([this, dirty_ancestor](SubModel &submodel) {
			submodel.UpdateTransform(
				GetTransform()->GetWorldToObjectMatrix(), 
				GetTransform()->GetObjectToWorldMatrix(),
				dirty_ancestor);
		});
	}

	void Model::Draw(const LightBuffer &lighting, const TransformBuffer &transform_buffer) const {
		// Geometry
		m_mesh->PrepareDrawing();
		// Childs
		ForEachSubModel([&lighting, &transform_buffer](SubModel &submodel) {
			submodel.Draw(lighting, transform_buffer);
		});
	}

	//-------------------------------------------------------------------------
	// SubModel
	//-------------------------------------------------------------------------

	SubModel::SubModel(const string &name, SharedPtr< StaticMesh > mesh,
		size_t start_index, size_t nb_indices, const ShadedMaterial &material)
		: Model(name, mesh), m_start_index(start_index), m_nb_indices(nb_indices),
		m_material(new ShadedMaterial(material)) {}
	
	SubModel::SubModel(const SubModel &submodel) 
		: Model(submodel), m_start_index(submodel.m_start_index), m_nb_indices(submodel.m_nb_indices),
		m_material(new ShadedMaterial(*submodel.m_material)) {}

	void SubModel::Draw(const LightBuffer &lighting, const TransformBuffer &transform_buffer) const {
		// Transform
		transform_buffer.SetModelToWorld(GetTransform()->GetObjectToWorldMatrix());
		// Appearance
		m_material->PrepareShading(lighting, transform_buffer);
		// Geometry
		GetMesh()->Draw(m_start_index, m_nb_indices);
		// Childs
		ForEachSubModel([&lighting, &transform_buffer](SubModel &submodel) {
			submodel.Draw(lighting, transform_buffer);
		});
	}
}