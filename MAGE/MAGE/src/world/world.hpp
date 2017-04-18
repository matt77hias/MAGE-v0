#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\transform_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declarations
	class Model;
	class Light;
	class SpriteObject;
	class SpriteBatch;

	class World final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		World();
		World(const World &world) = delete;
		World(World &&world) = default;
		~World();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		World &operator=(const World &world) = delete;
		World &operator=(World &&world) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------	
		void Clear();

		void Render2D() const;
		void Render3D(const TransformBuffer &transform_buffer) const;

		template< typename ActionT >
		void ForEachObject(ActionT action) const;
		template< typename ActionT >
		void ForEachObject2D(ActionT action) const;
		template< typename ActionT >
		void ForEachObject3D(ActionT action) const;

		//-------------------------------------------------------------------------
		// Member Methods: Models
		//-------------------------------------------------------------------------

		size_t GetNumberOfModels() const {
			return m_models.size();
		}
		bool HasModel(const SharedPtr< Model > model) const;
		void AddModel(SharedPtr< Model > model);
		void RemoveModel(SharedPtr< Model > model);
		void RemoveAllModels();
		template< typename ActionT >
		void ForEachModel(ActionT action) const;

		//-------------------------------------------------------------------------
		// Member Methods: Lights
		//-------------------------------------------------------------------------

		size_t GetNumberOfLights() const {
			return m_lights.size();
		}
		bool HasLight(const SharedPtr< Light > light) const;
		void AddLight(SharedPtr< Light > light);
		void RemoveLight(SharedPtr< Light > light);
		void RemoveAllLights();
		template< typename ActionT >
		void ForEachLight(ActionT action) const;

		//-------------------------------------------------------------------------
		// Member Methods: Sprites
		//-------------------------------------------------------------------------

		size_t GetNumberOfSprites() const {
			return m_sprites.size();
		}
		bool HasSprite(const SharedPtr< SpriteObject > sprite) const;
		void AddSprite(SharedPtr< SpriteObject > sprite);
		void RemoveSprite(SharedPtr< SpriteObject > sprite);
		void RemoveAllSprites();
		template< typename ActionT >
		void ForEachSprite(ActionT action) const;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		// 3D
		vector< SharedPtr< Model > > m_models;
		vector< SharedPtr< Light > > m_lights;

		// 2D
		vector< SharedPtr < SpriteObject > > m_sprites;
		SharedPtr< SpriteBatch > m_sprite_batch;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world.tpp"

#pragma endregion