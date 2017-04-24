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

	Model::Model(const string &name, const ModelDescriptor &desc, const CombinedShader &shader)
		: WorldObject(name),
		m_mesh(desc.GetMesh()), m_start_index(0), m_nb_indices(0),
		m_material(), m_submodels() {

		const HRESULT result_initialization = InitializeModel(desc, shader);
		if (FAILED(result_initialization)) {
			Error("Model initialization failed: %08X.", result_initialization);
			return;
		}
	}

	Model::Model(const string &name, SharedPtr< const StaticMesh > mesh,
		size_t start_index, size_t nb_indices, const ShadedMaterial &material)
		: WorldObject(name), 
		m_mesh(mesh), m_start_index(start_index), m_nb_indices(nb_indices),
		m_material(new ShadedMaterial(material)), m_submodels() {}

	Model::Model(const Model &model)
		: WorldObject(model), 
		m_mesh(model.m_mesh), m_start_index(model.m_start_index), m_nb_indices(model.m_nb_indices),
		m_material(new ShadedMaterial(*model.m_material)), m_submodels() {

		// Deep copy
		model.ForEachSubModel([this](const Model &submodel) {
			AddSubModel(submodel.Clone());
		});
	}

	Model::~Model() {
		m_submodels.clear();
	}

	HRESULT Model::InitializeModel(const ModelDescriptor &desc, const CombinedShader &shader) {
		map< string, pair< SharedPtr< Model >, string > > mapping;
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

			SharedPtr< Model > submodel(new Model(it->child, m_mesh, it->start_index, it->nb_indices, shaded_material));
			mapping[it->child] = pair< SharedPtr< Model >, string >(submodel, it->parent);
		}
		for (map< string, pair< SharedPtr< Model >, string > >::const_iterator it = mapping.cbegin(); it != mapping.cend(); ++it) {
			const pair< SharedPtr< Model >, string > &element = it->second;
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

	SharedPtr< Model > Model::GetSubModel(const string &name) const {
		for (vector< SharedPtr< Model > >::const_iterator it = m_submodels.cbegin(); it != m_submodels.cend(); ++it) {
			if ((*it)->GetName() == name) {
				return (*it);
			}
		}
		return nullptr;
	}

	void Model::AddSubModel(SharedPtr< Model > submodel) {
		Assert(submodel);
		m_submodels.push_back(submodel);
		submodel->GetTransform()->SetDirty();
	}

	void Model::UpdateChildTransforms(bool dirty_ancestor) {
		ForEachSubModel([this, dirty_ancestor](Model &submodel) {
			submodel.UpdateTransform(
				GetTransform()->GetWorldToObjectMatrix(), 
				GetTransform()->GetObjectToWorldMatrix(),
				dirty_ancestor);
		});
	}

	void Model::Draw(const LightBuffer &lighting, const TransformBuffer &transform_buffer) const {
		if (m_material && m_nb_indices != 0) {

			// Transform
			transform_buffer.SetModelToWorld(GetTransform()->GetObjectToWorldMatrix());

			// Geometry
			m_mesh->PrepareDrawing();

			// Appearance
			m_material->PrepareShading(lighting, transform_buffer);

			// Geometry
			GetMesh()->Draw(m_start_index, m_nb_indices);
		}
		
		// Childs
		ForEachSubModel([&lighting, &transform_buffer](const Model &submodel) {
			submodel.Draw(lighting, transform_buffer);
		});
	}
}