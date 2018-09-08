#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\state_manager.hpp"
#include "resource\rendering_resource_manager.hpp"
#include "scene\rendering_world.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of sprite passes for rendering sprites.
	 */
	class SpritePass {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite pass.

		 @param[in]		device
						A reference to the device.
		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		state_manager
						A reference to the state manager.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit SpritePass(ID3D11Device& device, 
							ID3D11DeviceContext& device_context, 
							StateManager& state_manager, 
							ResourceManager& resource_manager);

		/**
		 Constructs a sprite pass from the given sprite pass.

		 @param[in]		pass
						A reference to the sprite pass to copy.
		 */
		SpritePass(const SpritePass& pass) = delete;

		/**
		 Constructs a sprite pass by moving the given sprite pass.

		 @param[in]		pass
						A reference to the sprite pass to move.
		 */
		SpritePass(SpritePass&& pass) noexcept;

		/**
		 Destructs this sprite pass.
		 */
		~SpritePass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite pass to this sprite pass.

		 @param[in]		pass
						A reference to the sprite pass to copy.
		 @return		A reference to the copy of the given sprite pass (i.e. 
						this sprite pass).
		 */
		SpritePass& operator=(const SpritePass& pass) = delete;

		/**
		 Moves the given sprite pass to this sprite pass.

		 @param[in]		pass
						A reference to the sprite pass to move.
		 @return		A reference to the moved sprite pass (i.e. this sprite 
						pass).
		 */
		SpritePass& operator=(SpritePass&& pass) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders the world.

		 @param[in]		world
						A reference to the world.
		 @throws		Exception
						Failed to render the world.
		 */
		void Render(const World& world);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this sprite pass.
		 */
		void BindFixedState() const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------
		
		/**
		 A reference to the device context of this sprite pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A reference to the state manager of this sprite pass.
		 */
		std::reference_wrapper< StateManager > m_state_manager;

		/**
		 A pointer to the vertex shader of this sprite pass.
		 */
		VertexShaderPtr m_vs;

		/**
		 A pointer to the pixel shader of this sprite pass.
		 */
		PixelShaderPtr m_ps;

		/**
		 The sprite batch of this sprite pass.
		 */
		SpriteBatch m_sprite_batch;
	};
}