#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\transform_buffer.hpp"
#include "light\point_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declarations
	class Model;
	class SpriteBatch;
	class SpriteFont;

	class World {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		World();
		World(const World &world) = delete;
		World(World &&world) = default;
		virtual ~World() {
			RemoveAllModels();
			RemoveAllLights();
		}

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		World &operator=(const World &world) = delete;
		World &operator=(World &&world) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------	

		void Render2D() const;
		void Render3D(const TransformBuffer &transform_buffer) const;

		template< typename ActionT >
		void ForEachWorldObject(ActionT action) const;

		//-------------------------------------------------------------------------
		// Member Methods: Models
		//-------------------------------------------------------------------------

		size_t GetNumberOfModels() const {
			return m_models.size();
		}
		SharedPtr< Model > GetModel(const string &name) const;
		bool HasModel(const string &name) const {
			return GetModel(name) != nullptr;
		}
		bool HasModel(const SharedPtr< Model > model) const;
		void AddModel(SharedPtr< Model > model) {
			if (!model) {
				return;
			}
			m_models.insert(model);
		}
		void RemoveModel(const string &name);
		void RemoveModel(SharedPtr< Model > model);
		void RemoveAllModels() {
			m_models.clear();
		}
		template< typename ActionT >
		void ForEachModel(ActionT action) const;

		//-------------------------------------------------------------------------
		// Member Methods: Lights
		//-------------------------------------------------------------------------

		size_t GetNumberOfLights() const {
			return m_lights.size();
		}
		SharedPtr< PointLight > GetLight(const string &name) const;
		bool HasLight(const string &name) const {
			return GetLight(name) != nullptr;
		}
		bool HasLight(const SharedPtr< PointLight > light) const;
		void AddLight(SharedPtr< PointLight > light) {
			if (!light) {
				return;
			}
			m_lights.insert(light);
		}
		void RemoveLight(const string &name);
		void RemoveLight(SharedPtr< PointLight > light);
		void RemoveAllLights() {
			m_lights.clear();
		}
		template< typename ActionT >
		void ForEachLight(ActionT action) const;

		//TODO
		SharedPtr< SpriteFont > m_font;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		// 3D
		set< SharedPtr< Model >, std::less<> > m_models;
		set< SharedPtr< PointLight >, std::less<> > m_lights;

		// 2D
		SharedPtr< SpriteBatch > m_sprite_batch;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world.tpp"

#pragma endregion