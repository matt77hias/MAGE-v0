//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.hpp"
#include "light\light.hpp"
#include "sprite\sprite_object.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	World::World() 
		: m_models(), m_lights(), m_sprites(),
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
		for (vector< SharedPtr< Model > >::const_iterator it = m_models.cbegin(); it != m_models.cend(); ++it) {
			if ((*it) == model) {
				return true;
			}
		}
		return false;
	}
	void World::AddModel(SharedPtr< Model > model) {
		if (!model) {
			return;
		}
		m_models.push_back(model);
	}
	void World::RemoveModel(SharedPtr< Model > model) {
		vector< SharedPtr< Model > >::iterator it = m_models.begin();
		while (it != m_models.end()) {
			if ((*it) == model) {
				it = m_models.erase(it);
				break;
			}
			else {
				++it;
			}
		}
	}
	void World::RemoveAllModels() {
		m_models.clear();
	}

	//-------------------------------------------------------------------------
	// Lights
	//-------------------------------------------------------------------------

	bool World::HasLight(const SharedPtr< Light > light) const {
		for (vector< SharedPtr< Light > >::const_iterator it = m_lights.cbegin(); it != m_lights.cend(); ++it) {
			if ((*it) == light) {
				return true;
			}
		}
		return false;
	}
	void World::AddLight(SharedPtr< Light > light) {
		if (!light) {
			return;
		}
		m_lights.push_back(light);
	}
	void World::RemoveLight(SharedPtr< Light > light) {
		vector< SharedPtr< Light > >::iterator it = m_lights.begin();
		while (it != m_lights.end()) {
			if ((*it) == light) {
				it = m_lights.erase(it);
				break;
			}
			else {
				++it;
			}
		}
	}
	void World::RemoveAllLights() {
		m_lights.clear();
	}

	//-------------------------------------------------------------------------
	// Sprites
	//-------------------------------------------------------------------------

	bool World::HasSprite(const SharedPtr< SpriteObject > sprite) const {
		for (vector< SharedPtr< SpriteObject > >::const_iterator it = m_sprites.cbegin(); it != m_sprites.cend(); ++it) {
			if ((*it) == sprite) {
				return true;
			}
		}
		return false;
	}
	void World::AddSprite(SharedPtr< SpriteObject > sprite) {
		if (!sprite) {
			return;
		}
		m_sprites.push_back(sprite);
	}
	void World::RemoveSprite(SharedPtr< SpriteObject > sprite) {
		vector< SharedPtr< SpriteObject > >::iterator it = m_sprites.begin();
		while (it != m_sprites.end()) {
			if ((*it) == sprite) {
				it = m_sprites.erase(it);
				break;
			}
			else {
				++it;
			}
		}
	}
	void World::RemoveAllSprites() {
		m_sprites.clear();
	}
}