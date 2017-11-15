#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite.hpp"
#include "texture\texture.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of sprite images.
	 */
	class SpriteImage : public Sprite {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite image.
		 */
		SpriteImage();

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
		 @return		A reference to the copy of the given sprite image (i.e. 
						this sprite image).
		 */
		SpriteImage &operator=(const SpriteImage &sprite_image) = delete;

		/**
		 Moves the given sprite image to this sprite image.

		 @param[in]		sprite_image
						A reference to the sprite image to move.
		 @return		A reference to the moved sprite image (i.e. this sprite 
						image).
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
						A reference to the sprite batch used for rendering this 
						sprite image.
		 */
		void Draw(SpriteBatch &sprite_batch) const;

		//---------------------------------------------------------------------
		// Member Methods: Base Color and Base Color Texture
		//---------------------------------------------------------------------

		/**
		 Returns the sRGB base color of this sprite image.

		 @return		A reference to the sRGB base color of this sprite 
						image.
		 */
		SRGBA &GetBaseColor() noexcept {
			return m_base_color;
		}

		/**
		 Returns the sRGB base color of this sprite image.

		 @return		A reference to the sRGB base color of this sprite 
						image.
		 */
		const SRGBA &GetBaseColor() const noexcept {
			return m_base_color;
		}

		/**
		 Returns the sRGB base color texture of this sprite image.

		 @return		A pointer to the sRGB base color texture of this sprite 
						image.
		 */
		SharedPtr< const Texture > GetBaseColorTexture() const noexcept {
			return m_base_color_texture;
		}
		
		/**
		 Returns the shader resource view of the sRGB base color texture of 
		 this sprite image.

		 @return		@c nullptr, if this sprite image has no sRGB base 
						color texture.
		 @return		A pointer to the shader resource view of the sRGB base 
						color texture of this sprite image.
		 */
		ID3D11ShaderResourceView *GetBaseColorSRV() const noexcept {
			return m_base_color_texture ? m_base_color_texture->Get() : nullptr;
		}
		
		/**
		 Sets the sRGB base color texture of this sprite image to the given 
		 base color texture.

		 @param[in]		base_color_texture
						A pointer to the sRGB base color texture.
		 */
		void SetBaseColorTexture(
			SharedPtr< const Texture > base_color_texture) noexcept {
			
			m_base_color_texture = std::move(base_color_texture);
		}

		/**
		 Returns the base color texture region of this sprite image.

		 @return		A pointer to the base color texture region of this 
						sprite image.
		 */
		const RECT *GetBaseColorTextureRegion() const noexcept {
			return m_base_color_texture_region.get();
		}

		/**
		 Sets the base color texture region of this sprite image to the maximum 
		 texture region.
		 */
		void SetMaximumBaseColorTextureRegion() noexcept {
			m_base_color_texture_region.reset();
		}

		/**
		 Sets the base color texture region of this sprite image to the given 
		 texture region.

		 @param[in]		texture_region
						The texture region.
		 */
		void SetBaseColorTextureRegion(RECT texture_region) noexcept {
			m_base_color_texture_region 
				= MakeUnique< RECT >(std::move(texture_region));
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this sprite image.

		 @return		A pointer to the clone of this sprite image.
		 */
		virtual UniquePtr< Sprite > CloneImplementation() const override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The sRGB base color of this sprite image.
		 */
		SRGBA m_base_color;

		/**
		 A pointer to the sRGB base color texture of this sprite image.
		 */
		SharedPtr< const Texture > m_base_color_texture;

		/**
		 A pointer to the base color texture region of this sprite image.

		 If @c nullptr, the full texture region is considered.
		 */
		UniquePtr< RECT > m_base_color_texture_region;
	};
}