#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_object.hpp"
#include "texture\texture.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of sprite images.
	 */
	class SpriteImage : public SpriteObject {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite image.

		 @pre			@c texture.get() is not equal to @c nullptr.
		 @param[in]		name
						The name.
		 @param[in]		texture
						A pointer to the texture.
		 @param[in]		color
						The color.
		 @param[in]		effects
						The sprite effects to apply.
		 */
		explicit SpriteImage(const string &name, SharedPtr< Texture > texture,
			const Color &color, SpriteEffect effects = SpriteEffect_None);
		
		/**
		 Constructs a sprite image.

		 @pre			@c texture.get() is not equal to @c nullptr.
		 @param[in]		name
						The name.
		 @param[in]		texture
						A pointer to the texture.
		 @param[in]		texture_region
						A reference to the texture region.
		 @param[in]		color
						The color.
		 @param[in]		effects
						The sprite effects to apply.
		 */
		explicit SpriteImage(const string &name, SharedPtr< Texture > texture, const RECT &texture_region,
			const Color &color, SpriteEffect effects = SpriteEffect_None);
		
		/**
		 Constructs a sprite image.

		 @pre			@c texture.get() is not equal to @c nullptr.
		 @param[in]		name
						The name.
		 @param[in]		texture
						A pointer to the texture.
		 @param[in]		color
						The color.
		 @param[in]		effects
						The sprite effects to apply.
		 */
		explicit SpriteImage(const string &name, SharedPtr< Texture > texture,
			const XMVECTOR &color = Colors::White, SpriteEffect effects = SpriteEffect_None);
		
		/**
		 Constructs a sprite image.

		 @pre			@c texture.get() is not equal to @c nullptr.
		 @param[in]		name
						The name.
		 @param[in]		texture
						A pointer to the texture.
		 @param[in]		texture_region
						A reference to the texture region.
		 @param[in]		color
						The color.
		 @param[in]		effects
						The sprite effects to apply.
		 */
		explicit SpriteImage(const string &name, SharedPtr< Texture > texture, const RECT &texture_region,
			const XMVECTOR &color = Colors::White, SpriteEffect effects = SpriteEffect_None);
		
		/**
		 Constructs a sprite image from the given sprite image.

		 @param[in]		sprite_image
						A reference to the sprite image to copy.
		 */
		SpriteImage(const SpriteImage &sprite_image);

		/**
		 Constructs a sprite image by moving the given sprite image.

		 @param[in]		sprite_image
						A reference to the sprite image to move.
		 */
		SpriteImage(SpriteImage &&sprite_image);

		/**
		 Destruct this sprite image.
		 */
		virtual ~SpriteImage();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite image to this sprite image.

		 @param[in]		sprite_image
						A reference to the sprite image to copy.
		 @return		A reference to the copy of the given sprite image
						(i.e. this sprite image).
		 */
		SpriteImage &operator=(const SpriteImage &sprite_image) = delete;

		/**
		 Moves the given sprite image to this sprite image.

		 @param[in]		sprite_image
						A reference to the sprite image to move.
		 @return		A reference to the moved sprite image
						(i.e. this sprite image).
		 */
		SpriteImage &operator=(SpriteImage &&sprite_image) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this sprite image.

		 @return		A pointer to the clone of this sprite image.
		 */
		UniquePtr< SpriteImage > Clone() const {
			return static_pointer_cast< SpriteImage >(CloneImplementation());
		}

		/**
		 Draws this sprite image.

		 @param[in]		sprite_batch
						A reference to the sprite batch used for rendering
						this sprite image.
		 */
		void Draw(SpriteBatch &sprite_batch) const;

		/**
		 Sets the texture region of this sprite image 
		 to the given texture region.

		 @param[in]		texture_region
						A reference to the texture region.
		 */
		void SetTextureRegion(const RECT &texture_region);

		/**
		 Returns the texture of this sprite image.

		 @return		A pointer to the texture of this sprite image.
		 */
		SharedPtr< Texture > GetTexture() const noexcept {
			return m_texture;
		}

		/**
		 Sets the texture of this sprite image to the given texture.

		 @pre			@c texture.get() is not equal to @c nullptr
		 @param[in]		texture
						A pointer to the texture.
		 */
		void SetTexture(SharedPtr< Texture > texture);

		/**
		 Returns the color of this sprite image.

		 @return		The color of this sprite image.
		 */
		const Color GetColor() const noexcept {
			return m_color;
		}

		/**
		 Sets the color of this sprite image to the given color.

		 @param[in]		color
						A reference to the color.
		 */
		void SetColor(const Color &color) {
			m_color = color;
		}

		/**
		 Sets the color of this sprite image to the given color.

		 @param[in]		color
						A reference to the color.
		 */
		void SetColor(const XMVECTOR &color) {
			XMStoreFloat4(&m_color, color);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this sprite image.

		 @return		A pointer to the clone of this sprite image.
		 */
		virtual UniquePtr< SpriteObject > CloneImplementation() const override;

		/**
		 Returns the color of this sprite image as @c XMVECTOR.

		 @return		The color of this sprite image as @c XMVECTOR.
		 */
		const XMVECTOR GetColorVector() const {
			return XMLoadFloat4(&m_color);
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The color of this sprite image.
		 */
		Color m_color;

		/**
		 A pointer to the texture region of this sprite image.

		 If @c nullptr, the full texture region is considered.
		 */
		UniquePtr< RECT > m_texture_region;

		/**
		 A pointer tot the texture of this sprite image.
		 */
		SharedPtr< Texture > m_texture;
	};
}