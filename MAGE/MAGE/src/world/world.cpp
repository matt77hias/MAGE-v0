//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.hpp"
#include "light\omni_light.hpp"
#include "light\spot_light.hpp"
#include "sprite\sprite_object.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	World::World() 
		: m_models(), m_omni_lights(), m_spot_lights(), m_sprites(),
		m_sprite_batch(CreateSpriteBatch()) {}

	World::~World() {
		Clear();
	}

	void World::Clear() {
		RemoveAllModels();
		RemoveAllLights();
		RemoveAllSprites();
	}

	void World::Render2D() const {
		m_sprite_batch->Begin();
		ForEachSprite([&](const SpriteObject &sprite) {
			sprite.Draw(*m_sprite_batch);
		});
		m_sprite_batch->End();
	}
	void World::Render3D(const TransformBuffer &transform_buffer) const {
		ForEachModel([&](const Model &model) {
			model.Draw(*this, transform_buffer);
		});
	}

	//-------------------------------------------------------------------------
	// Models
	//-------------------------------------------------------------------------

	bool World::HasModel(const SharedPtr< Model > model) const {
		return std::find(m_models.begin(), m_models.end(), model) != m_models.end();
	}
	void World::AddModel(SharedPtr< Model > model) {
		if (!model) {
			return;
		}
		m_models.push_back(model);
	}
	void World::RemoveModel(SharedPtr< Model > model) {
		vector< SharedPtr< Model > >::iterator it = std::find(m_models.begin(), m_models.end(), model);
		if (it != m_models.end()) {
			m_models.erase(it);
		}
	}
	void World::RemoveAllModels() {
		m_models.clear();
	}

	//-------------------------------------------------------------------------
	// Lights
	//-------------------------------------------------------------------------

	bool World::HasLight(const SharedPtr< OmniLight > light) const {
		return std::find(m_omni_lights.begin(), m_omni_lights.end(), light) != m_omni_lights.end();
	}
	bool World::HasLight(const SharedPtr< SpotLight > light) const {
		return std::find(m_spot_lights.begin(), m_spot_lights.end(), light) != m_spot_lights.end();
	}
	void World::AddLight(SharedPtr< OmniLight > light) {
		if (!light) {
			return;
		}
		m_omni_lights.push_back(light);
	}
	void World::AddLight(SharedPtr< SpotLight > light) {
		if (!light) {
			return;
		}
		m_spot_lights.push_back(light);
	}
	void World::RemoveLight(SharedPtr< OmniLight > light) {
		vector< SharedPtr< OmniLight > >::iterator it = std::find(m_omni_lights.begin(), m_omni_lights.end(), light);
		if (it != m_omni_lights.end()) {
			m_omni_lights.erase(it);
		}
	}
	void World::RemoveLight(SharedPtr< SpotLight > light) {
		vector< SharedPtr< SpotLight > >::iterator it = std::find(m_spot_lights.begin(), m_spot_lights.end(), light);
		if (it != m_spot_lights.end()) {
			m_spot_lights.erase(it);
		}
	}
	void World::RemoveAllLights() {
		m_omni_lights.clear();
		m_spot_lights.clear();
	}

	//-------------------------------------------------------------------------
	// Sprites
	//-------------------------------------------------------------------------

	bool World::HasSprite(const SharedPtr< SpriteObject > sprite) const {
		return std::find(m_sprites.begin(), m_sprites.end(), sprite) != m_sprites.end();
	}
	void World::AddSprite(SharedPtr< SpriteObject > sprite) {
		if (!sprite) {
			return;
		}
		m_sprites.push_back(sprite);
	}
	void World::RemoveSprite(SharedPtr< SpriteObject > sprite) {
		vector< SharedPtr< SpriteObject > >::iterator it = std::find(m_sprites.begin(), m_sprites.end(), sprite);
		if (it != m_sprites.end()) {
			m_sprites.erase(it);
		}
	}
	void World::RemoveAllSprites() {
		m_sprites.clear();
	}
}