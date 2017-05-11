//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"

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

	const Material *ModelDescriptor::GetMaterial(const string &name) const {
		for (auto it = m_materials.cbegin(); it != m_materials.cend(); ++it) {
			if (it->GetName() == name) {
				return &(*it);
			}
		}
		return nullptr;
	}

	const ModelPart *ModelDescriptor::GetModelPart(const string &name) const {
		for (auto it = m_model_parts.cbegin(); it != m_model_parts.cend(); ++it) {
			if (it->m_child == name) {
				return &(*it);
			}
		}
		return nullptr;
	}

	ID3D11Device2 *GetModelRenderingDevice() {
		return GetRenderingDevice();
	}

	ID3D11DeviceContext2 *GetModelRenderingDeviceContext() {
		return GetRenderingDeviceContext();
	}

	ResourceFactory *GetModelResourceFactory() {
		return GetResourceFactory();
	}
}