//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\meshmodel.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	MeshModel::MeshModel(const string &name, const ModelDescriptor &desc, const CombinedShader &shader)
		: Model(name), m_mesh(desc.GetMesh()) {

		const HRESULT result_initialization = InitializeModel(desc, shader);
		if (FAILED(result_initialization)) {
			Error("Model initialization failed: %08X.", result_initialization);
			return;
		}
	}
	
	HRESULT MeshModel::InitializeModel(const ModelDescriptor &desc, const CombinedShader &shader) {
		map< string, pair< SubModel *, string > > mapping;
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

			SubModel *submodel = new SubModel(it->child, it->start_index, it->nb_indices, shaded_material);
			mapping[it->child] = pair< SubModel *, string >(submodel, it->parent);
		}
		for (map< string, pair< SubModel *, string > >::const_iterator it = mapping.cbegin(); it != mapping.cend(); ++it) {
			const pair< SubModel *, string > &element = it->second;
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

	void MeshModel::Draw(const World &world, const TransformBuffer &transform_buffer) const {
		m_mesh->PrepareDrawing();
		
		// Childs
		ForEachSubModel([&](SubModel &submodel) {
			submodel.Draw(*m_mesh, world, transform_buffer);
		});
	}
}