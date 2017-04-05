//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.hpp"
#include "sprite\sprite_font.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	World::World() 
		: m_models(), m_lights(), m_sprite_batch(CreateSpriteBatch()) {}

	void World::Render2D() const {
		m_sprite_batch->Begin();
		m_font->DrawString(*m_sprite_batch, L"Hello, world!", SpriteTransform(XMFLOAT2(256,256)));
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

	SharedPtr< Model > World::GetModel(const string &name) const {
		for (set< SharedPtr< Model > >::const_iterator it = m_models.cbegin(); it != m_models.cend(); ++it) {
			if ((*it)->GetName() == name) {
				return (*it);
			}
		}
		return nullptr;
	}
	bool World::HasModel(const SharedPtr< Model > model) const {
		for (set< SharedPtr< Model > >::const_iterator it = m_models.cbegin(); it != m_models.cend(); ++it) {
			if ((*it) == model) {
				return true;
			}
		}
		return false;
	}
	void World::RemoveModel(const string &name) {
		set< SharedPtr< Model > >::iterator it = m_models.begin();
		while (it != m_models.end()) {
			if ((*it)->GetName() == name) {
				it = m_models.erase(it);
				break;
			}
			else {
				++it;
			}
		}
	}
	void World::RemoveModel(SharedPtr< Model > model) {
		set< SharedPtr< Model > >::iterator it = m_models.begin();
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

	//-------------------------------------------------------------------------
	// Lights
	//-------------------------------------------------------------------------

	SharedPtr< PointLight > World::GetLight(const string &name) const {
		for (set< SharedPtr< PointLight > >::const_iterator it = m_lights.cbegin(); it != m_lights.cend(); ++it) {
			if ((*it)->GetName() == name) {
				return (*it);
			}
		}
		return nullptr;
	}
	bool World::HasLight(const SharedPtr< PointLight > light) const {
		for (set< SharedPtr< PointLight > >::const_iterator it = m_lights.cbegin(); it != m_lights.cend(); ++it) {
			if ((*it) == light) {
				return true;
			}
		}
		return false;
	}
	void World::RemoveLight(const string &name) {
		set< SharedPtr< PointLight > >::iterator it = m_lights.begin();
		while (it != m_lights.end()) {
			if ((*it)->GetName() == name) {
				it = m_lights.erase(it);
				break;
			}
			else {
				++it;
			}
		}
	}
	void World::RemoveLight(SharedPtr< PointLight > light) {
		set< SharedPtr< PointLight > >::iterator it = m_lights.begin();
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
}