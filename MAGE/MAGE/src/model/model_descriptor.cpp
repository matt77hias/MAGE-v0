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

	ModelDescriptor::ModelDescriptor(ModelDescriptor &&desc) noexcept = default;

	ModelDescriptor::~ModelDescriptor() = default;

	ModelDescriptor &ModelDescriptor
		::operator=(ModelDescriptor &&desc) noexcept = default;

	[[nodiscard]] const Material *ModelDescriptor
		::GetMaterial(const string &name) const noexcept {
		
		for (const auto &material : m_materials) {
			if (material.GetName() == name) {
				return &material;
			}
		}
		
		return nullptr;
	}

	[[nodiscard]] const ModelPart *ModelDescriptor
		::GetModelPart(const string &name) const noexcept {
		
		for (const auto &model_part : m_model_parts) {
			if (model_part.m_child == name) {
				return &model_part;
			}
		}
		
		return nullptr;
	}
}