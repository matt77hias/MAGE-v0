#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "sprite\sprite_batch.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of sprite passes for rendering sprites.
	 */
	class SpritePass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the sprite pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the sprite pass associated with the 
						current engine.
		 */
		static SpritePass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		SpritePass();

		/**
		 Constructs a sprite pass from the given sprite pass.

		 @param[in]		render_pass
						A reference to the sprite pass to copy.
		 */
		SpritePass(const SpritePass &render_pass) = delete;

		/**
		 Constructs a sprite pass by moving the given sprite pass.

		 @param[in]		render_pass
						A reference to the sprite pass to move.
		 */
		SpritePass(SpritePass &&render_pass) noexcept;

		/**
		 Destructs this sprite pass.
		 */
		~SpritePass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite pass to this sprite pass.

		 @param[in]		render_pass
						A reference to the sprite pass to copy.
		 @return		A reference to the copy of the given sprite pass (i.e. 
						this sprite pass).
		 */
		SpritePass &operator=(const SpritePass &render_pass) = delete;

		/**
		 Moves the given sprite pass to this sprite pass.

		 @param[in]		render_pass
						A reference to the sprite pass to move.
		 @return		A reference to the moved sprite pass (i.e. this sprite 
						pass).
		 */
		SpritePass &operator=(SpritePass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this sprite pass.

		 @throws		Exception
						Failed to bind the fixed state of this sprite pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Renders the scene.

		 @param[in]		scene
						A reference to the scene.
		 @throws		Exception
						Failed to render the scene.
		 */
		void Render(const Scene &scene) const;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------
		
		/**
		 A pointer to the device context of this sprite pass.
		 */
		ID3D11DeviceContext4 * const m_device_context;

		/**
		 A pointer to the vertex shader of this sprite pass.
		 */
		const VertexShaderPtr m_vs;

		/**
		 A pointer to the pixel shader of this sprite pass.
		 */
		const PixelShaderPtr m_ps;

		/**
		 A pointer to the sprite batch.
		 */
		UniquePtr< SpriteBatch > m_sprite_batch;
	};
}