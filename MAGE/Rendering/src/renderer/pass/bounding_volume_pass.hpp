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
	 A class of bounding volume passes for rendering model and finite light 
	 volumes.
	 */
	class BoundingVolumePass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a bounding volume pass.

		 @param[in]		device
						A reference to the device.
		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		state_manager
						A reference to the state manager.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit BoundingVolumePass(ID3D11Device& device, 
									ID3D11DeviceContext& device_context, 
									StateManager& state_manager, 
									ResourceManager& resource_manager);

		/**
		 Constructs a bounding volume pass from the given bounding volume pass.

		 @param[in]		pass
						A reference to the bounding volume pass to copy.
		 */
		BoundingVolumePass(const BoundingVolumePass& pass) = delete;

		/**
		 Constructs a bounding volume pass by moving the given bounding volume 
		 pass.

		 @param[in]		pass
						A reference to the bounding volume pass to move.
		 */
		BoundingVolumePass(BoundingVolumePass&& pass) noexcept;

		/**
		 Destructs this bounding volume pass.
		 */
		~BoundingVolumePass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given bounding volume pass to this bounding volume pass.

		 @param[in]		pass
						A reference to the bounding volume pass to copy.
		 @return		A reference to the copy of the given bounding volume 
						pass (i.e. this bounding volume pass).
		 */
		BoundingVolumePass& operator=(const BoundingVolumePass& pass) = delete;

		/**
		 Moves the given bounding volume pass to this bounding volume pass.

		 @param[in]		pass
						A reference to the bounding volume pass to move.
		 @return		A reference to the moved bounding volume pass (i.e. 
						this bounding volume pass).
		 */
		BoundingVolumePass& operator=(BoundingVolumePass&& pass) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders the world.

		 @param[in]		world
						A reference to the world.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @throws		Exception
						Failed to render the world.
		 */
		void XM_CALLCONV Render(const World& world,
			                    FXMMATRIX world_to_projection);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this bounding volume pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Binds the light color of this bounding volume pass.

		 @throws		Exception
						Failed to bind the light color of this bounding 
						volume pass.
		 */
		void BindLightColor();

		/**
		 Binds the model color of this bounding volume pass.
		 
		 @throws		Exception
						Failed to bind the model color of this bounding 
						volume pass.
		 */
		void BindModelColor();

		/**
		 Binds the color of this bounding volume pass.

		 @param[in]		color
						A reference to the color.
		 @throws		Exception
						Failed to bind the light color of this bounding 
						volume pass.
		 */
		void BindColor(const RGBA& color);

		/**
		 Binds the transform of this bounding volume pass.

		 @param[in]		cube_to_world
						The cube-to-world transformation matrix used for 
						transforming cube vertices.
		 @throws		Exception
						Failed to bind the transform of this bounding volume 
						pass.
		 */
		void XM_CALLCONV BindTransform(FXMMATRIX cube_to_world);

		/**
		 Renders the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @param[in]		object_to_world
						The object-to-world transformation matrix.
		 @throws		Exception
						Failed to bind the render the given AABB.
		 */
		void XM_CALLCONV Render(const AABB& aabb, FXMMATRIX object_to_world);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device context of this bounding volume pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A reference to the state manager of this bounding volume pass.
		 */
		std::reference_wrapper< StateManager > m_state_manager;

		/**
		 A pointer to the vertex shader of this bounding volume pass.
		 */
		VertexShaderPtr m_vs;

		/**
		 A pointer to the pixel shader of this bounding volume pass.
		 */
		PixelShaderPtr m_ps;

		/**
		 The color buffer of this bounding volume pass.
		 */
		ConstantBuffer< RGBA > m_color_buffer;

		/**
		 The transform buffer of this bounding volume pass.
		 */
		ConstantBuffer< XMMATRIX > m_transform_buffer;
	};
}
