//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ResourceManager::ResourceManager(ID3D11Device& device) 
		: m_device(device), 
		m_model_descriptor_pool(), 
		m_vs_pool(), 
		m_hs_pool(),
		m_ds_pool(),
		m_gs_pool(),
		m_ps_pool(),
		m_cs_pool(),
		m_sprite_font_pool(),
		m_texture_pool() {}

	ResourceManager::ResourceManager(ResourceManager&& manager) noexcept = default;

	ResourceManager::~ResourceManager() = default;
}
