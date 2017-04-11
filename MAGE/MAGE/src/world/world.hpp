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
	class PointLight;
	class SpriteBatch;
	class SpriteText;
	class SpriteImage;

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
		bool HasLight(const SharedPtr< PointLight > light) const;
		void AddLight(SharedPtr< PointLight > light);
		void RemoveLight(SharedPtr< PointLight > light);
		void RemoveAllLights();
		template< typename ActionT >
		void ForEachLight(ActionT action) const;

		//-------------------------------------------------------------------------
		// Member Methods: Texts
		//-------------------------------------------------------------------------

		size_t GetNumberOfTexts() const {
			return m_texts.size();
		}
		bool HasText(const SharedPtr< SpriteText > text) const;
		void AddText(SharedPtr< SpriteText > text);
		void RemoveText(SharedPtr< SpriteText > text);
		void RemoveAllTexts();
		template< typename ActionT >
		void ForEachText(ActionT action) const;

		//-------------------------------------------------------------------------
		// Member Methods: Images
		//-------------------------------------------------------------------------

		size_t GetNumberOfImages() const {
			return m_images.size();
		}
		bool HasImage(const SharedPtr< SpriteImage > image) const;
		void AddImage(SharedPtr< SpriteImage > image);
		void RemoveImage(SharedPtr< SpriteImage > image);
		void RemoveAllImages();
		template< typename ActionT >
		void ForEachImage(ActionT action) const;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		// 3D
		vector< SharedPtr< Model > > m_models;
		vector< SharedPtr< PointLight > > m_lights;

		// 2D
		vector< SharedPtr < SpriteText > > m_texts;
		vector< SharedPtr < SpriteImage > > m_images;
		SharedPtr< SpriteBatch > m_sprite_batch;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world.tpp"

#pragma endregion