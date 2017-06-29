//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ModelDescriptor::ModelDescriptor(ModelDescriptor &&desc) = default;

	ModelDescriptor::~ModelDescriptor() {
		m_materials.clear();
		m_model_parts.clear();
	}

	const Material *ModelDescriptor::GetMaterial(const string &name) const noexcept {
		for (auto it = m_materials.cbegin(); it != m_materials.cend(); ++it) {
			if (it->GetName() == name) {
				return &(*it);
			}
		}
		return nullptr;
	}

	const ModelPart *ModelDescriptor::GetModelPart(const string &name) const noexcept {
		for (auto it = m_model_parts.cbegin(); it != m_model_parts.cend(); ++it) {
			if (it->m_child == name) {
				return &(*it);
			}
		}
		return nullptr;
	}
}