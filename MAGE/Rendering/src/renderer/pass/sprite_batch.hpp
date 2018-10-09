#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "direct3d11.hpp"
#include "transform\transform.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// SpriteEffect
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An enumeration of the different sprite effects.

	 This contains:
	 @c None,
	 @c MirrorX,
	 @c MirrorY and
	 @c MirrorXY.
	 */
	enum class SpriteEffect : U8 {
		None     = 0,                 // No sprite effects.
		MirrorX  = 1,                 // Mirror sprites along the x-axis.
		MirrorY  = 2,                 // Mirror sprites along the y-axis.
		MirrorXY = MirrorX | MirrorY  // Mirror sprites along the x- and y-axis.
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// SpriteSortMode
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An enumeration of the different sprite sorting modes.

	 This contains:
	 @c Deferred,
	 @c Immediate,
	 @c Texture,
	 @c BackToFront and
	 @c FrontToBack.
	 */
	enum class SpriteSortMode : U8 {
		Deferred,	 // Deferred, FIFO order of the sprites.
		Immediate,   // Immediate, FIFO order of the sprites.
		Texture,     // Deferred sorting based on the texture of the sprites.
		BackToFront, // Deferred, back-to-front sorting based on the depth
		             // value of the sprites.
		FrontToBack	 // Deferred, front-to-back sorting based on the depth
		             // value of the sprites.
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// SpriteBatch
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of sprite batches.
	 */
	class SpriteBatch {

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
		SpriteBatch(ID3D11Device& device, ID3D11DeviceContext& device_context);

		/**
		 Constructs a sprite batch from the given sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to copy.
		 */
		SpriteBatch(const SpriteBatch& sprite_batch) = delete;

		/**
		 Constructs a sprite batch by moving the given sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to move.
		 */
		SpriteBatch(SpriteBatch&& sprite_batch) noexcept;

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
		SpriteBatch& operator=(const SpriteBatch& sprite_batch) = delete;

		/**
		 Moves the given sprite batch to this sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to move.
		 @return		A reference to the moved sprite batch (i.e. this sprite
						batch).
		 */
		SpriteBatch& operator=(SpriteBatch&& sprite_batch) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Lifecycle
		//---------------------------------------------------------------------

		/**
		 Begins the processing of a batch of sprites.

		 @pre			This sprite batch is not inside a begin/end pair.
		 @param[in]		sort_mode
						A reference to the sprite sorting mode for the whole
						batch of sprites.
		 */
		void Begin(SpriteSortMode sort_mode = SpriteSortMode::Deferred);

		/**
		 Draws a sprite.

		 @pre			This sprite batch is inside a begin/end pair.
		 @param[in]		texture
						A pointer to the shader resource view of the texture to
						draw.
		 @param[in]		color
						The (linear) RGBA color.
		 @param[in]		effects
						The sprite effects to apply.
		 @param[in]		transform
						A reference to the sprite transform.
		 @param[in]		source
						A pointer the rectangular subregion of the texture.
		 */
		void XM_CALLCONV Draw(ID3D11ShaderResourceView* texture,
			                  FXMVECTOR color,
			                  SpriteEffect effects,
			                  const SpriteTransform2D& transform,
			                  const RECT* source = nullptr);

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

	#pragma endregion
}