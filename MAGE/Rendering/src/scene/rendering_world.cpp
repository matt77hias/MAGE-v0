//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\rendering_world.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <map>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	World::World(ID3D11Device& device,
				 DisplayConfiguration& display_configuration,
				 ResourceManager& resource_manager)
		: m_device(device), 
		m_display_configuration(display_configuration), 
		m_resource_manager(resource_manager), 
		m_perspective_cameras(),
		m_orthographic_cameras(),
		m_ambient_lights(),
		m_directional_lights(),
		m_omni_lights(),
		m_spot_lights(),
		m_models(),
		m_sprite_images(),
		m_sprite_texts() {}

	World::World(World&& world) noexcept = default;

	World::~World() = default;

	World& World::operator=(World&& world) noexcept = default;
	
	void World::Clear() noexcept {
		m_perspective_cameras.clear();
		m_orthographic_cameras.clear();
		m_ambient_lights.clear();
		m_directional_lights.clear();
		m_omni_lights.clear();
		m_spot_lights.clear();
		m_models.clear();
		m_sprite_images.clear();
		m_sprite_texts.clear();
	}
}