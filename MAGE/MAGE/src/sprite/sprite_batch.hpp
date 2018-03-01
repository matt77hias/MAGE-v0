#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering.hpp"
#include "sprite\sprite_utils.hpp"
#include "transform\sprite_transform.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of sprite batches.
	 */
	class alignas(16) SpriteBatch final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite batch.

		 @param[in]		device
						A reference to the device.
		 @param[in]		device_context
						A reference to the device context.
		 */
		SpriteBatch(ID3D11Device &device, ID3D11DeviceContext &device_context);

		/**
		 Constructs a sprite batch from the given sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to copy.
		 */
		SpriteBatch(const SpriteBatch &sprite_batch) = delete;

		/**
		 Constructs a sprite batch by moving the given sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to move.
		 */
		SpriteBatch(SpriteBatch &&sprite_batch) noexcept;
		
		/**
		 Destructs this sprite batch.
		 */
		~SpriteBatch();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite batch to this sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to copy.
		 @return		A reference to the copy of the given sprite batch (i.e. 
						this sprite batch).
		 */
		SpriteBatch &operator=(const SpriteBatch &sprite_batch) = delete;

		/**
		 Moves the given sprite batch to this sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to move.
		 @return		A reference to the moved sprite batch (i.e. this sprite 
						batch).
		 */
		SpriteBatch &operator=(SpriteBatch &&sprite_batch) = delete;

		//---------------------------------------------------------------------
		// Member Methods: Lifecycle
		//---------------------------------------------------------------------

		/**
		 Begins the processing of a batch of sprites.

		 @pre			This sprite batch is not inside a begin/end pair.
		 @param[in]		sort_mode
						A reference to the sprite sorting mode for the whole 
						batch of sprites.
		 @param[in]		transform
						The transform for the whole batch of sprites.
		 */
		void XM_CALLCONV Begin(SpriteSortMode sort_mode = SpriteSortMode::Deferred,
			                   FXMMATRIX transform = XMMatrixIdentity());
		
		/**
		 Draws a sprite.

		 @pre			This sprite batch is inside a begin/end pair.
		 @pre			@a texture is not equal to @c nullptr.
		 @param[in]		texture
						A pointer to the shader resource view of the texture to 
						draw.
		 @param[in]		color
						The sRGB color (multiplier).
		 @param[in]		effects
						The sprite effects to apply.
		 @param[in]		transform
						A reference to the sprite transform.
		 @param[in]		source
						A pointer the rectangular subregion of the texture.
		 */
		void XM_CALLCONV Draw(ID3D11ShaderResourceView *texture, 
			                  FXMVECTOR color, 
			                  SpriteEffect effects, 
			                  const SpriteTransform &transform, 
			                  const RECT *source = nullptr);
		
		/**
		 Ends the processing of a batch of sprites.

		 @pre			This sprite batch is inside a begin/end pair.
		 */
		void End();

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		class Impl;

		/**
		 A pointer to the implementation of this sprite batch.
		 */
		UniquePtr< Impl > m_impl;
	};
}