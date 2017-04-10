//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.hpp"
#include "light\point_light.hpp"
#include "text\sprite_text.hpp"
#include "sprite\sprite_image.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	World::World() 
		: m_models(), m_lights(), m_sprite_batch(CreateSpriteBatch()) {}

	void World::Render2D() const {
		m_sprite_batch->Begin();
		ForEachImage([&](const SpriteImage &image) {
			image.Draw(*m_sprite_batch);
		});
		ForEachText([&](const SpriteText &text) {
			text.Draw(*m_sprite_batch);
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

	bool World::HasLight(const SharedPtr< PointLight > light) const {
		for (vector< SharedPtr< PointLight > >::const_iterator it = m_lights.cbegin(); it != m_lights.cend(); ++it) {
			if ((*it) == light) {
				return true;
			}
		}
		return false;
	}
	void World::AddLight(SharedPtr< PointLight > light) {
		if (!light) {
			return;
		}
		m_lights.push_back(light);
	}
	void World::RemoveLight(SharedPtr< PointLight > light) {
		vector< SharedPtr< PointLight > >::iterator it = m_lights.begin();
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
	// Texts
	//-------------------------------------------------------------------------

	bool World::HasText(const SharedPtr< SpriteText > text) const {
		for (vector< SharedPtr< SpriteText > >::const_iterator it = m_texts.cbegin(); it != m_texts.cend(); ++it) {
			if ((*it) == text) {
				return true;
			}
		}
		return false;
	}
	void World::AddText(SharedPtr< SpriteText > text) {
		if (!text) {
			return;
		}
		m_texts.push_back(text);
	}
	void World::RemoveText(SharedPtr< SpriteText > text) {
		vector< SharedPtr< SpriteText > >::iterator it = m_texts.begin();
		while (it != m_texts.end()) {
			if ((*it) == text) {
				it = m_texts.erase(it);
				break;
			}
			else {
				++it;
			}
		}
	}
	void World::RemoveAllTexts() {
		m_texts.clear();
	}

	//-------------------------------------------------------------------------
	// Images
	//-------------------------------------------------------------------------

	bool World::HasImage(const SharedPtr< SpriteImage > image) const {
		for (vector< SharedPtr< SpriteImage > >::const_iterator it = m_images.cbegin(); it != m_images.cend(); ++it) {
			if ((*it) == image) {
				return true;
			}
		}
		return false;
	}
	void World::AddImage(SharedPtr< SpriteImage > image) {
		if (!image) {
			return;
		}
		m_images.push_back(image);
	}
	void World::RemoveImage(SharedPtr< SpriteImage > image) {
		vector< SharedPtr< SpriteImage > >::iterator it = m_images.begin();
		while (it != m_images.end()) {
			if ((*it) == image) {
				it = m_images.erase(it);
				break;
			}
			else {
				++it;
			}
		}
	}
	void World::RemoveAllImages() {
		m_images.clear();
	}
}